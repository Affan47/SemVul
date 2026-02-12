save_config(
	struct recvbuf *rbufp,
	int restrict_mask
	)
{
#ifdef SAVECONFIG
	static const char savedconfig_eq[] = "savedconfig=";

	char filespec[128];
	char filename[128];
	char fullpath[512];
	char savedconfig[sizeof(savedconfig_eq) + sizeof(filename)];
	time_t now;
	int fd;
	FILE *fptr;
	int prc;
	size_t reqlen;
#endif

	if (RES_NOMODIFY & restrict_mask) {
		ctl_printf("%s", "saveconfig prohibited by restrict ... nomodify");
		ctl_flushpkt(0);
		NLOG(NLOG_SYSINFO)
			msyslog(LOG_NOTICE,
				"saveconfig from %s rejected due to nomodify restriction",
				stoa(&rbufp->recv_srcadr));
		sys_restricted++;
		return;
	}

#ifdef SAVECONFIG
	if (NULL == saveconfigdir) {
		ctl_printf("%s", "saveconfig prohibited, no saveconfigdir configured");
		ctl_flushpkt(0);
		NLOG(NLOG_SYSINFO)
			msyslog(LOG_NOTICE,
				"saveconfig from %s rejected, no saveconfigdir",
				stoa(&rbufp->recv_srcadr));
		return;
	}


	reqlen = (size_t)(reqend - reqpt);
	if (0 != reqlen) {
		char * nulpos = (char*)memchr(reqpt, 0, reqlen);
		if (NULL != nulpos)
			reqlen = (size_t)(nulpos - reqpt);
	}
	if (0 == reqlen)
		return;
	if (reqlen >= sizeof(filespec)) {
		ctl_printf("saveconfig exceeded maximum raw name length (%u)",
			   (u_int)sizeof(filespec));
		ctl_flushpkt(0);
		msyslog(LOG_NOTICE,
			"saveconfig exceeded maximum raw name length from %s",
			stoa(&rbufp->recv_srcadr));
		return;
	}


	memcpy(filespec, reqpt, reqlen);
	filespec[reqlen] = '\0';


	time(&now);
	if (0 == strftime(filename, sizeof(filename), filespec,
			  localtime(&now)))
	{


		strlcpy(filename, filespec, sizeof(filename));
	}


	if (!is_safe_filename(filename)) {
		ctl_printf("saveconfig rejects unsafe file name '%s'",
			   filename);
		ctl_flushpkt(0);
		msyslog(LOG_NOTICE,
			"saveconfig rejects unsafe file name from %s",
			stoa(&rbufp->recv_srcadr));
		return;
	}


	prc = snprintf(fullpath, sizeof(fullpath), "%s%s",
		       saveconfigdir, filename);
	if (prc < 0 || prc >= sizeof(fullpath)) {
		ctl_printf("saveconfig exceeded maximum path length (%u)",
			   (u_int)sizeof(fullpath));
		ctl_flushpkt(0);
		msyslog(LOG_NOTICE,
			"saveconfig exceeded maximum path length from %s",
			stoa(&rbufp->recv_srcadr));
		return;
	}

	fd = open(fullpath, O_CREAT | O_TRUNC | O_WRONLY,
		  S_IRUSR | S_IWUSR);
	if (-1 == fd)
		fptr = NULL;
	else
		fptr = fdopen(fd, "w");

	if (NULL == fptr || -1 == dump_all_config_trees(fptr, 1)) {
		ctl_printf("Unable to save configuration to file '%s'",
			   filename);
		msyslog(LOG_ERR,
			"saveconfig %s from %s failed", filename,
			stoa(&rbufp->recv_srcadr));
	} else {
		ctl_printf("Configuration saved to '%s'", filename);
		msyslog(LOG_NOTICE,
			"Configuration saved to '%s' (requested by %s)",
			fullpath, stoa(&rbufp->recv_srcadr));


		snprintf(savedconfig, sizeof(savedconfig), "%s%s",
			 savedconfig_eq, filename);
		set_sys_var(savedconfig, strlen(savedconfig) + 1, RO);
	}

	if (NULL != fptr)
		fclose(fptr);
#else
	ctl_printf("%s",
		   "saveconfig unavailable, configured with --disable-saveconfig");
#endif
	ctl_flushpkt(0);
}
