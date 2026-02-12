char *VDir::MapPathA(const char *pInName)
{


    int driveIndex;
    char szBuffer[(MAX_PATH+1)*2];
    char szlBuf[MAX_PATH+1];
    int length = strlen(pInName);

    if (!length)
	return (char*)pInName;

    if (length > MAX_PATH) {
	strncpy(szlBuf, pInName, MAX_PATH);
	if (IsPathSep(pInName[0]) && !IsPathSep(pInName[1])) {

	    szlBuf[MAX_PATH-2] = '\0';
	}
	else
	    szlBuf[MAX_PATH] = '\0';
	pInName = szlBuf;
    }


    if (length > 1 && pInName[1] == ':') {

	if (length > 2 && IsPathSep(pInName[2])) {

	    DoGetFullPathNameA((char*)pInName, sizeof(szLocalBufferA), szLocalBufferA);
	}
	else {

            driveIndex = DriveIndex(*pInName);
            if (driveIndex < 0 || driveIndex >= driveLetterCount)
                return (char *)pInName;
	    strcpy(szBuffer, GetDirA(driveIndex));
	    strcat(szBuffer, &pInName[2]);
	    if(strlen(szBuffer) > MAX_PATH)
		szBuffer[MAX_PATH] = '\0';

	    DoGetFullPathNameA(szBuffer, sizeof(szLocalBufferA), szLocalBufferA);
	}
    }
    else {

	if (length > 1 && IsPathSep(pInName[1]) && IsPathSep(pInName[0])) {

	    DoGetFullPathNameA((char*)pInName, sizeof(szLocalBufferA), szLocalBufferA);
	}
	else {
	    strcpy(szBuffer, GetDefaultDirA());
	    if (IsPathSep(pInName[0])) {

		strcpy(&szBuffer[2], pInName);
		DoGetFullPathNameA(szBuffer, sizeof(szLocalBufferA), szLocalBufferA);
	    }
	    else {

		if (IsSpecialFileName(pInName)) {
		    return (char*)pInName;
		}
		else {
		    strcat(szBuffer, pInName);
		    if (strlen(szBuffer) > MAX_PATH)
			szBuffer[MAX_PATH] = '\0';

		    DoGetFullPathNameA(szBuffer, sizeof(szLocalBufferA), szLocalBufferA);
		}
	    }
	}
    }

    return szLocalBufferA;
}
