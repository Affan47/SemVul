eerror(const char *EINFO_RESTRICT fmt, ...)
{
	int retval;
	va_list ap;

	if (!fmt || is_really_quiet())
		return 0;
	va_start(ap, fmt);
	elogv(LOG_ERR, fmt, ap);
	retval = _eerrorvn(fmt, ap);
	va_end(ap);
	retval += fprintf(stderr, "\n");
	LASTCMD("eerror");
	return retval;
}
