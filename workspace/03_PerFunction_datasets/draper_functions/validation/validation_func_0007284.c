debug(const char *format, ...)
{
	char str[256];
	va_list ap;

	if (callbacks_pointer->debug == NULL)
		return;

	va_start(ap, format);

	if (vsnprintf(str, sizeof(str), format, ap) > 0)
		callbacks_pointer->debug(str);

	va_end(ap);
}
