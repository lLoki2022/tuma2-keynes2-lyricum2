#ifndef __INC_TABLES_H__
#define __INC_TABLES_H__

#include "length.h"
#include "item_length.h"
#include "CommonDefines.h"
#include "service.h"

#include <m2_length.hpp>

typedef	DWORD IDENT;

/**
 * @version 05/06/10	Bang2ni - Myshop Pricelist 관련 패킷 HEADER_XX_MYSHOP_PRICELIST_XXX 추가
 */
enum
{
	HEADER_GD_LOGIN				= 1,
	HEADER_GD_LOGOUT			= 2,

	HEADER_GD_PLAYER_LOAD		= 3,
	HEADER_GD_PLAYER_SAVE		= 4,
	HEADER_GD_PLAYER_CREATE		= 5,
	HEADER_GD_PLAYER_DELETE		= 6,

	HEADER_GD_LOGIN_KEY			= 7,
	// 8 empty
	HEADER_GD_BOOT				= 9,
	HEADER_GD_PLAYER_COUNT		= 10,
	HEADER_GD_QUEST_SAVE		= 11,
	HEADER_GD_SAFEBOX_LOAD		= 12,
	HEADER_GD_SAFEBOX_SAVE		= 13,
	HEADER_GD_SAFEBOX_CHANGE_SIZE	= 14,
	HEADER_GD_EMPIRE_SELECT		= 15,

	HEADER_GD_SAFEBOX_CHANGE_PASSWORD		= 16,
	HEADER_GD_SAFEBOX_CHANGE_PASSWORD_SECOND	= 17, // Not really a packet, used internal
	HEADER_GD_DIRECT_ENTER		= 18,

	HEADER_GD_GUILD_SKILL_UPDATE	= 19,
	HEADER_GD_GUILD_EXP_UPDATE		= 20,
	HEADER_GD_GUILD_ADD_MEMBER		= 21,
	HEADER_GD_GUILD_REMOVE_MEMBER	= 22,
	HEADER_GD_GUILD_CHANGE_GRADE	= 23,
	HEADER_GD_GUILD_CHANGE_MEMBER_DATA	= 24,
	HEADER_GD_GUILD_DISBAND		= 25,
	HEADER_GD_GUILD_WAR			= 26,
	HEADER_GD_GUILD_WAR_SCORE		= 27,
	HEADER_GD_GUILD_CREATE		= 28,
	HEADER_GD_CHANGE_COUNTRY_FLAG = 29,
	HEADER_GD_ITEM_SAVE			= 30,
	HEADER_GD_ITEM_DESTROY		= 31,

	HEADER_GD_ADD_AFFECT		= 32,
	HEADER_GD_REMOVE_AFFECT		= 33,

	HEADER_GD_HIGHSCORE_REGISTER	= 34,
	HEADER_GD_ITEM_FLUSH		= 35,

	HEADER_GD_PARTY_CREATE		= 36,
	HEADER_GD_PARTY_DELETE		= 37,
	HEADER_GD_PARTY_ADD			= 38,
	HEADER_GD_PARTY_REMOVE		= 39,
	HEADER_GD_PARTY_STATE_CHANGE	= 40,
	HEADER_GD_PARTY_HEAL_USE		= 41,

	HEADER_GD_FLUSH_CACHE		= 42,
	HEADER_GD_RELOAD_PROTO		= 43,

	HEADER_GD_CHANGE_NAME		= 44,
	HEADER_GD_SMS				= 45,

	HEADER_GD_GUILD_CHANGE_LADDER_POINT	= 46,
	HEADER_GD_GUILD_USE_SKILL		= 47,

	HEADER_GD_REQUEST_EMPIRE_PRIV	= 48,
	HEADER_GD_REQUEST_GUILD_PRIV	= 49,

	HEADER_GD_MONEY_LOG				= 50,

	HEADER_GD_GUILD_DEPOSIT_MONEY				= 51,
	HEADER_GD_GUILD_WITHDRAW_MONEY				= 52,
	HEADER_GD_GUILD_WITHDRAW_MONEY_GIVE_REPLY	= 53,

	HEADER_GD_REQUEST_CHARACTER_PRIV	= 54,

	HEADER_GD_SET_EVENT_FLAG			= 55,

	HEADER_GD_PARTY_SET_MEMBER_LEVEL	= 56,

	HEADER_GD_GUILD_WAR_BET		= 57,

	HEADER_GD_CREATE_OBJECT		= 60,
	HEADER_GD_DELETE_OBJECT		= 61,
	HEADER_GD_UPDATE_LAND		= 62,

	HEADER_GD_MARRIAGE_ADD		= 70,
	HEADER_GD_MARRIAGE_UPDATE	= 71,
	HEADER_GD_MARRIAGE_REMOVE	= 72,

	HEADER_GD_WEDDING_REQUEST	= 73,
	HEADER_GD_WEDDING_READY		= 74,
	HEADER_GD_WEDDING_END		= 75,
#if defined(ENABLE_INGAME_ITEMSHOP)
	HEADER_GD_ITEMSHOP = 76,
#endif
#if defined(USE_BATTLEPASS)
	HEADER_GD_SAVE_EXT_BATTLE_PASS = 82,
#endif
#ifdef ENABLE_HWID
	HEADER_GD_BLOCKHWID = 85,
	HEADER_GD_UNBLOCKHWID = 86,
#endif
	HEADER_GD_AUTH_LOGIN		= 100,
	HEADER_GD_LOGIN_BY_KEY		= 101,
	HEADER_GD_MALL_LOAD			= 107,

	HEADER_GD_MYSHOP_PRICELIST_UPDATE	= 108,		///< 가격정보 갱신 요청
	HEADER_GD_MYSHOP_PRICELIST_REQ		= 109,		///< 가격정보 리스트 요청

	HEADER_GD_BLOCK_CHAT				= 110,

	HEADER_GD_RELOAD_ADMIN			= 115,			///<운영자 정보 요청
	HEADER_GD_BREAK_MARRIAGE		= 116,			///< 결혼 파기

	HEADER_GD_REQ_CHANGE_GUILD_MASTER	= 129,

	HEADER_GD_REQ_SPARE_ITEM_ID_RANGE	= 130,

	HEADER_GD_UPDATE_HORSE_NAME		= 131,
	HEADER_GD_REQ_HORSE_NAME		= 132,

	HEADER_GD_DC					= 133,		// Login Key를 지움

	HEADER_GD_VALID_LOGOUT			= 134,
	HEADER_GD_EXPIRED_LOGIN_KEY = 136,
	HEADER_GD_REQUEST_CHARGE_CASH	= 137,

	HEADER_GD_DELETE_AWARDID	= 138,	// delete gift notify icon

	HEADER_GD_UPDATE_CHANNELSTATUS	= 139,
	HEADER_GD_REQUEST_CHANNELSTATUS	= 140,
#if defined(BL_OFFLINE_MESSAGE)
	HEADER_GD_REQUEST_OFFLINE_MESSAGES = 141,
	HEADER_GD_SEND_OFFLINE_MESSAGE = 142,
#endif
#ifdef __ENABLE_NEW_OFFLINESHOP__
	HEADER_GD_NEW_OFFLINESHOP		= 143,
#endif

#ifdef ENABLE_CHANNEL_SWITCH_SYSTEM
	HEADER_GD_FIND_CHANNEL = 144,
#endif
	HEADER_GD_GUILD_SYMBOL_AUTH_KEY = 146,
	HEADER_GD_SETUP = 0xff,

	///////////////////////////////////////////////
	HEADER_DG_NOTICE			= 1,

	HEADER_DG_LOGIN_SUCCESS			= 30,
	HEADER_DG_LOGIN_NOT_EXIST		= 31,
	HEADER_DG_LOGIN_WRONG_PASSWD	= 33,
	HEADER_DG_LOGIN_ALREADY			= 34,

	HEADER_DG_PLAYER_LOAD_SUCCESS	= 35,
	HEADER_DG_PLAYER_LOAD_FAILED	= 36,
	HEADER_DG_PLAYER_CREATE_SUCCESS	= 37,
	HEADER_DG_PLAYER_CREATE_ALREADY	= 38,
	HEADER_DG_PLAYER_CREATE_FAILED	= 39,
	HEADER_DG_PLAYER_DELETE_SUCCESS	= 40,
	HEADER_DG_PLAYER_DELETE_FAILED	= 41,

	HEADER_DG_ITEM_LOAD			= 42,

	HEADER_DG_BOOT				= 43,
	HEADER_DG_QUEST_LOAD		= 44,

	HEADER_DG_SAFEBOX_LOAD					= 45,
	HEADER_DG_SAFEBOX_CHANGE_SIZE			= 46,
	HEADER_DG_SAFEBOX_WRONG_PASSWORD		= 47,
	HEADER_DG_SAFEBOX_CHANGE_PASSWORD_ANSWER = 48,

	HEADER_DG_EMPIRE_SELECT		= 49,

	HEADER_DG_AFFECT_LOAD		= 50,
	HEADER_DG_MALL_LOAD			= 51,

	HEADER_DG_DIRECT_ENTER		= 55,

	HEADER_DG_GUILD_SKILL_UPDATE	= 56,
	HEADER_DG_GUILD_SKILL_RECHARGE	= 57,
	HEADER_DG_GUILD_EXP_UPDATE		= 58,

	HEADER_DG_PARTY_CREATE		= 59,
	HEADER_DG_PARTY_DELETE		= 60,
	HEADER_DG_PARTY_ADD			= 61,
	HEADER_DG_PARTY_REMOVE		= 62,
	HEADER_DG_PARTY_STATE_CHANGE	= 63,
	HEADER_DG_PARTY_HEAL_USE		= 64,
	HEADER_DG_PARTY_SET_MEMBER_LEVEL	= 65,
#if defined(ENABLE_INGAME_ITEMSHOP)
	HEADER_DG_ITEMSHOP = 76,
#endif
#if defined(USE_BATTLEPASS)
	HEADER_DG_EXT_BATTLE_PASS_LOAD = 78,
#endif
#ifdef ENABLE_HWID
	HEADER_DG_BLOCKHWID = 80,
	HEADER_DG_UNBLOCKHWID = 81,
#endif

	HEADER_DG_TIME			= 90,
	HEADER_DG_ITEM_ID_RANGE		= 91,

	HEADER_DG_GUILD_ADD_MEMBER		= 92,
	HEADER_DG_GUILD_REMOVE_MEMBER	= 93,
	HEADER_DG_GUILD_CHANGE_GRADE	= 94,
	HEADER_DG_GUILD_CHANGE_MEMBER_DATA	= 95,
	HEADER_DG_GUILD_DISBAND		= 96,
	HEADER_DG_GUILD_WAR			= 97,
	HEADER_DG_GUILD_WAR_SCORE		= 98,
	HEADER_DG_GUILD_TIME_UPDATE		= 99,
	HEADER_DG_GUILD_LOAD		= 100,
	HEADER_DG_GUILD_LADDER		= 101,
	HEADER_DG_GUILD_SKILL_USABLE_CHANGE	= 102,
	HEADER_DG_GUILD_MONEY_CHANGE	= 103,
	HEADER_DG_GUILD_WITHDRAW_MONEY_GIVE	= 104,

	HEADER_DG_SET_EVENT_FLAG		= 105,

	HEADER_DG_GUILD_WAR_RESERVE_ADD	= 106,
	HEADER_DG_GUILD_WAR_RESERVE_DEL	= 107,
	HEADER_DG_GUILD_WAR_BET		= 108,

	HEADER_DG_RELOAD_PROTO		= 120,
	HEADER_DG_CHANGE_NAME		= 121,

	HEADER_DG_AUTH_LOGIN		= 122,
	HEADER_DG_CHANGE_COUNTRY_FLAG = 123,
	HEADER_DG_CHANGE_EMPIRE_PRIV	= 124,
	HEADER_DG_CHANGE_GUILD_PRIV		= 125,

	HEADER_DG_MONEY_LOG			= 126,

	HEADER_DG_CHANGE_CHARACTER_PRIV	= 127,

	HEADER_DG_CREATE_OBJECT		= 140,
	HEADER_DG_DELETE_OBJECT		= 141,
	HEADER_DG_UPDATE_LAND		= 142,

	HEADER_DG_MARRIAGE_ADD		= 150,
	HEADER_DG_MARRIAGE_UPDATE		= 151,
	HEADER_DG_MARRIAGE_REMOVE		= 152,

	HEADER_DG_WEDDING_REQUEST		= 153,
	HEADER_DG_WEDDING_READY		= 154,
	HEADER_DG_WEDDING_START		= 155,
	HEADER_DG_WEDDING_END		= 156,

	HEADER_DG_MYSHOP_PRICELIST_RES	= 157,		///< 가격정보 리스트 응답
	HEADER_DG_RELOAD_ADMIN = 158, 				///< 운영자 정보 리로드
	HEADER_DG_BREAK_MARRIAGE = 159,				///< 결혼 파기

	HEADER_DG_BLOCK_COUNTRY_IP		= 171,		// 광대역 IP-Block
	HEADER_DG_BLOCK_EXCEPTION		= 172,		// 광대역 IP-Block 예외 account

	HEADER_DG_ACK_CHANGE_GUILD_MASTER = 173,

	HEADER_DG_ACK_SPARE_ITEM_ID_RANGE = 174,

	HEADER_DG_UPDATE_HORSE_NAME 	= 175,
	HEADER_DG_ACK_HORSE_NAME		= 176,

	HEADER_DG_NEED_LOGIN_LOG		= 177,
	HEADER_DG_RESULT_CHARGE_CASH	= 179,
	HEADER_DG_ITEMAWARD_INFORMER	= 180,	//gift notify
	HEADER_DG_RESPOND_CHANNELSTATUS		= 181,
#ifdef __ENABLE_NEW_OFFLINESHOP__
	HEADER_DG_NEW_OFFLINESHOP		= 182,
#endif

#ifdef ENABLE_CHANNEL_SWITCH_SYSTEM
	HEADER_DG_CHANNEL_RESULT = 183,
#endif
#ifdef ENABLE_ITEM_EXTRA_PROTO
	HEADER_DG_ITEM_EXTRA_PROTO_LOAD = 184,
#endif
#ifdef ENABLE_EVENT_MANAGER
	HEADER_DG_EVENT_MANAGER = 186,
	HEADER_GD_EVENT_MANAGER = 187,
#endif

#if defined(BL_OFFLINE_MESSAGE)
	HEADER_DG_RESPOND_OFFLINE_MESSAGES = 188,
#endif
	HEADER_DG_GUILD_SYMBOL_AUTH = 189,
	HEADER_DG_GUILD_SYMBOL_AUTH_KEY = 190,
	HEADER_DG_MAP_LOCATIONS		= 0xfe,
	HEADER_DG_P2P			= 0xff,
};

#ifdef ENABLE_REWARD_SYSTEM
typedef struct reward_infos
{
	char lc_text[100];
	char playerName[CHARACTER_NAME_MAX_LEN+1];
	std::vector<std::pair<DWORD, DWORD>> m_rewardItems;
}TRewardInfo;
#endif

/* game Server -> DB Server */
#pragma pack(1)
enum ERequestChargeType
{
	ERequestCharge_Cash = 0,
	ERequestCharge_Mileage,
};

typedef struct SRequestChargeCash
{
	int32_t aid;
	int32_t amount;
} TRequestChargeCash;

typedef struct SSimplePlayer
{
	DWORD		dwID;
	char		szName[CHARACTER_NAME_MAX_LEN + 1];
	BYTE		byJob;
	BYTE		byLevel;
	DWORD		dwPlayMinutes;
	BYTE		byST, byHT, byDX, byIQ;
	uint32_t wMainPart;
	BYTE		bChangeName;
	uint32_t wHairPart;
#ifdef ENABLE_ACCE_SYSTEM
	uint32_t wAccePart;
#endif
	BYTE		bDummy[4];
	long		x, y;
	long		lAddr;
	WORD		wPort;
	BYTE		skill_group;
#if defined(ENABLE_ORDER_BY_LASTPLAY)
	int32_t lastplay;
#endif
	bool is_selected;
	char country_flag[3 + 1];
} TSimplePlayer;

typedef struct SAccountTable
{
#ifdef ENABLE_HWID
	char hwid[HWID_LENGTH + 1];
#endif
	DWORD id;
	char login[LOGIN_MAX_LEN + 1];
	char passwd[PASSWD_MAX_LEN + 1];
	char social_id[SOCIAL_ID_MAX_LEN + 1];
#ifdef ENABLE_MULTILANGUAGE_SYSTEM
	char language[LANGUAGE_MAX_LEN + 1];
#endif
	char status[ACCOUNT_STATUS_MAX_LEN + 1];
	BYTE bEmpire;
#ifdef ENABLE_MULTI_LANGUAGE
	BYTE bLanguage;
#endif
#ifdef ENABLE_GENERAL_CH
	BYTE bChannel;
#endif
	TSimplePlayer players[PLAYER_PER_ACCOUNT];
} TAccountTable;

typedef struct SPacketDGCreateSuccess
{
	BYTE		bAccountCharacterIndex;
	TSimplePlayer	player;
} TPacketDGCreateSuccess;

typedef struct TPlayerItemAttribute
{
	BYTE	bType;
	short	sValue;
} TPlayerItemAttribute;

typedef struct SPlayerItem
{
	DWORD	id;
	BYTE	window;
	WORD	pos;
	DWORD	count;

	DWORD	vnum;
	long	alSockets[ITEM_SOCKET_MAX_NUM];	// 소켓번호

	TPlayerItemAttribute    aAttr[ITEM_ATTRIBUTE_MAX_NUM];

	DWORD	owner;
#ifdef ATTR_LOCK
	short	lockedattr;
#endif
#if defined(ENABLE_CHANGELOOK)
	uint32_t transmutation;
#endif
} TPlayerItem;

typedef struct TQuickSlot
{
	uint8_t type;
	uint16_t pos;
} TQuickslot;

typedef struct SPlayerSkill
{
	BYTE	bMasterType;
	BYTE	bLevel;
	time_t	tNextRead;
} TPlayerSkill;

struct	THorseInfo
{
	BYTE	bLevel;
	BYTE	bRiding;
	short	sStamina;
	short	sHealth;
	DWORD	dwHorseHealthDropTime;
};

#if defined(ENABLE_GAYA_RENEWAL)
typedef struct SPlayerGemItems
{
	BYTE	bItemId;
	BYTE	bSlotStatus;
} TPlayerGemItems;

typedef struct SGemShopTable
{
	DWORD	dwVnum;
	BYTE	bCount;
	DWORD	dwPrice;
	DWORD	dwRow;
} TGemShopTable;

typedef struct SGemShopItem
{
	BYTE	slotIndex;
	BYTE	status;
	
	DWORD	dwVnum;
	BYTE	bCount;
	DWORD	dwPrice;
} TGemShopItem;
#endif

#if defined(ENABLE_NEW_FISH_EVENT)
typedef struct SPlayerFishEventSlot
{
	uint8_t bIsMain;
	uint8_t bShape;
} TPlayerFishEventSlot;
#endif

typedef struct SPlayerTable
{
	DWORD	id;

	char	name[CHARACTER_NAME_MAX_LEN + 1];
	char	ip[IP_ADDRESS_LENGTH + 1];

	WORD	job;
	BYTE	voice;

	BYTE	level;
	BYTE	level_step;
	short	st, ht, dx, iq;
	DWORD	exp;
#if defined(ENABLE_NEW_GOLD_LIMIT)
	uint64_t gold;
#else
	uint32_t gold;
#endif
#if defined(ENABLE_WORLDBOSS)
	uint32_t wbpoints;
#endif
#if defined(ENABLE_HALLOWEEN_EVENT_2022)
	uint32_t skull;
#endif
	BYTE	dir;
	INT		x, y, z;
	INT		lMapIndex;

	long	lExitX, lExitY;
	long	lExitMapIndex;

	// @fixme301
	int		hp;
	int		sp;

	short	sRandomHP;
	short	sRandomSP;

	int         playtime;

	short	stat_point;
	short	skill_point;
	short	sub_skill_point;
	short	horse_skill_point;

	TPlayerSkill skills[SKILL_MAX_NUM];

	TQuickSlot quickslot[QUICKSLOT_MAX_NUM];

	uint32_t part_base;
	uint32_t parts[PART_MAX_NUM];

	short	stamina;

	BYTE	skill_group;
	long	lAlignment;
	char	szMobile[MOBILE_MAX_LEN + 1];

	short	stat_reset_count;

	THorseInfo	horse;

	DWORD	logoff_interval;

	int		aiPremiumTimes[PREMIUM_MAX_NUM];
#ifdef ENABLE_RANKING
	long long	lRankPoints[RANKING_MAX_CATEGORIES];
#endif
#if defined(USE_BATTLEPASS)
	int	battle_pass_premium_id;
#endif
#if defined(ENABLE_GAYA_RENEWAL)
	INT		gem;
	DWORD	gem_next_refresh;
	TPlayerGemItems gemItems[GEM_SLOTS_MAX_NUM];
#endif
#ifdef __ENABLE_PREMIUM_PLAYERS__
	BYTE premium;
	long int premium_time;
#endif
#if defined(ENABLE_PENDANT_RENEWAL)
	uint8_t bPendant;
#endif
#if defined(ENABLE_NEW_FISH_EVENT)
	uint32_t fishEventCount;
	TPlayerFishEventSlot fishEventSlot[FISH_EVENT_SLOTS_NUM];
#endif
#if defined(ENABLE_HIDE_COSTUME_SYSTEM)
	uint8_t partStatus[HIDE_PART_MAX];
#endif
	char country_flag[3 + 1];
} TPlayerTable;

typedef struct SMobSkillLevel
{
	DWORD	dwVnum;
	BYTE	bLevel;
} TMobSkillLevel;

typedef struct SEntityTable
{
	DWORD dwVnum;
} TEntityTable;

typedef struct SMobTable : public SEntityTable
{
	char	szName[CHARACTER_NAME_MAX_LEN + 1];
#ifdef ENABLE_MULTI_NAMES
	char	szLocaleName[LANGUAGE_MAX_NUM][CHARACTER_NAME_MAX_LEN + 1];
#else
	char	szLocaleName[CHARACTER_NAME_MAX_LEN + 1];
#endif

	BYTE	bType;			// Monster, NPC
	BYTE	bRank;			// PAWN, KNIGHT, KING
	BYTE	bBattleType;		// MELEE, etc..
	BYTE	bLevel;			// Level
	BYTE	bSize;

	DWORD	dwGoldMin;
	DWORD	dwGoldMax;
	DWORD	dwExp;
	DWORD	dwMaxHP;
	BYTE	bRegenCycle;
	BYTE	bRegenPercent;
	WORD	wDef;

	DWORD	dwAIFlag;
	DWORD	dwRaceFlag;
	DWORD	dwImmuneFlag;

	BYTE	bStr, bDex, bCon, bInt;
	DWORD	dwDamageRange[2];

	short	sAttackSpeed;
	short	sMovingSpeed;
	BYTE	bAggresiveHPPct;
	WORD	wAggressiveSight;
	WORD	wAttackRange;

	char	cEnchants[MOB_ENCHANTS_MAX_NUM];
	char	cResists[MOB_RESISTS_MAX_NUM];

	DWORD	dwResurrectionVnum;
	DWORD	dwDropItemVnum;

	BYTE	bMountCapacity;
	BYTE	bOnClickType;

	BYTE	bEmpire;
	char	szFolder[64 + 1];

	float	fDamMultiply;

	DWORD	dwSummonVnum;
	DWORD	dwDrainSP;
	DWORD	dwMobColor;
	DWORD	dwPolymorphItemVnum;

	TMobSkillLevel Skills[MOB_SKILL_MAX_NUM];

	BYTE	bBerserkPoint;
	BYTE	bStoneSkinPoint;
	BYTE	bGodSpeedPoint;
	BYTE	bDeathBlowPoint;
	BYTE	bRevivePoint;
} TMobTable;

typedef struct SSkillTable
{
	DWORD	dwVnum;
	char	szName[32 + 1];
	BYTE	bType;
	BYTE	bMaxLevel;
	DWORD	dwSplashRange;

	char	szPointOn[64];
	char	szPointPoly[100 + 1];
	char	szSPCostPoly[100 + 1];
	char	szDurationPoly[100 + 1];
	char	szDurationSPCostPoly[100 + 1];
	char	szCooldownPoly[100 + 1];
	char	szMasterBonusPoly[100 + 1];
	//char	szAttackGradePoly[100 + 1];
	char	szGrandMasterAddSPCostPoly[100 + 1];
	DWORD	dwFlag;
	DWORD	dwAffectFlag;

	// Data for secondary skill
	char 	szPointOn2[64];
	char 	szPointPoly2[100 + 1];
	char 	szDurationPoly2[100 + 1];
	DWORD 	dwAffectFlag2;

	// Data for grand master point
	char 	szPointOn3[64];
	char 	szPointPoly3[100 + 1];
	char 	szDurationPoly3[100 + 1];

	BYTE	bLevelStep;
	BYTE	bLevelLimit;
	DWORD	preSkillVnum;
	BYTE	preSkillLevel;

	long	lMaxHit;
	char	szSplashAroundDamageAdjustPoly[100 + 1];

	BYTE	bSkillAttrType;

	DWORD	dwTargetRange;
} TSkillTable;

#ifdef ENABLE_BUY_WITH_ITEM
typedef struct SShopItemPrice
{
	DWORD		vnum;
	DWORD		count;
} TShopItemPrice;
#endif

typedef struct SShopItemTable
{
	DWORD		vnum;
	WORD count;
#ifdef ENABLE_BUY_WITH_ITEM
	TShopItemPrice	itemprice[MAX_SHOP_PRICES];
#endif
#if defined(ENABLE_NEW_GOLD_LIMIT)
	uint64_t price;
#else
	uint32_t price;
#endif
	TItemPos	pos;
	BYTE		display_pos;
} TShopItemTable;

typedef struct SShopTable
{
	DWORD		dwVnum;
	DWORD		dwNPCVnum;
	BYTE		byItemCount;
	TShopItemTable	items[SHOP_HOST_ITEM_MAX_NUM];
} TShopTable;

#define QUEST_NAME_MAX_LEN	32
#define QUEST_STATE_MAX_LEN	64

typedef struct SQuestTable
{
	DWORD		dwPID;
	char		szName[QUEST_NAME_MAX_LEN + 1];
	char		szState[QUEST_STATE_MAX_LEN + 1];
	long		lValue;
} TQuestTable;

typedef struct SItemLimit
{
	BYTE	bType;
	long	lValue;
} TItemLimit;

typedef struct SItemApply
{
	BYTE	bType;
	long	lValue;
} TItemApply;

typedef struct SItemTable : public SEntityTable
{
	DWORD		dwVnumRange;
	char        szName[ITEM_NAME_MAX_LEN + 1];
#ifdef ENABLE_MULTI_NAMES
	char	szLocaleName[LANGUAGE_MAX_NUM][ITEM_NAME_MAX_LEN + 1];
#else
	char	szLocaleName[ITEM_NAME_MAX_LEN + 1];
#endif
	BYTE	bType;
	BYTE	bSubType;

	BYTE        bWeight;
	BYTE	bSize;

	DWORD	dwAntiFlags;
	DWORD	dwFlags;
	DWORD	dwWearFlags;
	DWORD	dwImmuneFlag;
#if defined(ENABLE_NEW_GOLD_LIMIT)
	uint64_t dwGold;
	uint64_t dwShopBuyPrice;
#else
	uint32_t dwGold;
	uint32_t dwShopBuyPrice;
#endif

	TItemLimit	aLimits[ITEM_LIMIT_MAX_NUM];
	TItemApply	aApplies[ITEM_APPLY_MAX_NUM];
	long        alValues[ITEM_VALUES_MAX_NUM];
	long	alSockets[ITEM_SOCKET_MAX_NUM];
	DWORD	dwRefinedVnum;
	WORD	wRefineSet;
	BYTE	bAlterToMagicItemPct;
	BYTE	bSpecular;
	BYTE	bGainSocketPct;

	short int	sAddonType; // 기본 속성

	// 아래 limit flag들은 realtime에 체크 할 일이 많고, 아이템 VNUM당 고정된 값인데,
	// 현재 구조대로 매번 아이템마다 필요한 경우에 LIMIT_MAX_NUM까지 루프돌면서 체크하는 부하가 커서 미리 저장 해 둠.
	char		cLimitRealTimeFirstUseIndex;		// 아이템 limit 필드값 중에서 LIMIT_REAL_TIME_FIRST_USE 플래그의 위치 (없으면 -1)
	char		cLimitTimerBasedOnWearIndex;		// 아이템 limit 필드값 중에서 LIMIT_TIMER_BASED_ON_WEAR 플래그의 위치 (없으면 -1)

} TItemTable;

struct TItemAttrTable
{
	TItemAttrTable() :
		dwApplyIndex(0),
		dwProb(0)
	{
		szApply[0] = 0;
		memset(&lValues, 0, sizeof(lValues));
		memset(&bMaxLevelBySet, 0, sizeof(bMaxLevelBySet));
	}

	char	szApply[APPLY_NAME_MAX_LEN + 1];
	DWORD	dwApplyIndex;
	DWORD	dwProb;
#ifdef ENABLE_ATTR_COSTUMES
	long	lValues[ITEM_ATTRIBUTE_MAX_LEVEL + COSTUME_ATTRIBUTE_MAX_LEVEL];
#else
	long	lValues[ITEM_ATTRIBUTE_MAX_LEVEL];
#endif
	BYTE	bMaxLevelBySet[ATTRIBUTE_SET_MAX_NUM];
};

typedef struct SConnectTable
{
	char	login[LOGIN_MAX_LEN + 1];
	IDENT	ident;
} TConnectTable;

typedef struct SLoginPacket
{
	char	login[LOGIN_MAX_LEN + 1];
	char	passwd[PASSWD_MAX_LEN + 1];
} TLoginPacket;

typedef struct SPlayerLoadPacket
{
	DWORD	account_id;
	DWORD	player_id;
	BYTE	account_index;	/* account 에서의 위치 */
} TPlayerLoadPacket;

typedef struct SPlayerCreatePacket
{
	char		login[LOGIN_MAX_LEN + 1];
	char		passwd[PASSWD_MAX_LEN + 1];
	DWORD		account_id;
	BYTE		account_index;
	TPlayerTable	player_table;
} TPlayerCreatePacket;

typedef struct SPlayerDeletePacket
{
	char	login[LOGIN_MAX_LEN + 1];
	DWORD	player_id;
	BYTE	account_index;
	//char	name[CHARACTER_NAME_MAX_LEN + 1];
	char	private_code[8];
} TPlayerDeletePacket;

typedef struct SLogoutPacket
{
	char	login[LOGIN_MAX_LEN + 1];
	char	passwd[PASSWD_MAX_LEN + 1];
} TLogoutPacket;

typedef struct SPlayerCountPacket
{
	DWORD	dwCount;
} TPlayerCountPacket;

#define SAFEBOX_MAX_NUM			135
#define SAFEBOX_PASSWORD_MAX_LEN	6

typedef struct SSafeboxTable
{
	DWORD	dwID;
	BYTE	bSize;
	DWORD	dwGold;
	WORD	wItemCount;
} TSafeboxTable;

typedef struct SSafeboxChangeSizePacket
{
	DWORD	dwID;
	BYTE	bSize;
} TSafeboxChangeSizePacket;

typedef struct SSafeboxLoadPacket
{
	DWORD	dwID;
	char	szLogin[LOGIN_MAX_LEN + 1];
	char	szPassword[SAFEBOX_PASSWORD_MAX_LEN + 1];
} TSafeboxLoadPacket;

typedef struct SSafeboxChangePasswordPacket
{
	DWORD	dwID;
	char	szOldPassword[SAFEBOX_PASSWORD_MAX_LEN + 1];
	char	szNewPassword[SAFEBOX_PASSWORD_MAX_LEN + 1];
} TSafeboxChangePasswordPacket;

typedef struct SSafeboxChangePasswordPacketAnswer
{
	BYTE	flag;
} TSafeboxChangePasswordPacketAnswer;

typedef struct SEmpireSelectPacket
{
	DWORD	dwAccountID;
	BYTE	bEmpire;
} TEmpireSelectPacket;

typedef struct SPacketGDSetup
{
	char	szPublicIP[16];	// Public IP which listen to users
	BYTE	bChannel;	// 채널
	WORD	wListenPort;	// 클라이언트가 접속하는 포트 번호
	WORD	wP2PPort;	// 서버끼리 연결 시키는 P2P 포트 번호
	long	alMaps[MAP_ALLOW_LIMIT];
	DWORD	dwLoginCount;
	BYTE	bAuthServer;
	bool guild_mark_server;
} TPacketGDSetup;

typedef struct SPacketDGMapLocations
{
	BYTE	bCount;
} TPacketDGMapLocations;

typedef struct SMapLocation
{
	long alMaps[MAP_ALLOW_LIMIT];
	char szHost[MAX_HOST_LENGTH + 1];
	WORD wPort;
#ifdef ENABLE_GENERAL_CH
	BYTE bChannel;
#endif
} TMapLocation;

typedef struct SPacketDGP2P
{
	char	szHost[MAX_HOST_LENGTH + 1];
	WORD	wPort;
	BYTE	bChannel;
} TPacketDGP2P;

typedef struct SPacketGDDirectEnter
{
	char	login[LOGIN_MAX_LEN + 1];
	char	passwd[PASSWD_MAX_LEN + 1];
	BYTE	index;
} TPacketGDDirectEnter;

typedef struct SPacketDGDirectEnter
{
	TAccountTable accountTable;
	TPlayerTable playerTable;
} TPacketDGDirectEnter;

typedef struct SPacketGuildSkillUpdate
{
	DWORD guild_id;
	int amount;
	BYTE skill_levels[12];
	BYTE skill_point;
	BYTE save;
} TPacketGuildSkillUpdate;

typedef struct SPacketGuildExpUpdate
{
	DWORD guild_id;
	int amount;
} TPacketGuildExpUpdate;

typedef struct SPacketGuildChangeMemberData
{
	DWORD guild_id;
	DWORD pid;
	DWORD offer;
	BYTE level;
	BYTE grade;
} TPacketGuildChangeMemberData;


typedef struct SPacketDGLoginAlready
{
	char	szLogin[LOGIN_MAX_LEN + 1];
} TPacketDGLoginAlready;

typedef struct TPacketAffectElement
{
	DWORD	dwType;
	BYTE	bApplyOn;
	long	lApplyValue;
	DWORD	dwFlag;
	long	lDuration;
	long	lSPCost;
} TPacketAffectElement;

typedef struct SPacketGDAddAffect
{
	DWORD			dwPID;
	TPacketAffectElement	elem;
} TPacketGDAddAffect;

typedef struct SPacketGDRemoveAffect
{
	DWORD	dwPID;
	DWORD	dwType;
	BYTE	bApplyOn;
} TPacketGDRemoveAffect;

typedef struct SPacketGDHighscore
{
	DWORD	dwPID;
	long	lValue;
	char	cDir;
	char	szBoard[21];
} TPacketGDHighscore;

typedef struct SPacketPartyCreate
{
	DWORD	dwLeaderPID;
} TPacketPartyCreate;

typedef struct SPacketPartyDelete
{
	DWORD	dwLeaderPID;
} TPacketPartyDelete;

typedef struct SPacketPartyAdd
{
	DWORD	dwLeaderPID;
	DWORD	dwPID;
	BYTE	bState;
} TPacketPartyAdd;

typedef struct SPacketPartyRemove
{
	DWORD	dwLeaderPID;
	DWORD	dwPID;
} TPacketPartyRemove;

typedef struct SPacketPartyStateChange
{
	DWORD	dwLeaderPID;
	DWORD	dwPID;
	BYTE	bRole;
	BYTE	bFlag;
} TPacketPartyStateChange;

typedef struct SPacketPartySetMemberLevel
{
	DWORD	dwLeaderPID;
	DWORD	dwPID;
	BYTE	bLevel;
} TPacketPartySetMemberLevel;

typedef struct SPacketGDBoot
{
    DWORD	dwItemIDRange[2];
	char	szIP[16];
} TPacketGDBoot;

typedef struct SPacketGuild
{
	DWORD	dwGuild;
	DWORD	dwInfo;
} TPacketGuild;

typedef struct SPacketGDGuildAddMember
{
	DWORD	dwPID;
	DWORD	dwGuild;
	BYTE	bGrade;
} TPacketGDGuildAddMember;

typedef struct SPacketDGGuildMember
{
	DWORD	dwPID;
	DWORD	dwGuild;
	BYTE	bGrade;
	BYTE	isGeneral;
	BYTE	bJob;
	BYTE	bLevel;
	DWORD	dwOffer;
	char	szName[CHARACTER_NAME_MAX_LEN + 1];
} TPacketDGGuildMember;

typedef struct SPacketGuildWar
{
	BYTE	bType;
	BYTE	bWar;
	DWORD	dwGuildFrom;
	DWORD	dwGuildTo;
	long	lWarPrice;
	long	lInitialScore;
} TPacketGuildWar;

// Game -> DB : 상대적 변화값
// DB -> Game : 토탈된 최종값
typedef struct SPacketGuildWarScore
{
	DWORD dwGuildGainPoint;
	DWORD dwGuildOpponent;
	long lScore;
	long lBetScore;
} TPacketGuildWarScore;

typedef struct SRefineMaterial
{
	uint32_t vnum;
	uint16_t count;
} TRefineMaterial;

typedef struct SRefineTable
{
	uint32_t id;
	uint8_t material_count;
#if defined(ENABLE_NEW_GOLD_LIMIT)
	uint64_t cost;
#else
	uint32_t cost;
#endif
	uint8_t prob;
	TRefineMaterial materials[REFINE_MATERIAL_MAX_NUM];
} TRefineTable;

typedef struct SBanwordTable
{
	char szWord[BANWORD_MAX_LEN + 1];
} TBanwordTable;

typedef struct SPacketGDChangeName
{
	DWORD pid;
	char name[CHARACTER_NAME_MAX_LEN + 1];
} TPacketGDChangeName;

typedef struct SPacketDGChangeName
{
	DWORD pid;
	char name[CHARACTER_NAME_MAX_LEN + 1];
} TPacketDGChangeName;

typedef struct SPacketGuildLadder
{
	DWORD dwGuild;
	long lLadderPoint;
	long lWin;
	long lDraw;
	long lLoss;
} TPacketGuildLadder;

typedef struct SPacketGuildLadderPoint
{
	DWORD dwGuild;
	long lChange;
} TPacketGuildLadderPoint;

typedef struct SPacketGDSMS
{
	char szFrom[CHARACTER_NAME_MAX_LEN + 1];
	char szTo[CHARACTER_NAME_MAX_LEN + 1];
	char szMobile[MOBILE_MAX_LEN + 1];
	char szMsg[SMS_MAX_LEN + 1];
} TPacketGDSMS;

typedef struct SPacketGuildUseSkill
{
	DWORD dwGuild;
	DWORD dwSkillVnum;
	DWORD dwCooltime;
} TPacketGuildUseSkill;

typedef struct SPacketGuildSkillUsableChange
{
	DWORD dwGuild;
	DWORD dwSkillVnum;
	BYTE bUsable;
} TPacketGuildSkillUsableChange;

typedef struct SPacketGDLoginKey
{
	DWORD dwAccountID;
	DWORD dwLoginKey;
} TPacketGDLoginKey;

typedef struct SPacketGDAuthLogin
{
	DWORD	dwID;
#ifdef ENABLE_HWID
	char hwid[HWID_LENGTH + 1];
#endif
	DWORD	dwLoginKey;
	char	szLogin[LOGIN_MAX_LEN + 1];
	char	szSocialID[SOCIAL_ID_MAX_LEN + 1];
#ifdef ENABLE_MULTILANGUAGE_SYSTEM
	char	szLanguage[LANGUAGE_MAX_LEN + 1];
#endif
	DWORD	adwClientKey[4];
#ifdef ENABLE_MULTI_LANGUAGE
	BYTE	bLanguage;
#endif	
	int		iPremiumTimes[PREMIUM_MAX_NUM];
} TPacketGDAuthLogin;

typedef struct SPacketGDLoginByKey
{
	char	szLogin[LOGIN_MAX_LEN + 1];
	DWORD	dwLoginKey;
	DWORD	adwClientKey[4];
	char	szIP[MAX_HOST_LENGTH + 1];
} TPacketGDLoginByKey;

/**
 * @version 05/06/08	Bang2ni - 지속시간 추가
 */
typedef struct SPacketGiveGuildPriv
{
	BYTE type;
	int value;
	DWORD guild_id;
	time_t duration_sec;	///< 지속시간
} TPacketGiveGuildPriv;
typedef struct SPacketGiveEmpirePriv
{
	BYTE type;
	int value;
	BYTE empire;
	time_t duration_sec;
} TPacketGiveEmpirePriv;
typedef struct SPacketGiveCharacterPriv
{
	BYTE type;
	int value;
	DWORD pid;
} TPacketGiveCharacterPriv;
typedef struct SPacketRemoveGuildPriv
{
	BYTE type;
	DWORD guild_id;
} TPacketRemoveGuildPriv;
typedef struct SPacketRemoveEmpirePriv
{
	BYTE type;
	BYTE empire;
} TPacketRemoveEmpirePriv;

typedef struct SPacketDGChangeCharacterPriv
{
	BYTE type;
	int value;
	DWORD pid;
	BYTE bLog;
} TPacketDGChangeCharacterPriv;

/**
 * @version 05/06/08	Bang2ni - 지속시간 추가
 */
typedef struct SPacketDGChangeGuildPriv
{
	BYTE type;
	int value;
	DWORD guild_id;
	BYTE bLog;
	time_t end_time_sec;	///< 지속시간
} TPacketDGChangeGuildPriv;

typedef struct SPacketDGChangeEmpirePriv
{
	BYTE type;
	int value;
	BYTE empire;
	BYTE bLog;
	time_t end_time_sec;
} TPacketDGChangeEmpirePriv;

typedef struct SPacketMoneyLog
{
	BYTE type;
	DWORD vnum;
#if defined(ENABLE_NEW_GOLD_LIMIT)
	uint64_t gold;
#else
	uint32_t gold;
#endif
} TPacketMoneyLog;

typedef struct SPacketGDGuildMoney
{
	DWORD dwGuild;
	INT iGold;
} TPacketGDGuildMoney;

typedef struct SPacketDGGuildMoneyChange
{
	DWORD dwGuild;
	INT iTotalGold;
} TPacketDGGuildMoneyChange;

typedef struct SPacketDGGuildMoneyWithdraw
{
	DWORD dwGuild;
	INT iChangeGold;
} TPacketDGGuildMoneyWithdraw;

typedef struct SPacketGDGuildMoneyWithdrawGiveReply
{
	DWORD dwGuild;
	INT iChangeGold;
	BYTE bGiveSuccess;
} TPacketGDGuildMoneyWithdrawGiveReply;

typedef struct SPacketSetEventFlag
{
	char	szFlagName[EVENT_FLAG_NAME_MAX_LEN + 1];
	long	lValue;
} TPacketSetEventFlag;

typedef struct SPacketLoginOnSetup
{
	DWORD   dwID;
#ifdef ENABLE_HWID
	char hwid[HWID_LENGTH + 1];
#endif
	char    szLogin[LOGIN_MAX_LEN + 1];
	char    szSocialID[SOCIAL_ID_MAX_LEN + 1];
#ifdef ENABLE_MULTILANGUAGE_SYSTEM
	char	szLanguage[LANGUAGE_MAX_LEN + 1];
#endif
	char    szHost[MAX_HOST_LENGTH + 1];
	DWORD   dwLoginKey;
	DWORD   adwClientKey[4];
#ifdef ENABLE_MULTI_LANGUAGE
	BYTE	bLanguage;
#endif
} TPacketLoginOnSetup;

typedef struct SPacketGDCreateObject
{
	DWORD	dwVnum;
	DWORD	dwLandID;
	INT		lMapIndex;
	INT	 	x, y;
	float	xRot;
	float	yRot;
	float	zRot;
} TPacketGDCreateObject;

typedef struct SGuildReserve
{
	DWORD       dwID;
	DWORD       dwGuildFrom;
	DWORD       dwGuildTo;
	DWORD       dwTime;
	BYTE        bType;
	long        lWarPrice;
	long        lInitialScore;
	bool        bStarted;
	DWORD	dwBetFrom;
	DWORD	dwBetTo;
	long	lPowerFrom;
	long	lPowerTo;
	long	lHandicap;
} TGuildWarReserve;

typedef struct
{
	DWORD	dwWarID;
	char	szLogin[LOGIN_MAX_LEN + 1];
	DWORD	dwGold;
	DWORD	dwGuild;
} TPacketGDGuildWarBet;

// Marriage

typedef struct
{
	DWORD dwPID1;
	DWORD dwPID2;
	time_t tMarryTime;
	char szName1[CHARACTER_NAME_MAX_LEN + 1];
	char szName2[CHARACTER_NAME_MAX_LEN + 1];
} TPacketMarriageAdd;

typedef struct
{
	DWORD dwPID1;
	DWORD dwPID2;
	INT  iLovePoint;
	BYTE  byMarried;
} TPacketMarriageUpdate;

typedef struct
{
	DWORD dwPID1;
	DWORD dwPID2;
} TPacketMarriageRemove;

typedef struct
{
	DWORD dwPID1;
	DWORD dwPID2;
} TPacketWeddingRequest;

typedef struct
{
	DWORD dwPID1;
	DWORD dwPID2;
	DWORD dwMapIndex;
} TPacketWeddingReady;

typedef struct
{
	DWORD dwPID1;
	DWORD dwPID2;
} TPacketWeddingStart;

typedef struct
{
	DWORD dwPID1;
	DWORD dwPID2;
} TPacketWeddingEnd;

/// 개인상점 가격정보의 헤더. 가변 패킷으로 이 뒤에 byCount 만큼의 TItemPriceInfo 가 온다.
typedef struct SPacketMyshopPricelistHeader
{
	DWORD	dwOwnerID;	///< 가격정보를 가진 플레이어 ID
	BYTE	byCount;	///< 가격정보 갯수
} TPacketMyshopPricelistHeader;

/// 개인상점의 단일 아이템에 대한 가격정보
typedef struct SItemPriceInfo
{
	DWORD	dwVnum;		///< 아이템 vnum
	DWORD	dwPrice;	///< 가격
} TItemPriceInfo;

/// 개인상점 아이템 가격정보 리스트 테이블
typedef struct SItemPriceListTable
{
	DWORD	dwOwnerID;	///< 가격정보를 가진 플레이어 ID
	BYTE	byCount;	///< 가격정보 리스트의 갯수

	TItemPriceInfo	aPriceInfo[SHOP_PRICELIST_MAX_NUM];	///< 가격정보 리스트
} TItemPriceListTable;

typedef struct
{
	char szName[CHARACTER_NAME_MAX_LEN + 1];
	long lDuration;
} TPacketBlockChat;

//ADMIN_MANAGER
typedef struct TAdminInfo
{
	int m_ID;				//고유ID
	char m_szAccount[32];	//계정
	char m_szName[32];		//캐릭터이름
	char m_szContactIP[16];	//접근아이피
	char m_szServerIP[16];  //서버아이피
	int m_Authority;		//권한
} tAdminInfo;
//END_ADMIN_MANAGER

//BOOT_LOCALIZATION
struct tLocale
{
	char szValue[32];
	char szKey[32];
};
//BOOT_LOCALIZATION

//RELOAD_ADMIN
typedef struct SPacketReloadAdmin
{
	char szIP[16];
} TPacketReloadAdmin;
//END_RELOAD_ADMIN

typedef struct tChangeGuildMaster
{
	DWORD dwGuildID;
	DWORD idFrom;
	DWORD idTo;
} TPacketChangeGuildMaster;

typedef struct tItemIDRange
{
	DWORD dwMin;
	DWORD dwMax;
	DWORD dwUsableItemIDMin;
} TItemIDRangeTable;

typedef struct tUpdateHorseName
{
	DWORD dwPlayerID;
	char szHorseName[CHARACTER_NAME_MAX_LEN + 1];
} TPacketUpdateHorseName;

typedef struct tDC
{
	char	login[LOGIN_MAX_LEN + 1];
} TPacketDC;

typedef struct SPacketExpiredLoginKey
{
	char login[LOGIN_MAX_LEN + 1];
	uint32_t dwLoginKey;
} TPacketExpiredLoginKey;

typedef struct tNeedLoginLogInfo
{
	DWORD dwPlayerID;
} TPacketNeedLoginLogInfo;

//독일 선물 알림 기능 테스트용 패킷 정보
typedef struct tItemAwardInformer
{
	char	login[LOGIN_MAX_LEN + 1];
	char	command[20];		//명령어
	unsigned int vnum;			//아이템
} TPacketItemAwardInfromer;
// 선물 알림 기능 삭제용 패킷 정보
typedef struct tDeleteAwardID
{
	DWORD dwID;
} TPacketDeleteAwardID;

typedef struct SChannelStatus
{
	uint16_t port;
	uint8_t status;
} TChannelStatus;

typedef struct SPacketGuildSymbolAuthKey
{
	uint32_t gid, pid;
	uint8_t key[32];
	bool empty;
} TPacketGuildSymbolAuthKey;

#ifdef __ENABLE_NEW_OFFLINESHOP__
//common
typedef struct {
	BYTE bSubHeader;
} TPacketGDNewOfflineShop;


typedef struct {
	BYTE bSubHeader;
} TPacketDGNewOfflineShop;


namespace offlineshop
{
	//patch 08-03-2020
	enum class ExpirationType {
		EXPIRE_NONE,
		EXPIRE_REAL_TIME,
		EXPIRE_REAL_TIME_FIRST_USE,
	};

	typedef struct SPriceInfo
	{
		long long	illYang;
#ifdef __ENABLE_CHEQUE_SYSTEM__
		int iCheque;
#endif

		SPriceInfo() : illYang(0)
#ifdef __ENABLE_CHEQUE_SYSTEM__
			,iCheque(0)
#endif
		{}

		bool operator < (const SPriceInfo& rItem) const
		{
			return GetTotalYangAmount() < rItem.GetTotalYangAmount();
		}

		long long GetTotalYangAmount() const{
			long long total = illYang;
#ifdef __ENABLE_CHEQUE_SYSTEM__
			total += (long long) YANG_PER_CHEQUE * (long long) iCheque;
#endif
			return total;
		}

	} TPriceInfo;

	typedef struct
	{
		DWORD	dwVnum;
		DWORD	dwCount;
		long	alSockets[ITEM_SOCKET_MAX_NUM];
		TPlayerItemAttribute    aAttr[ITEM_ATTRIBUTE_MAX_NUM];

#if defined(ENABLE_CHANGELOOK)
		DWORD	dwTransmutation;
#endif
#ifdef ATTR_LOCK
		int     iLockedAttr;
#endif
		//patch 08-03-2020
		ExpirationType	expiration;

	} TItemInfoEx;

	typedef struct
	{
		DWORD		dwOwnerID, dwItemID;
		TPriceInfo	price;
		TItemInfoEx	item;
#if defined(ENABLE_OFFLINESHOP_REWORK)
		char szOwnerName[CHARACTER_NAME_MAX_LEN+1];
#endif
	} TItemInfo;

	typedef struct {
		DWORD		dwOfferID, dwOwnerID, dwItemID, dwOffererID;
		TPriceInfo	price;
		bool		bNoticed, bAccepted;

		//offlineshop-updated 03/08/19
		char		szBuyerName[CHARACTER_NAME_MAX_LEN+1];

	} TOfferInfo;

	//AUCTION
	typedef struct {
		DWORD dwOwnerID;
		char  szOwnerName[CHARACTER_NAME_MAX_LEN + 1];
		DWORD dwDuration;

		TPriceInfo	init_price;
		TItemInfoEx item;
	} TAuctionInfo;


	typedef struct {
		TPriceInfo	price;
		DWORD		dwOwnerID;
		DWORD		dwBuyerID;

		char		szBuyerName[CHARACTER_NAME_MAX_LEN + 1];
	} TAuctionOfferInfo;

	typedef struct SValutesInfoa
	{
		long long	illYang;
#ifdef __ENABLE_CHEQUE_SYSTEM__
		int 		iCheque;
#endif

		void operator +=(const SValutesInfoa& r)
		{
			illYang += r.illYang;
#ifdef __ENABLE_CHEQUE_SYSTEM__
			iCheque += r.iCheque;
#endif
		}

		void operator -=(const SValutesInfoa& r)
		{
			illYang -= r.illYang;
#ifdef __ENABLE_CHEQUE_SYSTEM__
			iCheque -= r.iCheque;
#endif
		}

		SValutesInfoa() : illYang(0)
#ifdef __ENABLE_CHEQUE_SYSTEM__
			, iCheque(0)
#endif
		{}

	} TValutesInfo;


	typedef struct {
		DWORD	dwOwnerID;
		DWORD	dwDuration;
		char	szName[OFFLINE_SHOP_NAME_MAX_LEN];
		DWORD	dwCount;
	} TShopInfo;

	// ### GAME TO DB ###

	enum eNewOfflineshopSubHeaderGD
	{
		SUBHEADER_GD_BUY_ITEM = 0,
		SUBHEADER_GD_BUY_LOCK_ITEM,
		SUBHEADER_GD_CANNOT_BUY_LOCK_ITEM, //topatch
		SUBHEADER_GD_EDIT_ITEM,
		SUBHEADER_GD_REMOVE_ITEM,
		SUBHEADER_GD_ADD_ITEM,

		SUBHEADER_GD_SHOP_FORCE_CLOSE,
		SUBHEADER_GD_SHOP_CREATE_NEW,
		SUBHEADER_GD_SHOP_CHANGE_NAME,
#if defined(ENABLE_OFFLINESHOP_REWORK)
		SUBHEADER_GD_SHOP_EXTEND_TIME,
#endif

		SUBHEADER_GD_OFFER_CREATE,
		SUBHEADER_GD_OFFER_NOTIFIED,
		SUBHEADER_GD_OFFER_ACCEPT,
		SUBHEADER_GD_OFFER_CANCEL,

		SUBHEADER_GD_SAFEBOX_GET_ITEM,
		SUBHEADER_GD_SAFEBOX_GET_VALUTES,
		SUBHEADER_GD_SAFEBOX_ADD_ITEM,

		//AUCTION
		SUBHEADER_GD_AUCTION_CREATE,
		SUBHEADER_GD_AUCTION_ADD_OFFER,
		SUBHEADER_GD_AUCTION_CLOSE,
	};



	typedef struct {
		DWORD dwOwnerID, dwItemID, dwGuestID;
	} TSubPacketGDBuyItem;


	typedef struct {
		DWORD dwOwnerID, dwItemID, dwGuestID;
		long long TotalPriceSeen;
	} TSubPacketGDLockBuyItem;

	typedef struct SSubPacketGDCannotBuyLockItem //topatch
	{
		DWORD dwOwnerID, dwItemID;
	} TSubPacketGDCannotBuyLockItem;

	typedef struct {
		DWORD		dwOwnerID, dwItemID;
		TPriceInfo	priceInfo;
	} TSubPacketGDEditItem;


	typedef struct {
		DWORD dwOwnerID;
		DWORD dwItemID;
	} TSubPacketGDRemoveItem;


	typedef struct {
		DWORD		dwOwnerID;
		TItemInfo	itemInfo;
	} TSubPacketGDAddItem;


	typedef struct {
		DWORD dwOwnerID;
	} TSubPacketGDShopForceClose;


	typedef struct {
		TShopInfo shop;
	} TSubPacketGDShopCreateNew;


	typedef struct {
		DWORD	dwOwnerID;
		char	szName[OFFLINE_SHOP_NAME_MAX_LEN];
	} TSubPacketGDShopChangeName;

#if defined(ENABLE_OFFLINESHOP_REWORK)
	typedef struct {
		DWORD	dwOwnerID;
		DWORD	dwTime;
	} TSubPacketGDShopExtendTime;

	typedef struct {
		DWORD dwOwnerID;
		DWORD dwTime;
	} TSubPacketDGShopExtendTime;
#endif

	typedef struct {
		DWORD dwOwnerID, dwItemID;
		TOfferInfo offer;
	} TSubPacketGDOfferCreate;


	typedef struct {
		DWORD dwOfferID;
		DWORD dwOwnerID;
	}TSubPacketGDOfferCancel;


	typedef struct {
		DWORD dwOwnerID, dwOfferID;
	} TSubPacketGDOfferNotified;


	typedef struct {
		DWORD dwOwnerID, dwOfferID;
	} TSubPacketGDOfferAccept;


	typedef struct {
		DWORD			dwOwnerID;
		DWORD			dwItemID;
	} TSubPacketGDSafeboxGetItem;


	typedef struct {
		DWORD			dwOwnerID;
		TItemInfoEx		item;
	} TSubPacketGDSafeboxAddItem;



	typedef struct {
		DWORD			dwOwnerID;
		TValutesInfo	valute;
	} TSubPacketGDSafeboxGetValutes;


	//AUCTION
	typedef struct 
	{
		TAuctionInfo auction;
	}TSubPacketGDAuctionCreate;

	typedef struct 
	{
		TAuctionOfferInfo offer;
	}TSubPacketGDAuctionAddOffer;

	typedef struct  {
		DWORD dwOwnerID;
	}TSubPacketGDAuctionClose;



	// ### DB TO GAME

	enum eSubHeaderDGNewOfflineshop
	{
		SUBHEADER_DG_BUY_ITEM,
		SUBHEADER_DG_LOCKED_BUY_ITEM,
		SUBHEADER_DG_EDIT_ITEM,
		SUBHEADER_DG_REMOVE_ITEM,
		SUBHEADER_DG_ADD_ITEM,

		SUBHEADER_DG_SHOP_FORCE_CLOSE,
		SUBHEADER_DG_SHOP_CREATE_NEW,
		SUBHEADER_DG_SHOP_CHANGE_NAME,
#if defined(ENABLE_OFFLINESHOP_REWORK)
		SUBHEADER_DG_SHOP_EXTEND_TIME,
#endif
		SUBHEADER_DG_SHOP_EXPIRED,


		SUBHEADER_DG_OFFER_CREATE,
		SUBHEADER_DG_OFFER_NOTIFIED,
		SUBHEADER_DG_OFFER_ACCEPT,
		SUBHEADER_DG_OFFER_CANCEL,

		SUBHEADER_DG_LOAD_TABLES,

		SUBHEADER_DG_SAFEBOX_ADD_ITEM,
		SUBHEADER_DG_SAFEBOX_ADD_VALUTES,
		SUBHEADER_DG_SAFEBOX_LOAD,
		//patch 08-03-2020
		SUBHEADER_DG_SAFEBOX_EXPIRED_ITEM,

		//AUCTION
		SUBHEADER_DG_AUCTION_CREATE,
		SUBHEADER_DG_AUCTION_ADD_OFFER,
		SUBHEADER_DG_AUCTION_EXPIRED,
	};


	typedef struct {
		DWORD dwOwnerID, dwItemID, dwBuyerID;
	} TSubPacketDGBuyItem;

	typedef struct {
		DWORD dwOwnerID, dwItemID, dwBuyerID;
	} TSubPacketDGLockedBuyItem;


	typedef struct {
		DWORD		dwOwnerID, dwItemID;
		TPriceInfo	price;
	} TSubPacketDGEditItem;


	typedef struct {
		DWORD dwOwnerID, dwItemID;
	} TSubPacketDGRemoveItem;


	typedef struct {
		DWORD		dwOwnerID, dwItemID;
		TItemInfo	item;
	} TSubPacketDGAddItem;


	typedef struct {
		DWORD dwOwnerID;
	} TSubPacketDGShopForceClose;


	typedef struct {
		TShopInfo shop;
	} TSubPacketDGShopCreateNew;



	typedef struct {
		DWORD dwOwnerID;
		char  szName[OFFLINE_SHOP_NAME_MAX_LEN];
	} TSubPacketDGShopChangeName;


	typedef struct {
		DWORD		dwOwnerID, dwItemID;
		TOfferInfo	offer;
	} TSubPacketDGOfferCreate;


	typedef struct {
		DWORD dwOfferID;
		DWORD dwOwnerID;

		//offlineshop-updated 05/08/19
		bool  IsRemovingItem;

	}TSubPacketDGOfferCancel;



	typedef struct {
		DWORD dwOwnerID, dwOfferID;
	} TSubPacketDGOfferNotified;

	typedef struct {
		DWORD dwOwnerID, dwOfferID;
	} TSubPacketDGOfferAccept;

	typedef struct {
		DWORD	dwShopCount;
		DWORD	dwOfferCount;
		DWORD	dwAuctionCount;
		DWORD	dwAuctionOfferCount;

	} TSubPacketDGLoadTables;


	typedef struct {
		DWORD dwOwnerID;
	} TSubPacketDGShopExpired;


	typedef struct {
		DWORD dwOwnerID, dwItemID;
		TItemInfoEx item;
	} TSubPacketDGSafeboxAddItem;


	typedef struct {
		DWORD			dwOwnerID;
		TValutesInfo	valute;
	} TSubPacketDGSafeboxAddValutes;

	typedef struct {
		DWORD			dwOwnerID;
		TValutesInfo	valute;

		DWORD			dwItemCount;
	} TSubPacketDGSafeboxLoad;

	//patch 08-03-2020
	typedef struct {
		DWORD dwOwnerID;
		DWORD dwItemID;
	} TSubPacketDGSafeboxExpiredItem;


	//AUCTION
	typedef struct 
	{
		TAuctionInfo auction;
	}TSubPacketDGAuctionCreate;

	typedef struct 
	{
		TAuctionOfferInfo offer;
	}TSubPacketDGAuctionAddOffer;

	typedef struct
	{
		DWORD dwOwnerID;
	}TSubPacketDGAuctionExpired;

}

#endif

#ifdef ENABLE_CHANNEL_SWITCH_SYSTEM
typedef struct
{
	long lMapIndex;
	int channel;
} TPacketChangeChannel;

typedef struct
{
	long lAddr;
	WORD port;
} TPacketReturnChannel;
#endif

#ifdef ENABLE_ITEM_EXTRA_PROTO
typedef struct {
	DWORD dwVnum;

#ifdef ENABLE_RARITY_SYSTEM
	int iRarity;
#endif
#ifdef ENABLE_NEW_EXTRA_BONUS
	TItemApply ExtraBonus[NEW_EXTRA_BONUS_COUNT];
#endif
} TItemExtraProto;


typedef struct {
	DWORD dwCount;
	DWORD dwTableSize;
} TPacketDGLoadItemExtraProto;

#endif

#if defined(BL_OFFLINE_MESSAGE)
typedef struct
{
	char 	szName[CHARACTER_NAME_MAX_LEN + 1];
} TPacketGDReadOfflineMessage;

typedef struct
{
	char	szFrom[CHARACTER_NAME_MAX_LEN + 1];
	char	szMessage[CHAT_MAX_LEN + 1];
} TPacketDGReadOfflineMessage;

typedef struct
{
	char	szFrom[CHARACTER_NAME_MAX_LEN + 1];
	char	szTo[CHARACTER_NAME_MAX_LEN + 1];
	char	szMessage[CHAT_MAX_LEN + 1];
} TPacketGDSendOfflineMessage;
#endif

#ifdef ENABLE_HWID
typedef struct {
	char whoname[CHARACTER_NAME_MAX_LEN + 1];
	char targetname[CHARACTER_NAME_MAX_LEN + 1];
} THwidRequest;
#endif

#ifdef ENABLE_EVENT_MANAGER
typedef struct event_struct_
{
	int16_t eventID;
	uint8_t eventIndex;
	int32_t startTime;
	int32_t endTime;
	uint8_t empireFlag;
	uint8_t channelFlag;
	uint32_t value[4];
	bool eventStatus;
	bool eventTypeOnlyStart;
} TEventManagerData;

enum
{
	EVENT_MANAGER_LOAD,
	EVENT_MANAGER_EVENT_STATUS,
	EVENT_MANAGER_REMOVE_EVENT,
	EVENT_MANAGER_UPDATE,
	BONUS_EVENT = 1,
	DOUBLE_BOSS_LOOT_EVENT = 2,
	DOUBLE_METIN_LOOT_EVENT = 3,
	DOUBLE_MISSION_BOOK_EVENT = 4,
	DUNGEON_COOLDOWN_EVENT = 5,
	DUNGEON_TICKET_LOOT_EVENT = 6,
	EMPIRE_WAR_EVENT = 7,
	MOONLIGHT_EVENT = 8,
	TOURNAMENT_EVENT = 9,
	WHELL_OF_FORTUNE_EVENT = 10,
#if defined(ENABLE_HALLOWEEN_EVENT_2022)
	HALLOWEEN_EVENT = 11,
#endif
	NPC_SEARCH_EVENT = 12,
	EXP_EVENT = 13,
	ITEM_DROP_EVENT = 14,
	YANG_DROP_EVENT = 15,
#if defined(ENABLE_NEW_FISH_EVENT)
	JIGSAW_EVENT = 16,
#endif
#if defined(ENABLE_LETTERS_EVENT)
	LETTERS_EVENT = 17,
#endif
#if defined(ENABLE_OKEY_CARD_GAME)
	OKEY_CARD_EVENT = 18,
#endif
};
#endif

#if defined(ENABLE_INGAME_ITEMSHOP)
enum
{
	ITEMSHOP_LOAD,
	ITEMSHOP_LOG,
	ITEMSHOP_BUY,
	ITEMSHOP_DRAGONCOIN,
	ITEMSHOP_RELOAD,
};

typedef struct SIShopData
{
	DWORD	id;
	DWORD	itemVnum;
	long long	itemPrice;
	int		topSellingIndex;
	BYTE	discount;
	int		offerTime;
	int		addedTime;
	long long	sellCount;
	int	week_limit;
	int	month_limit;
}TIShopData;

typedef struct SIShopLogData
{
	DWORD	accountID;
	char	playerName[CHARACTER_NAME_MAX_LEN+1];
	char	buyDate[21];
	int		buyTime;
	char	ipAdress[16];
	DWORD	itemVnum;
	int		itemCount;
	long long	itemPrice;
}TIShopLogData;
#endif

#if defined(USE_BATTLEPASS)
typedef struct SPlayerExtBattlePassMission
{
	DWORD dwPlayerId;
	DWORD dwMissionIndex;
	DWORD dwMissionType;
	DWORD dwBattlePassId;
	DWORD dwExtraInfo;
	BYTE bCompleted;
	BYTE bIsUpdated;
} TPlayerExtBattlePassMission;

typedef struct SExtBattlePassRewardItem
{
	DWORD dwVnum;
	DWORD bCount;
} TExtBattlePassRewardItem;

typedef struct SExtBattlePassMissionInfo
{
	BYTE bMissionIndex;
	BYTE bMissionType;
	DWORD dwMissionInfo[3];
	TExtBattlePassRewardItem aRewardList[3];
} TExtBattlePassMissionInfo;

typedef struct SExtBattlePassTimeTable
{
	BYTE	bBattlePassId;
	DWORD	dwStartTime;
	DWORD	dwEndTime;
} TExtBattlePassTimeTable;
#endif

#if defined(USE_ATTR_6TH_7TH)
typedef struct SAttr67AddData
{
	SAttr67AddData() : wRegistItemPos(0), byMaterialCount(0), wSupportItemPos(0), bySupportItemCount(0) {}
	uint16_t wRegistItemPos;
	uint8_t byMaterialCount;
	uint16_t wSupportItemPos;
	uint8_t bySupportItemCount;
} TAttr67AddData;
#endif

typedef struct SPacketGDChangeCountryFlag
{
	char login[LOGIN_MAX_LEN + 1];
	DWORD pid;
	char country_flag[3 + 1];
} TPacketGDChangeCountryFlag;

typedef struct SPacketDGChangeCountryFlag
{
	DWORD pid;
	char country_flag[3 + 1];
} TPacketDGChangeCountryFlag;

#pragma pack()
#endif
