//add as the last #include at the top of the file:
#ifdef ENABLE_SAVED_LOCATIONS
#include "saved_locations_manager.h"
#endif

//find:
	default:
		return (-1);

//add above:
#ifdef ENABLE_SAVED_LOCATIONS
	case HEADER_DG_ADD_LOCATION:
		AddLocation(c_pData);
		break;
#endif	

//add at the bottom of the file:
#ifdef ENABLE_SAVED_LOCATIONS
void CInputDB::AddLocation(const char* c_pData)
{
	TPacketAddLocation* p = (TPacketAddLocation*)c_pData;

	TLocationTable localization{};
	localization.dwGlobalX = p->dwGlobalX;
	localization.dwGlobalY = p->dwGlobalY;
	localization.dwLocalX = p->dwLocalX;
	localization.dwLocalY = p->dwLocalY;
	strlcpy(localization.szName, p->szName, sizeof(localization.szName));

	SavedLocationsManager::Instance().AddLocationToMap(p->dwPID, p->byIdx, localization);
}
#endif