//find:
HEADER_CG_SCRIPT_SELECT_ITEM = 114,

//add below:
#ifdef ENABLE_SAVED_LOCATIONS
	HEADER_CG_SAVE_LOCATION = 120,
	HEADER_CG_RENAME_LOCATION = 121,
#endif	

//if you have already defined 120/121 change it to unused packet numbers

//find:
HEADER_GC_HYBRIDCRYPT_SDB = 153,

//add below:
#ifdef ENABLE_SAVED_LOCATIONS
	HEADER_GC_LOCATION_APPEND = 160,
#endif

//if you have already defined 160 change it to unused packet number

//find:
#pragma pack()

//add above:
#ifdef ENABLE_SAVED_LOCATIONS
typedef struct SPacketCGSaveLocation
{
	BYTE byHeader;
	BYTE byIdx;
	char szName[MAX_SAVED_LOCATION_NAME_LENGTH + 1];
} TPacketCGSaveLocation;

typedef struct SPacketCGRenameLocation
{
	BYTE byHeader;
	BYTE byIdx;
	char szName[MAX_SAVED_LOCATION_NAME_LENGTH + 1];
} TPacketCGRenameLocation;

typedef struct SPacketGCLocationAppend
{
	BYTE byHeader;
	BYTE byIdx;
	DWORD dwGlobalX;
	DWORD dwGlobalY;
	DWORD dwLocalX;
	DWORD dwLocalY;
	char szName[MAX_SAVED_LOCATION_NAME_LENGTH + 1];
} TPacketGCLocationAppend;
#endif