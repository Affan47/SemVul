nist_header_read_int (const char *header, const char *key, int *val)
{
	const char *cp;
	char keystring[256], scanstring[256];

	snprintf(keystring, 256, "\n%s -i", key);

	if ((cp = strstr(header, keystring)) != NULL)
	{
		snprintf(scanstring, 256, "\n%s -i %%d", key);
		sscanf(cp, scanstring, val);
		return true;
	}

	return false;
}
