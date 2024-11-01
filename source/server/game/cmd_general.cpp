//add as the last #include at the top of the file:
#ifdef ENABLE_SAVED_LOCATIONS
#include "saved_locations_manager.h"
#endif

//add at the bottom of the file:
#ifdef ENABLE_SAVED_LOCATIONS
ACMD(do_load_locations)
{
	if (!ch)
	{
		return;
	}

	SavedLocationsManager::Instance().LoadLocations(ch);
}

ACMD(do_save_location)
{
	if (!ch)
	{
		return;
	}

	char arg1[256];
	char arg2[256];

	two_arguments(argument, arg1, sizeof(arg1), arg2, sizeof(arg2));

	if (!*arg1 || !*arg2)
	{
		return;
	}

	BYTE idx;
	str_to_number(idx, arg1);

	if (idx < 0 || idx >= MAX_SAVED_LOCATIONS)
	{
		return;
	}

	if (strlen(arg2) > MAX_SAVED_LOCATION_NAME_LENGTH)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Location name is too long."));
		return;
	}

	SavedLocationsManager::Instance().SaveLocation(ch, idx, arg2);
}

ACMD(do_teleport_to_location)
{
	if (!ch)
	{
		return;
	}

	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	if (!*arg1 || !isdigit(*arg1))
		return;

	BYTE idx;
	str_to_number(idx, arg1);

	if (idx < 0 || idx >= MAX_SAVED_LOCATIONS)
	{
		return;
	}

	SavedLocationsManager::Instance().TeleportToLocation(ch, idx);
}
#endif