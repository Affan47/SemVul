atfirst_exceptspace(void)
{
	const char *start = sp;
	const char *end = cp ? cp - 1 : lp;

	while (start < end && *start && isspace(*start))
		start++;
	return (start == end) ? 1 : 0;
}
