ewendv(int retval, const char *EINFO_RESTRICT fmt, ...)
{
	va_list ap;

	if (!is_verbose())
		return 0;
	va_start(ap, fmt);
	_do_eend("ewendv", retval, fmt, ap);
	va_end(ap);
	LASTCMD("ewendv");
	return retval;
}
