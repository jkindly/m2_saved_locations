//add at the end of the file, just before: }

#ifdef ENABLE_SAVED_LOCATIONS
	public:
		bool RecvLocationAppend();
		bool SendLocationSave(BYTE index, const char* name);
		bool SendLocationRename(BYTE index, const char* name);
#endif