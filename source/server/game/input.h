//find:
void Refine(LPCHARACTER ch, const char* c_pData);

//add below:
#ifdef ENABLE_SAVED_LOCATIONS
		void LocationSave(LPCHARACTER ch, const char* data);
		void LocationRename(LPCHARACTER ch, const char* data);
#endif

//find:
void RespondChannelStatus(LPDESC desc, const char* pcData);

//add below:
#ifdef ENABLE_SAVED_LOCATIONS
	void AddLocation(const char* c_pData);
#endif