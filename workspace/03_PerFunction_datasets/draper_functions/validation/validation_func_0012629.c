on_off(const char *value)
{
	if (!value)
		return -1;

	if (!xstrcasecmp(value, "on") || !xstrcasecmp(value, "true") || !xstrcasecmp(value, "yes") || !xstrcasecmp(value, "tak") || !xstrcmp(value, "1"))
		return 1;

	if (!xstrcasecmp(value, "off") || !xstrcasecmp(value, "false") || !xstrcasecmp(value, "no") || !xstrcasecmp(value, "nie") || !xstrcmp(value, "0"))
		return 0;

	return -1;
}
