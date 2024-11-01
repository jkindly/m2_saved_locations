//find:
TItemIDRangeTable GetItemRange() { return m_itemRange; }

//add below:
#ifdef ENABLE_SAVED_LOCATIONS
public:
	void AddLocation(TPacketAddLocation* p);
#endif