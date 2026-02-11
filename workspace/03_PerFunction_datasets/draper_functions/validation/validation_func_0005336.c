lastlog_filetype(char *filename)
{
	struct stat st;

	if (stat(filename, &st) != 0) {
		dropbear_log(LOG_WARNING, "lastlog_perform_login: Couldn't stat %s: %s", filename,
			strerror(errno));
		return 0;
	}
	if (S_ISDIR(st.st_mode))
		return LL_DIR;
	else if (S_ISREG(st.st_mode))
		return LL_FILE;
	else
		return LL_OTHER;
}
