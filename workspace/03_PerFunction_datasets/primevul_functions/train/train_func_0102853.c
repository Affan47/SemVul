pg_vsnprintf(char *str, size_t count, const char *fmt, va_list args)
{
	PrintfTarget target;

	if (str == NULL || count == 0)
		return 0;
	target.bufstart = target.bufptr = str;
	target.bufend = str + count - 1;
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
