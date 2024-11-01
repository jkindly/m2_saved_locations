//find:
Set(HEADER_GC_LOGIN_KEY, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCLoginKey), STATIC_SIZE_PACKET));

//add below:
#ifdef ENABLE_SAVED_LOCATIONS
			Set(HEADER_GC_LOCATION_APPEND, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCLocationAppend), STATIC_SIZE_PACKET));
#endif
