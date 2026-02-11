delete_temp_dir(const char *dirname) {
	char filename[MAX_PATH_LEN];
	struct stat buf;

	if (!dirname[0])
		return;

	snprintf(filename, MAX_PATH_LEN, "%s%s", dirname, CPUFREQD_SOCKET);


	if (stat(filename, &buf) != 0) {
		clog(LOG_ERR, "Couldn't stat %s: %s\n", filename, strerror(errno));
	} else if (!S_ISSOCK(buf.st_mode)) {
		clog(LOG_ERR, "%s not a socket!\n", filename);
	} else if (unlink(filename) != 0) {
		clog(LOG_ERR, "Couldn't delete %s: %s\n", filename, strerror(errno));
	} else {
		clog(LOG_INFO, "%s deleted.\n", filename);
	}


	if (rmdir(dirname) != 0) {
		clog(LOG_ERR, "Couldn't delete %s: %s\n", dirname, strerror(errno));
	} else {
		clog(LOG_INFO, "%s deleted.\n", dirname);
	}
}
