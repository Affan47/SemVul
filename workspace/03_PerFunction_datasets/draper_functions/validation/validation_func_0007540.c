elogv(int level, const char *EINFO_RESTRICT fmt, va_list ap)
{
	char *e = getenv("EINFO_LOG");
	va_list apc;

	if (fmt && e) {
		closelog();
		openlog(e, LOG_PID, LOG_DAEMON);
		va_copy(apc, ap);
		vsyslog(level, fmt, apc);
		va_end(apc);
		closelog();
	}
}
