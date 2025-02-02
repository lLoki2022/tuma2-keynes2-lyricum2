#ifndef __INC_CRC32_H__
#define __INC_CRC32_H__

#ifndef _WIN32
#include <unistd.h>
#endif
#include <cstdint>

uint32_t	get_crc32(const char* buffer, size_t count);
uint32_t	get_crc32_case(const char* buffer, size_t count);
uint32_t	get_fast_hash(const char* key, size_t len);

#define CRC32(buf) get_crc32(buf, strlen(buf))
#define CRC32CASE(buf) get_crc32_case(buf, strlen(buf))

#endif
