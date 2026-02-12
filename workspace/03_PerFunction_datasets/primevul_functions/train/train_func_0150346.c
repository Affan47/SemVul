findInLibpath(const char *libpath, const char *backupPath)
{
	size_t backupPathLen = strlen(backupPath);
	BOOLEAN leadingColon = FALSE;
	BOOLEAN trailingColon = FALSE;
	const char *libpathdir = libpath;

	if (':' == backupPath[0]) {

		leadingColon = TRUE;
	}
	if (':' == backupPath[backupPathLen - 1]) {
		trailingColon = TRUE;
	}

	while (NULL != libpathdir) {
		if (!leadingColon) {

			while (':' == libpathdir[0]) {
				libpathdir += 1;
			}
		}
		if (0 == strncmp(libpathdir, backupPath, backupPathLen)) {
			if (('\0' == libpathdir[backupPathLen]) || (':' == libpathdir[backupPathLen]) || trailingColon) {
				return libpathdir;
			}
		}


		libpathdir = strchr(libpathdir + 1, ':');
	}
	return NULL;
}
