LPSTR VDir::BuildEnvironmentSpace(LPSTR lpStr)
{
    int index, length;
    LPSTR lpDirStr;
    for (index = 0; index < driveCount; ++index) {
	lpDirStr = dirTableA[index];
	if (lpDirStr != NULL) {
	    lpStr[0] = '=';
	    lpStr[1] = lpDirStr[0];
	    lpStr[2] = '\0';
	    CharUpper(&lpStr[1]);
	    lpStr[2] = ':';
	    lpStr[3] = '=';
	    strcpy(&lpStr[4], lpDirStr);
	    length = strlen(lpDirStr);
	    lpStr += length + 5;
	    if (length > 3 && IsPathSep(lpStr[-2])) {
		lpStr[-2] = '\0';
		--lpStr;
	    }
	}
    }
    return lpStr;
}
