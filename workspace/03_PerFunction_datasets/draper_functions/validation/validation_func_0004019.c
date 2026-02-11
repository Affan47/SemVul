LCreader(CHANNEL *cp)
{
    int		fd;
    CHANNEL	*new;

    if (cp != LCchan) {
	syslog(L_ERROR, "%s internal LCreader wrong channel 0x%p not 0x%p",
	    LogName, (void *)cp, (void *)LCchan);
	return;
    }

    if ((fd = accept(cp->fd, NULL, NULL)) < 0) {
	syslog(L_ERROR, "%s cant accept CCreader %m", LogName);
	return;
    }
    if ((new = NCcreate(fd, false, true)) != NULL) {
	memset( &new->Address, 0, sizeof( new->Address ) );
	syslog(L_NOTICE, "%s connected %d", "localhost", new->fd);
	NCwritereply(new, (char *)NCgreeting);
    }
}
