acquire_mountpoint(char **mountpointp)
{
	int rc, dacrc;
	uid_t realuid, oldfsuid;
	gid_t oldfsgid;
	char *mountpoint = NULL;


	realuid = getuid();
	if (realuid == 0) {
		dacrc = toggle_dac_capability(0, 1);
		if (dacrc)
			return dacrc;
	} else {
		oldfsuid = setfsuid(realuid);
		oldfsgid = setfsgid(getgid());
	}

	rc = chdir(*mountpointp);
	if (rc) {
		fprintf(stderr, "Couldn't chdir to %s: %s\n", *mountpointp,
			strerror(errno));
		rc = EX_USAGE;
		goto restore_privs;
	}

	mountpoint = realpath(".", NULL);
	if (!mountpoint) {
		fprintf(stderr, "Unable to resolve %s to canonical path: %s\n",
			*mountpointp, strerror(errno));
		rc = EX_SYSERR;
	}

	*mountpointp = mountpoint;
restore_privs:
	if (realuid == 0) {
		dacrc = toggle_dac_capability(0, 0);
		if (dacrc)
			rc = rc ? rc : dacrc;
	} else {
		uid_t __attribute__((unused)) uignore = setfsuid(oldfsuid);
		gid_t __attribute__((unused)) gignore = setfsgid(oldfsgid);
	}

	if (rc)
		free(mountpoint);

	return rc;
}
