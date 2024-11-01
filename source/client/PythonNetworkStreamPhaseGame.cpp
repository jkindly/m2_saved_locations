//find:
			default:
				ret = RecvDefaultPacket(header);
				break;
				
//add below:

#ifdef ENABLE_SAVED_LOCATIONS
			case HEADER_GC_LOCATION_APPEND:
				ret = RecvLocationAppend();
				break;
#endif	

//add at the bottom of the file:
#ifdef ENABLE_SAVED_LOCATIONS
bool CPythonNetworkStream::SendLocationSave(BYTE index, const char* name)
{
	TPacketCGSaveLocation packet{};
	packet.byHeader = HEADER_CG_SAVE_LOCATION;
	packet.byIdx = index;
	strncpy(packet.szName, name, sizeof(packet.szName) - 1);

	if (!Send(sizeof(packet), &packet))
		return false;

	return SendSequence();
}

bool CPythonNetworkStream::SendLocationRename(BYTE index, const char* name)
{
	TPacketCGRenameLocation packet{};
	packet.byHeader = HEADER_CG_RENAME_LOCATION;
	packet.byIdx = index;
	strncpy(packet.szName, name, sizeof(packet.szName) - 1);

	if (!Send(sizeof(packet), &packet))
		return false;

	return SendSequence();
}

bool CPythonNetworkStream::RecvLocationAppend()
{
	TPacketGCLocationAppend packet{};

	if (!Recv(sizeof(TPacketGCLocationAppend), &packet))
		return false;

	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_Location_Append", Py_BuildValue("(iiiiis)",
		packet.byIdx,
		packet.dwGlobalX,
		packet.dwGlobalY,
		packet.dwLocalX,
		packet.dwLocalY,
		packet.szName
	));

	return true;
}
#endif