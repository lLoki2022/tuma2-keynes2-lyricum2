#include "stdafx.h"

#ifndef _WIN32
#define SYSLOG_FILENAME "syslog"
#define SYSERR_FILENAME "syserr"
#define PTS_FILENAME "PTS"
#else
#define SYSLOG_FILENAME "syslog.txt"
#define SYSERR_FILENAME "syserr.txt"
#define PTS_FILENAME "PTS.txt"
#endif

using LPLOGFILE = struct log_file_s*;
using LOGFILE = struct log_file_s;

struct log_file_s
{
	char* filename;
	FILE* fp;

	int32_t last_hour;
	int32_t last_day;
};

LPLOGFILE log_file_sys = nullptr;
LPLOGFILE log_file_err = nullptr;
LPLOGFILE log_file_pt = nullptr;
static char log_dir[32] = {0,};
uint32_t log_keep_days = 3;

// Internal functions
LPLOGFILE log_file_init(const char* filename, const char* openmode);
void log_file_destroy(LPLOGFILE logfile);
void log_file_rotate(LPLOGFILE logfile);
void log_file_check(LPLOGFILE logfile);
void log_file_set_dir(const char* dir);

static uint32_t log_level_bits = 0;

void log_set_level(uint32_t bit)
{
	log_level_bits |= bit;
}

void log_unset_level(uint32_t bit)
{
	log_level_bits &= ~bit;
}

void log_set_expiration_days(uint32_t days)
{
	log_keep_days = days;
}

int32_t log_get_expiration_days(void)
{
	return log_keep_days;
}

bool log_init()
{
	log_file_set_dir("./log");

	if (!((log_file_sys = log_file_init(SYSLOG_FILENAME, "a+"))))
	{
		fprintf(stderr, "Could not initialize log_file_sys\n");
		return false;
	}

	if (!((log_file_err = log_file_init(SYSERR_FILENAME, "a+"))))
	{
		fprintf(stderr, "Could not initialize log_file_err\n");
		return false;
	}

	if (!((log_file_pt = log_file_init(PTS_FILENAME, "a+"))))
	{
		fprintf(stderr, "Could not initialize log_file_pt\n");
		return false;
	}

	/*
	 #ifdef _WIN32
		// Verbose
		FILE* fp = nullptr;
		freopen_s(&fp, "CONIN$", "r", stdin);
		freopen_s(&fp, "CONOUT$", "w", stdout);
		freopen_s(&fp, "CONOUT$", "w", stderr);
	#endif
	*/

	return true;
}

void log_destroy(void)
{
	log_file_destroy(log_file_sys);
	log_file_destroy(log_file_err);
	log_file_destroy(log_file_pt);

	log_file_sys = nullptr;
	log_file_err = nullptr;
	log_file_pt = nullptr;
}

void log_rotate(void)
{
	log_file_check(log_file_sys);
	log_file_check(log_file_err);
	log_file_check(log_file_pt);

	log_file_rotate(log_file_sys);
}

#ifndef _WIN32
void _sys_err(const char *func, int32_t line, const char *format, ...)
{
	if (!log_file_err)
		return;

	va_list args;
	time_t ct = time(nullptr);
	char *time_s = asctime(localtime(&ct));

	char buf[1024 + 2];
	int32_t len;

	time_s[strlen(time_s) - 1] = '\0';
	len = snprintf(buf, 1024, "SYSERR: %-15.15s :: %s: ", time_s + 4, func);
	buf[1025] = '\0';

	if (len < 1024)
	{
		va_start(args, format);
		vsnprintf(buf + len, 1024 - len, format, args);
		va_end(args);
	}

	strcat(buf, "\n");

	fputs(buf, log_file_err->fp);
	fflush(log_file_err->fp);
}
#else
void _sys_err(const char* func, int32_t line, const char* format, ...)
{
	if (!log_file_err)
		return;

	va_list args;
	time_t ct = time(nullptr);
	char* time_s = asctime(localtime(&ct));

	char buf[1024 + 2];
	int32_t len;

	time_s[strlen(time_s) - 1] = '\0';
	len = snprintf(buf, 1024, "SYSERR: %-15.15s :: %s: ", time_s + 4, func);
	buf[1025] = '\0';

	if (len < 1024)
	{
		va_start(args, format);
		vsnprintf(buf + len, 1024 - len, format, args);
		va_end(args);
	}

	strcat(buf, "\n");

	fputs(buf, log_file_err->fp);
	fflush(log_file_err->fp);

	fputs(buf, stdout);
	fflush(stdout);
}
#endif

static char sys_log_header_string[33] = {0,};

void sys_log_header(const char* header)
{
	strncpy(sys_log_header_string, header, 32);
}

void sys_log(uint32_t bit, const char* format, ...)
{
	va_list args;

	if (bit != 0 && !(log_level_bits & bit))
		return;

	if (log_file_sys)
	{
		time_t ct = time(nullptr);
		char* time_s = asctime(localtime(&ct));

		fprintf(log_file_sys->fp, "%s", sys_log_header_string);

		time_s[strlen(time_s) - 1] = '\0';
		fprintf(log_file_sys->fp, "%-15.15s :: ", time_s + 4);

		va_start(args, format);
		vfprintf(log_file_sys->fp, format, args);
		va_end(args);

		fputc('\n', log_file_sys->fp);
		fflush(log_file_sys->fp);
	}

#ifndef _WIN32
	if (log_level_bits > 1)
	{
#endif
	fprintf(stdout, "%s", sys_log_header_string);

	va_start(args, format);
	vfprintf(stdout, format, args);
	va_end(args);

	fputc('\n', stdout);
	fflush(stdout);
#ifndef _WIN32
	}
#endif
}

void pt_log(const char* format, ...)
{
	if (!log_file_pt)
		return;

	va_list args;
	va_start(args, format);
	vfprintf(log_file_pt->fp, format, args);
	va_end(args);

	fputc('\n', log_file_pt->fp);
	fflush(log_file_pt->fp);
}

LPLOGFILE log_file_init(const char* filename, const char* openmode)
{
	LPLOGFILE logfile;
	FILE* fp;
	struct tm curr_tm;
	time_t time_s;

	time_s = time(nullptr);
	curr_tm = *localtime(&time_s);

	fp = fopen(filename, openmode);

	if (!fp)
		return nullptr;

	logfile = (LPLOGFILE)malloc(sizeof(LOGFILE));
	logfile->filename = strdup(filename);
	logfile->fp = fp;
	logfile->last_hour = curr_tm.tm_hour;
	logfile->last_day = curr_tm.tm_mday;

	return logfile;
}

void log_file_destroy(LPLOGFILE logfile)
{
	if (logfile == nullptr)
	{
		return;
	}

	if (logfile->filename)
	{
		free(logfile->filename);
		logfile->filename = nullptr;
	}

	if (logfile->fp)
	{
		fclose(logfile->fp);
		logfile->fp = nullptr;
	}

	free(logfile);
}

void log_file_check(LPLOGFILE logfile)
{
	if (!logfile)
		return;

	struct stat sb{};

	if (stat(logfile->filename, &sb) != 0 && errno == ENOENT)
	{
		fclose(logfile->fp);
		logfile->fp = fopen(logfile->filename, "a+");
	}
}

void log_file_delete_old(const char* filename)
{
	struct stat sb;
	int32_t num1, num2;
	char buf[32];
	char system_cmd[64];
	struct tm new_tm;

	if (stat(filename, &sb) == -1)
	{
		perror("log_file_delete_old: stat");
		return;
	}

	if (!S_ISDIR(sb.st_mode))
		return;

	new_tm = *tm_calc(nullptr, -static_cast<int32_t>(log_keep_days));
	sprintf(buf, "%04d%02d%02d", new_tm.tm_year + 1900, new_tm.tm_mon + 1, new_tm.tm_mday);
	num1 = atoi(buf);
#ifndef _WIN32
	{
		struct dirent ** namelist;
		int32_t	n;

		n = scandir(filename, &namelist, 0, alphasort);

		if (n < 0)
			perror("scandir");
		else
		{
			char name[MAXNAMLEN+1];

			while (n-- > 0)
			{
				strncpy(name, namelist[n]->d_name, 255);
				name[255] = '\0';

				free(namelist[n]);

				if (*name == '.')
					continue;

				if (!isdigit(*name))
					continue;

				num2 = atoi(name);

				if (num2 <= num1)
				{
					sprintf(system_cmd, "rm -rf %s/%s", filename, name);
					system(system_cmd);

					sys_log(0, "%s: SYSTEM_CMD: %s", __FUNCTION__, system_cmd);
					fprintf(stderr, "%s: SYSTEM_CMD: %s %s:%d %s:%d\n", __FUNCTION__, system_cmd, buf, num1, name, num2);
				}
			}
		}

		free(namelist);
	}
#else
	{
		WIN32_FIND_DATA fdata;
		HANDLE hFind;
		if ((hFind = FindFirstFile(filename, &fdata)) != INVALID_HANDLE_VALUE)
		{
			do
			{
				if (!isdigit(*fdata.cFileName))
					continue;

				num2 = atoi(fdata.cFileName);

				if (num2 <= num1)
				{
					sprintf(system_cmd, "del %s\\%s", filename, fdata.cFileName);
					system(system_cmd);

					sys_log(0, "SYSTEM_CMD: %s", system_cmd);
				}
			}
			while (FindNextFile(hFind, &fdata));
		}
	}
#endif
}

void log_file_rotate(LPLOGFILE logfile)
{
	if (!logfile)
		return;

	struct tm curr_tm{};
	time_t time_s;
	char dir[128];
	char system_cmd[PATH_MAX];

	time_s = time(nullptr);
	curr_tm = *localtime(&time_s);

	if (curr_tm.tm_mday != logfile->last_day)
	{
		const struct tm new_tm = *tm_calc(&curr_tm, -3);

#ifndef _WIN32
		sprintf(system_cmd, "rm -rf %s/%04d%02d%02d", log_dir, new_tm.tm_year + 1900, new_tm.tm_mon + 1, new_tm.tm_mday);
#else
		sprintf(system_cmd, "del %s\\%04d%02d%02d", log_dir, new_tm.tm_year + 1900, new_tm.tm_mon + 1, new_tm.tm_mday);
#endif
		system(system_cmd);

		sys_log(0, "SYSTEM_CMD: %s", system_cmd);

		logfile->last_day = curr_tm.tm_mday;
	}

	if (curr_tm.tm_hour != logfile->last_hour)
	{
		struct stat stat_buf{};
		snprintf(dir, 128, "%s/%04d%02d%02d", log_dir, curr_tm.tm_year + 1900, curr_tm.tm_mon + 1, curr_tm.tm_mday);

		if (stat(dir, &stat_buf) != 0 || S_ISDIR(stat_buf.st_mode))
		{
#ifdef _WIN32
			CreateDirectory(dir, nullptr);
#else
			mkdir(dir, S_IRWXU);
#endif
		}

		//sys_log(0, "SYSTEM: LOG ROTATE (%04d-%02d-%02d %d)", curr_tm.tm_year + 1900, curr_tm.tm_mon + 1, curr_tm.tm_mday, logfile->last_hour);

		fclose(logfile->fp);

#ifndef _WIN32
		snprintf(system_cmd, PATH_MAX, "mv %s %s/%s.%02d", logfile->filename, dir, logfile->filename, logfile->last_hour);
#else
		snprintf(system_cmd, PATH_MAX, "move %s %s\\%s.%02d", logfile->filename, dir, logfile->filename, logfile->last_hour);
#endif
		system_cmd[PATH_MAX - 1] = '\0';
		system(system_cmd);

		logfile->last_hour = curr_tm.tm_hour;

		logfile->fp = fopen(logfile->filename, "a+");
	}
}

void log_file_set_dir(const char* dir)
{
	if (!dir)
	{
		fprintf(stderr, "nil log dir");
		std::exit(EXIT_FAILURE);
	}

	strcpy(log_dir, dir);
	log_file_delete_old(log_dir);
}
