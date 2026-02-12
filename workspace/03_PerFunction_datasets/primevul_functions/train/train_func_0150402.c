backupLibpath(J9LibpathBackup *libpathBackup, size_t origLibpathLen)
{
	const char *curLibpath = getenv("LIBPATH");

	libpathBackup->fullpath = NULL;
	libpathBackup->j9prefixLen = 0;

	if (NULL != curLibpath) {

		libpathBackup->j9prefixLen = strlen(curLibpath) - origLibpathLen;


		if (libpathBackup->j9prefixLen > 0) {
			libpathBackup->fullpath = strdup(curLibpath);
			if (NULL == libpathBackup->fullpath) {
				fprintf(stderr, "backupLibpath: strdup() failed to allocate memory for the backup path\n");
				abort();
			}
		}
	}
}
