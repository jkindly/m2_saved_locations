//find:
Set(HEADER_CG_REFINE, sizeof(TPacketCGRefine), "Refine", true);

//add below:
#ifdef ENABLE_SAVED_LOCATIONS
	Set(HEADER_CG_SAVE_LOCATION, sizeof(TPacketCGSaveLocation), "LocationSave", true);
	Set(HEADER_CG_RENAME_LOCATION, sizeof(TPacketCGRenameLocation), "LocationRename", true);
#endif