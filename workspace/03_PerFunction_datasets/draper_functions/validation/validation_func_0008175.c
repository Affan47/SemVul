cfg_get_int_with_result (char *cfg, char *var, int *result)
{
	char str[128];

	if (!cfg_get_str (cfg, var, str, sizeof (str)))
	{
		*result = 0;
		return 0;
	}

	*result = 1;
	return atoi (str);
}
