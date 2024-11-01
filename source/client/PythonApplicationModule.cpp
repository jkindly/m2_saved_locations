//add at the end of the file, just before: {

#ifdef ENABLE_SAVED_LOCATIONS
	PyModule_AddIntConstant(poModule, "ENABLE_SAVED_LOCATIONS", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_SAVED_LOCATIONS", 0);
#endif