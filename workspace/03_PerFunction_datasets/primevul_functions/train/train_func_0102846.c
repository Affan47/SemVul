pg_vsprintf(char *str, const char *fmt, va_list args)
{
	PrintfTarget target;

	if (str == NULL)
		return 0;
	target.bufstart = target.bufptr = str;
	target.bufend = NULL;
	target.stream = NULL;

	if (dopr(&target, fmt, args))
	{
		*(target.bufptr) = '\0';
		errno = EINVAL;
		return -1;
	}
	*(target.bufptr) = '\0';
	return target.bufptr - target.bufstart;
}
