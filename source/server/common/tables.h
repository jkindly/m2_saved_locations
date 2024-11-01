//find:
HEADER_GD_REQUEST_CHANNELSTATUS	= 140,

//add below:
#ifdef ENABLE_SAVED_LOCATIONS
	HEADER_GD_ADD_LOCATION = 141,
#endif

// if you have already defined 141 change it to unused packet number

//find:
HEADER_DG_RESPOND_CHANNELSTATUS	= 181

//add below:
#ifdef ENABLE_SAVED_LOCATIONS
	HEADER_DG_ADD_LOCATION = 182,
#endif

// if you have already defined 182 change it to unused packet number

//find:
#pragma pack()

//add above:
#ifdef ENABLE_SAVED_LOCATIONS
typedef struct SLocationTable
{
	DWORD dwGlobalX;
	DWORD dwGlobalY;
	DWORD dwLocalX;
	DWORD dwLocalY;
	char  szName[MAX_SAVED_LOCATION_NAME_LENGTH + 1];
} TLocationTable;

typedef struct SPacketAddLocation
{
	BYTE  byIdx;
	DWORD dwPID;
	DWORD dwGlobalX;
	DWORD dwGlobalY;
	DWORD dwLocalX;
	DWORD dwLocalY;
	char  szName[MAX_SAVED_LOCATION_NAME_LENGTH + 1];
} TPacketAddLocation;
#endif