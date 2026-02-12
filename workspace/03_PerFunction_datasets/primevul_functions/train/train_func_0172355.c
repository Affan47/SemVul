static void _pam_log(int err, CONST char *format, ...)
{
	va_list args;
	char buffer[BUFFER_SIZE];

	va_start(args, format);
	vsprintf(buffer, format, args);

	syslog(err, "%s: %s", pam_module_name, buffer);
	va_end(args);
}
