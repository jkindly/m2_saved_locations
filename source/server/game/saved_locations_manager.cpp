#include "stdafx.h"
#include "saved_locations_manager.h"
#include "char.h"
#include "db.h"
#include "config.h"
#include "sectree_manager.h"
#include "desc.h"
#include "desc_client.h"

SavedLocationsManager::SavedLocationsManager()
{
	m_MapLocation.clear();
}
SavedLocationsManager::~SavedLocationsManager()
{
	m_MapLocation.clear();
}

void SavedLocationsManager::RenameLocation(LPCHARACTER ch, BYTE idx, const char* name)
{
	if (!ch)
	{
		return;
	}

	if (idx < 0 || idx >= MAX_SAVED_LOCATIONS)
	{
		return;
	}

	if (strlen(name) > MAX_SAVED_LOCATION_NAME_LENGTH)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Location name is too long."));
		return;
	}

	static char escapedName[MAX_SAVED_LOCATION_NAME_LENGTH * 2 + 1];
	DBManager::instance().EscapeString(escapedName, sizeof(escapedName), name, strlen(name));

	char szQuery[QUERY_MAX_LEN];
	snprintf(szQuery, sizeof(szQuery),
		"UPDATE `player`.`saved_locations` SET `name` = '%s' WHERE `pid` = %d and `idx` = %d",
		name,
		ch->GetPlayerID(),
		idx
	);

	std::unique_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery(szQuery));

	if (pMsg->Get()->uiAffectedRows <= 0)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Location rename error."));
		return;
	}

	TLocationTable* location = SavedLocationsManager::Instance().GetLocationFromMap(ch->GetPlayerID(), idx);

	if (!location)
	{
		SavedLocationsManager::Instance().LoadLocations(ch);
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Location save success."));
		return;
	}

	snprintf(location->szName, sizeof(location->szName), "%s", name);

	SavedLocationsManager::Instance().AddLocationToMap(ch->GetPlayerID(), idx, *location);
	SavedLocationsManager::Instance().SendAddLocationPacket(
		ch->GetPlayerID(),
		idx,
		location->dwGlobalX,
		location->dwGlobalY,
		location->dwLocalX,
		location->dwLocalY,
		location->szName
	);

	SendLocationAppendPacket(ch, idx, location);

	ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Location save success."));
}

void SavedLocationsManager::SaveLocation(LPCHARACTER ch, BYTE idx, const char* name)
{
	if (!ch)
	{
		return;
	}

	if (idx < 0 || idx >= MAX_SAVED_LOCATIONS)
	{
		return;
	}

	if (strlen(name) > MAX_SAVED_LOCATION_NAME_LENGTH)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Location name is too long."));
		return;
	}

	if (ch->IsObserverMode())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Location blocked in observer mode."));
		return;
	}

	if (ch->GetDungeon())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Location blocked dungeon."));
		return;
	}

	if (g_bChannel == 99)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Location blocked ch99."));
		return;
	}

	static char escapedName[MAX_SAVED_LOCATION_NAME_LENGTH * 2 + 1];
	DBManager::instance().EscapeString(escapedName, sizeof(escapedName), name, strlen(name));

	DWORD global_x = 0, global_y = 0, local_x = 0, local_y = 0;
	PIXEL_POSITION pos = ch->GetXYZ();

	LPSECTREE_MAP locationMap = SECTREE_MANAGER::instance().GetMap(ch->GetMapIndex());

	global_x = pos.x;
	global_y = pos.y;
	local_x = (ch->GetX() - locationMap->m_setting.iBaseX) / 100;
	local_y = (ch->GetY() - locationMap->m_setting.iBaseY) / 100;

	char szQuery[QUERY_MAX_LEN];
	snprintf(szQuery, sizeof(szQuery), 
		"REPLACE INTO `player`.`saved_locations` (`pid`, `idx`, `global_x`, `global_y`, `local_x`, `local_y`, `name`) VALUES(%d, %d, %d, %d, %d, %d, '%s');", 
		ch->GetPlayerID(),
		idx,
		global_x,
		global_y,
		local_x,
		local_y,
		escapedName
	);

	std::unique_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery(szQuery));

	if (pMsg->Get()->uiAffectedRows <= 0)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Location save error."));
		return;
	}

	TLocationTable location{};
	location.dwGlobalX = global_x;
	location.dwGlobalY = global_y;
	location.dwLocalX = local_x;
	location.dwLocalY = local_y;
	strlcpy(location.szName, escapedName, sizeof(location.szName));

	SavedLocationsManager::Instance().AddLocationToMap(ch->GetPlayerID(), idx, location);
	SavedLocationsManager::Instance().SendAddLocationPacket(
		ch->GetPlayerID(),
		idx,
		location.dwGlobalX,
		location.dwGlobalY,
		location.dwLocalX,
		location.dwLocalY,
		location.szName
	);

	SendLocationAppendPacket(ch, idx, location);

	ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Location save success."));
}

void SavedLocationsManager::LoadLocations(LPCHARACTER ch)
{
	if (!ch)
	{
		return;
	}

	if (SavedLocationsManager::Instance().IsLocationsLoaded(ch->GetPlayerID()))
	{
		SavedLocationsManager::Instance().GetLocationsFromMap(ch);

		if (test_server)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "[TEST SERVER] Loaded from cache");
		}

		ch->ChatPacket(CHAT_TYPE_COMMAND, "open_locations");

		return;
	}

	char szQuery[QUERY_MAX_LEN];
	snprintf(szQuery, sizeof(szQuery),
		"SELECT `idx`, `global_x`, `global_y`, `local_x`, `local_y`, `name` FROM `player`.`saved_locations` WHERE `pid` = %d",
		ch->GetPlayerID()
	);

	std::unique_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery(szQuery));

	if (pMsg->Get()->uiNumRows > 0)
	{
		MYSQL_ROW row;

		while ((row = mysql_fetch_row(pMsg->Get()->pSQLResult)) != NULL)
		{
			TLocationTable location{};

			BYTE idx = 0;
			str_to_number(idx, row[0]);
			str_to_number(location.dwGlobalX, row[1]);
			str_to_number(location.dwGlobalY, row[2]);
			str_to_number(location.dwLocalX, row[3]);
			str_to_number(location.dwLocalY, row[4]);
			snprintf(location.szName, sizeof(location.szName), "%s", row[5]);

			SavedLocationsManager::Instance().AddLocationToMap(ch->GetPlayerID(), idx, location);
			SavedLocationsManager::Instance().SendAddLocationPacket(
				ch->GetPlayerID(),
				idx,
				location.dwGlobalX,
				location.dwGlobalY,
				location.dwLocalX,
				location.dwLocalY,
				location.szName
			);

			SavedLocationsManager::Instance().SendLocationAppendPacket(ch, idx, location);
		}
	}

	ch->ChatPacket(CHAT_TYPE_COMMAND, "open_locations");

	if (test_server)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[TEST SERVER] Loaded from DB");
	}
}

void SavedLocationsManager::SendLocationAppendPacket(LPCHARACTER ch, BYTE idx, TLocationTable location)
{
	if (!ch)
	{
		return;
	}

	if (!ch->GetDesc())
	{
		return;
	}

	TPacketGCLocationAppend p{};
	p.byHeader = HEADER_GC_LOCATION_APPEND;
	p.byIdx = idx;
	p.dwGlobalX = location.dwGlobalX;
	p.dwGlobalY = location.dwGlobalY;
	p.dwLocalX = location.dwLocalX;
	p.dwLocalY = location.dwLocalY;
	strlcpy(p.szName, location.szName, sizeof(p.szName));
	ch->GetDesc()->Packet(&p, sizeof(TPacketGCLocationAppend));
}

void SavedLocationsManager::SendLocationAppendPacket(LPCHARACTER ch, BYTE idx, TLocationTable* pLocation)
{
	if (!ch)
	{
		return;
	}

	if (!ch->GetDesc())
	{
		return;
	}

	TPacketGCLocationAppend p{};
	p.byHeader = HEADER_GC_LOCATION_APPEND;
	p.byIdx = idx;
	p.dwGlobalX = pLocation->dwGlobalX;
	p.dwGlobalY = pLocation->dwGlobalY;
	p.dwLocalX = pLocation->dwLocalX;
	p.dwLocalY = pLocation->dwLocalY;
	strlcpy(p.szName, pLocation->szName, sizeof(p.szName));
	ch->GetDesc()->Packet(&p, sizeof(TPacketGCLocationAppend));
}

void SavedLocationsManager::TeleportToLocation(LPCHARACTER ch, BYTE idx)
{
	if (!ch)
	{
		return;
	}

	if (!ch->CanWarp())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Must wait before teleport."));
		return;
	}

	TLocationTable* location = SavedLocationsManager::Instance().GetLocationFromMap(ch->GetPlayerID(), idx);

	if (!location)
	{
		SavedLocationsManager::Instance().LoadLocations(ch);
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Location not found."));
		return;
	}

	DWORD map_index = SECTREE_MANAGER::instance().GetMapIndex(location->dwGlobalX, location->dwGlobalY);

	if (map_index == 0)
	{
		return;
	}

	bool isRequiredItemMap = false;
	bool canWarpFromDragonLair = ch->GetDungeon() && (ch->GetMapIndex() / 10000) == 208 && (map_index == 72 || map_index == 73);

	if (IS_REQUIRED_ITEM_MAP(map_index))
	{
		isRequiredItemMap = true;
	}
	
	if ((ch->GetMapIndex() == 72 || ch->GetMapIndex() == 73) && (map_index == 72 || map_index == 73))
	{
		isRequiredItemMap = false;
	}

	if (ch->GetMapIndex() == 71 && map_index == 71)
	{
		isRequiredItemMap = false;
	}

	if (canWarpFromDragonLair)
	{
		isRequiredItemMap = false;
	}

	if (isRequiredItemMap && ch->GetMapIndex() != map_index)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "Location must be the same map index.");
		return;
	}

	int x = 0;
	int y = 0;

	double nDist = 0;
	const double nDistant = 5000.0;

	x = location->dwGlobalX - ch->GetX();
	y = location->dwGlobalY - ch->GetY();

	nDist = sqrt(pow((float)x, 2) + pow((float)y, 2));

	if (nDistant > nDist)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Location too close."));

		if (test_server)
			ch->ChatPacket(CHAT_TYPE_INFO, "PossibleDistant %f nNowDist %f", nDistant, nDist);

		return;
	}

	ch->WarpSet(location->dwGlobalX, location->dwGlobalY);
}

void SavedLocationsManager::SendAddLocationPacket(DWORD pid, BYTE idx, DWORD globalX, DWORD globalY, DWORD localX, DWORD localY, const char* name)
{
	TPacketAddLocation p{};
	p.dwPID = pid;
	p.byIdx = idx;
	p.dwGlobalX = globalX;
	p.dwGlobalY = globalY;
	p.dwLocalX = localX;
	p.dwLocalY = localY;
	strlcpy(p.szName, name, sizeof(p.szName));

	db_clientdesc->DBPacket(HEADER_GD_ADD_LOCATION, 0, &p, sizeof(TPacketAddLocation));
}

TLocationTable* SavedLocationsManager::GetLocationFromMap(DWORD pid, BYTE idx)
{
	if (m_MapLocation.find(pid) == m_MapLocation.end())
	{
		return nullptr;
	}

	if (m_MapLocation[pid].find(idx) == m_MapLocation[pid].end())
	{
		return nullptr;
	}

	return &m_MapLocation[pid][idx];
}

void SavedLocationsManager::GetLocationsFromMap(LPCHARACTER ch)
{
	if (!ch)
	{
		return;
	}

	DWORD pid = ch->GetPlayerID();

	if (m_MapLocation.find(pid) == m_MapLocation.end())
	{
		return;
	}

	for (auto const& it : m_MapLocation[pid])
	{
		SavedLocationsManager::Instance().SendLocationAppendPacket(ch, it.first, it.second);
	}
}

bool SavedLocationsManager::IsLocationsLoaded(DWORD pid)
{
	return m_MapLocation.find(pid) != m_MapLocation.end();
}

void SavedLocationsManager::AddLocationToMap(DWORD pid, BYTE idx, TLocationTable location)
{
	auto& innerMap = m_MapLocation[pid];
	innerMap[idx] = location;
}