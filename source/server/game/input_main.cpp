//add as the last #include at the top of the file:
#ifdef ENABLE_SAVED_LOCATIONS
#include "saved_locations_manager.h"
#endif

//find:
void CInputMain::Refine(LPCHARACTER ch, const char* c_pData)
{
	...
}

//add below:
#ifdef ENABLE_SAVED_LOCATIONS
void CInputMain::LocationSave(LPCHARACTER ch, const char* data)
{
	const TPacketCGSaveLocation* p = reinterpret_cast<const TPacketCGSaveLocation*>(data);

	SavedLocationsManager::Instance().SaveLocation(ch, p->byIdx, p->szName);
}

void CInputMain::LocationRename(LPCHARACTER ch, const char* data)
{
	const TPacketCGRenameLocation* p = reinterpret_cast<const TPacketCGRenameLocation*>(data);

	SavedLocationsManager::Instance().RenameLocation(ch, p->byIdx, p->szName);
}
#endif

#ifdef ENABLE_SAVED_LOCATIONS
		case HEADER_CG_SAVE_LOCATION:
			LocationSave(ch, c_pData);
			break;

		case HEADER_CG_RENAME_LOCATION:
			LocationRename(ch, c_pData);
			break;
#endif

//find:
case HEADER_CG_REFINE:
	Refine(ch, c_pData);
	break;
	
//add below:
#ifdef ENABLE_SAVED_LOCATIONS
		case HEADER_CG_SAVE_LOCATION:
			LocationSave(ch, c_pData);
			break;

		case HEADER_CG_RENAME_LOCATION:
			LocationRename(ch, c_pData);
			break;
#endif