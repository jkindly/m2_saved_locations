//find:
void initnet()

//add above:
#ifdef ENABLE_SAVED_LOCATIONS
PyObject* netSendSaveLocationPacket(PyObject* poSelf, PyObject* poArgs)
{
	int idx;
	if (!PyTuple_GetInteger(poArgs, 0, &idx))
		return Py_BuildException();

	char* name;
	if (!PyTuple_GetString(poArgs, 1, &name))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendLocationSave(idx, name);

	return Py_BuildNone();
}

PyObject* netSendRenameLocationPacket(PyObject* poSelf, PyObject* poArgs)
{
	int idx;
	if (!PyTuple_GetInteger(poArgs, 0, &idx))
		return Py_BuildException();

	char* name;
	if (!PyTuple_GetString(poArgs, 1, &name))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendLocationRename(idx, name);

	return Py_BuildNone();
}
#endif

//find:
		{ "SendSelectItemPacket",					netSendSelectItemPacket,					METH_VARARGS },

//add below:
#ifdef ENABLE_SAVED_LOCATIONS
		{ "SendSaveLocationPacket",					netSendSaveLocationPacket,					METH_VARARGS },
		{ "SendRenameLocationPacket",				netSendRenameLocationPacket,				METH_VARARGS },
#endif