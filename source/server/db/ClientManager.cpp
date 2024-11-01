//find:
default:
	sys_err("Unknown header (header: %d handle: %d length: %d)", header, dwHandle, dwLength);
	break;

//add above:
#ifdef ENABLE_SAVED_LOCATIONS
	case HEADER_GD_ADD_LOCATION:
		AddLocation((TPacketAddLocation*) data);
		break;
#endif	

//add at the bottom of the file:
#ifdef ENABLE_SAVED_LOCATIONS
struct FAddLocation
{
	FAddLocation(DWORD pid, BYTE idx, DWORD globalX, DWORD globalY, DWORD localX, DWORD localY, const char* name)
	{
		p.dwPID = pid;
		p.byIdx = idx;
		p.dwGlobalX = globalX;
		p.dwGlobalY = globalY;
		p.dwLocalX = localX;
		p.dwLocalY = localY;
		strlcpy(p.szName, name, sizeof(p.szName));
	}

	void operator ()(CPeer* peer)
	{
		peer->EncodeHeader(HEADER_DG_ADD_LOCATION, 0, sizeof(TPacketAddLocation));
		peer->Encode(&p, sizeof(TPacketAddLocation));
	}

	TPacketAddLocation p{};
};

void CClientManager::AddLocation(TPacketAddLocation* p)
{
	CClientManager::Instance().for_each_peer(FAddLocation(p->dwPID, p->byIdx, p->dwGlobalX, p->dwGlobalY, p->dwLocalX, p->dwLocalY, p->szName));
}
#endif