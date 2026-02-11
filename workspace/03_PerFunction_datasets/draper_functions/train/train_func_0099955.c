pa_ap_log_rerror(const char *file, int line, int level, const pa_request_rec *s, const char *fmt, ...) {
	const char* str;
	va_list l;
	va_start(l, fmt);
	str=va_arg(l, const char*);
	va_end(l);

	ap_log_rerror(file, line,
#if (AP_SERVER_MAJORVERSION_NUMBER == 2) && (AP_SERVER_MINORVERSION_NUMBER >= 4)
			APLOG_MODULE_INDEX,
#endif
			level,
#ifdef STANDARD20_MODULE_STUFF
			0,
#endif
			(request_rec*)s->real_request_rec, "%s", str);
}
