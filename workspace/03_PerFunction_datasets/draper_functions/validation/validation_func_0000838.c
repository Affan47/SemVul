setdevname(cp)
    char *cp;
{
    struct stat statbuf;
    char *tty, *ttyname();
    char dev[MAXPATHLEN];

    if (strncmp("/dev/", cp, 5) != 0) {
	strcpy(dev, "/dev/");
	strncat(dev, cp, MAXPATHLEN - 5);
	dev[MAXPATHLEN-1] = 0;
	cp = dev;
    }


    if (stat(cp, &statbuf) < 0) {
	if (errno == ENOENT)
	    return 0;
	syslog(LOG_ERR, cp);
	return -1;
    }

    (void) strncpy(devnam, cp, MAXPATHLEN);
    devnam[MAXPATHLEN-1] = 0;
    default_device = FALSE;

    return 1;
}
