//find:
struct command_info cmd_info[] =

//add above:
#ifdef ENABLE_SAVED_LOCATIONS
ACMD(do_load_locations);
ACMD(do_save_location);
ACMD(do_teleport_to_location);
#endif

//find:
{ "\n",		NULL,			0,			POS_DEAD,	GM_IMPLEMENTOR	}

//add above:
#ifdef ENABLE_SAVED_LOCATIONS
	{ "save_location",			do_save_location,			0,			POS_DEAD,	GM_PLAYER },
	{ "load_locations",			do_load_locations,			0,			POS_DEAD,	GM_PLAYER },
	{ "teleport_to_location",	do_teleport_to_location,	0,			POS_DEAD,	GM_PLAYER },
#endif