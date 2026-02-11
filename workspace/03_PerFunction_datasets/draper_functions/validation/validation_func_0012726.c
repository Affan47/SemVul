check_exe_name(const char *val, int line)
{
	struct stat buf;

	if (val == NULL) {
		syslog(LOG_ERR, "Executable path needed for line %d", line);
		return -1;
	}

	if (*val != '/') {
		syslog(LOG_ERR, "Absolute path needed for %s - line %d",
			val, line);
		return -1;
	}

	if (stat(val, &buf) < 0) {
		syslog(LOG_ERR, "Unable to stat %s (%s) - line %d", val,
			strerror(errno), line);
		return -1;
	}
	if (!S_ISREG(buf.st_mode)) {
		syslog(LOG_ERR, "%s is not a regular file - line %d", val,
			line);
		return -1;
	}
	if (buf.st_uid != 0) {
		syslog(LOG_ERR, "%s is not owned by root - line %d", val,
			line);
		return -1;
	}
	if ((buf.st_mode & (S_IRWXU|S_IRWXG|S_IWOTH)) !=
			   (S_IRWXU|S_IRGRP|S_IXGRP)) {
		syslog(LOG_ERR, "%s permissions should be 0750 - line %d", val,
			line);
		return -1;
	}
	return 0;
}
