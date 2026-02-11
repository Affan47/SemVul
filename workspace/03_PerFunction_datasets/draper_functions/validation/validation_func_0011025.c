swarn(const char *fmt, ...)
#else
swarn(fmt, va_alist)
	const char *fmt;
	va_dcl
#endif
{

	if (fmt != NULL) {
		va_list ap;
		char buf[2048];
		size_t bufused;

#ifdef STDC_HEADERS

		va_start(ap, fmt);
#else
		va_start(ap);
#endif

		bufused = vsnprintf(buf, sizeof(buf), fmt, ap);

		bufused += snprintfn(&buf[bufused], sizeof(buf) - bufused,
		": %s (errno = %d)", strerror(errno), errno);

		slog(LOG_ERR, "%s", buf);


		va_end(ap);
	}
}
