vmod_syslog(struct sess *sp, int fac, const char *fmt, ...)
{
	char buf[8192], *p;
	va_list ap;

	(void)sp;
	va_start(ap, fmt);
	p = VRT_StringList(buf, sizeof buf, fmt, ap);
	va_end(ap);
	if (p != NULL)
		syslog(fac, "%s", buf);
}
