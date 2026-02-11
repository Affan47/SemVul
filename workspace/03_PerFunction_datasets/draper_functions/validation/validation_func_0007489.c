PrintWarningSameLine(const char *format, ...)
{
	va_list args;
	va_start(args, format);

	vfprintf(stderr, format, args);
	fflush(stderr);

	if (stdoutErrors)
	{
		vfprintf(stdout, format, args);
		fflush(stdout);
	}

	va_end(args);
}
