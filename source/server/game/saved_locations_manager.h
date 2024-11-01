#ifdef ENABLE_SAVED_LOCATIONS
#pragma once
#include "../../common/tables.h"

class SavedLocationsManager : public singleton<SavedLocationsManager>
{
private:
	typedef std::map<DWORD, std::map<BYTE, TLocationTable>> TMapLocation;
	TMapLocation m_MapLocation;
	bool IsLocationsLoaded(DWORD pid);
	void GetLocationsFromMap(LPCHARACTER ch);
	TLocationTable* GetLocationFromMap(DWORD pid, BYTE idx);
	void SendAddLocationPacket(DWORD pid, BYTE idx, DWORD globalX, DWORD globalY, DWORD localX, DWORD localY, const char* name);
public:
	SavedLocationsManager();
	~SavedLocationsManager();

	void SaveLocation(LPCHARACTER ch, BYTE idx, const char* name);
	void RenameLocation(LPCHARACTER ch, BYTE idx, const char* name);
	void LoadLocations(LPCHARACTER ch);
	void SendLocationAppendPacket(LPCHARACTER ch, BYTE idx, TLocationTable location);
	void SendLocationAppendPacket(LPCHARACTER ch, BYTE idx, TLocationTable* pLocation);
	void TeleportToLocation(LPCHARACTER ch, BYTE idx);
	void AddLocationToMap(DWORD pid, BYTE idx, TLocationTable location);
};
#endif
