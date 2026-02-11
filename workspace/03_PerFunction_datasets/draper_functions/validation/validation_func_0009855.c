log_verbose(const char *fmt, ...)
{
	va_list	ap;
#ifdef USE_DEBUG
	int	i;
#endif

	if (verbose_logging == 0)
		return;

#ifdef USE_DEBUG
	for (i = 0; i < LOG_ENDCLASS; i++)
		if (log_level[i] > 0)
			return;
#endif

	va_start(ap, fmt);
	_log_print(0, LOG_NOTICE, fmt, ap, LOG_PRINT, 0);
	va_end(ap);
}
