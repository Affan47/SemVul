static void json_trace(int errlevel, const char *fmt, ...)

{
    if (errlevel <= debuglevel && NULL != debugfp) {
	char buf[BUFSIZ] = {0};
	va_list ap;

	(void)strlcpy(buf, "json: ", sizeof(buf));
	va_start(ap, fmt);
	str_vappendf(buf, sizeof(buf), fmt, ap);
	va_end(ap);

	(void)fputs(buf, debugfp);
    }
}
