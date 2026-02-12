JVM_UcsOpen(const jchar* filename, jint flags, jint mode)
{
#ifdef WIN32
	WCHAR *prefixStr;
	DWORD prefixLen ;

	DWORD fullPathLen, rc;
	WCHAR* longFilename;
	DWORD newFlags, disposition, attributes;
	HANDLE hFile;
	jint returnVal;
	int isUNC = FALSE;
	int isDosDevices = FALSE;

	if (filename==NULL) {
		Trc_SC_UcsOpen_nullName();
		return -1;
	}

	Trc_SC_UcsOpen_Entry(filename, flags, mode);

	if (filename[0] == L'\\' && filename[1] == L'\\') {

		if (filename[2] == L'?') {
			prefixStr = L"";
			prefixLen = 0;
		} else if (filename[2] == L'.' && filename[3] == L'\\') {
			isDosDevices = TRUE;
			prefixStr = L"";
			prefixLen = 0;
		} else {
			isUNC = TRUE;
			prefixStr = L"\\\\?\\UNC";
			prefixLen = (sizeof(L"\\\\?\\UNC") / sizeof(WCHAR)) - 1;
		}
	} else {
		prefixStr = L"\\\\?\\";
		prefixLen = (sizeof(L"\\\\?\\") / sizeof(WCHAR)) - 1;
	}


	fullPathLen = GetFullPathNameW(filename, 0, NULL, NULL);

	if (filename[0] == L'\0' || filename[1] == L'\0') fullPathLen += 3;

	if (isDosDevices) fullPathLen += 4;
	longFilename = malloc(sizeof(WCHAR) * (prefixLen+fullPathLen));


	wcscpy(longFilename, prefixStr);


	if (isUNC) prefixLen--;
	rc = GetFullPathNameW(filename, fullPathLen, &longFilename[prefixLen], NULL);
	if (!rc || rc >= fullPathLen) {
		Trc_SC_UcsOpen_GetFullPathNameW(rc);
		return -1;
	}

	if (isUNC) longFilename[prefixLen] = L'C';

	if (!flags || (flags & O_RDONLY) || (flags == O_TEMPORARY))
		newFlags = GENERIC_READ;
	else if (flags & O_WRONLY)
		newFlags = GENERIC_WRITE;
	else if (flags & O_RDWR)
		newFlags = (GENERIC_READ | GENERIC_WRITE);

	if (flags & O_TRUNC)
		disposition = CREATE_ALWAYS;
	else if (flags & O_CREAT)
		disposition = OPEN_ALWAYS;
	else
		disposition = OPEN_EXISTING;

	if (flags & (O_SYNC | O_DSYNC))
		attributes = FILE_FLAG_WRITE_THROUGH;
	else
		attributes = FILE_ATTRIBUTE_NORMAL;

	if (flags & O_TEMPORARY)
		attributes |= FILE_FLAG_DELETE_ON_CLOSE;

	hFile = CreateFileW(longFilename, newFlags, mode, NULL, disposition, attributes, NULL);
	returnVal = _open_osfhandle((UDATA)hFile, flags);

	if (returnVal<0) {
		Trc_SC_UcsOpen_error(returnVal);
	} else {
		Trc_SC_UcsOpen_Exit(returnVal);
	}

	free(longFilename);

	if (returnVal>=0)
		return returnVal;
	else if (errno==EEXIST)
		return JVM_EEXIST;
	else
		return -1;
#else
	printf("JVM_UcsOpen is only supported on Win32 platforms\n");
	return -1;
#endif
}
