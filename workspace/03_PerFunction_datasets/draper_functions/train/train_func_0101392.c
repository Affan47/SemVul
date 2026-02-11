e2p_string2os(char *str)
{
	const char	**cpp;
	int		i = 0;

	for (cpp = os_tab; *cpp; cpp++, i++) {
		if (!strcasecmp(str, *cpp))
			return i;
	}
	return -1;
}
