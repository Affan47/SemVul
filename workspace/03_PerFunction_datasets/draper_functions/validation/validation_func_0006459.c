gravity_dir_to_string(direction_t dir, char *default_str)
{
	char *str = NULL;
	int d = dir * STRINGS_PER_DIR;

	if (d >= sizeof(gravity_dir_optlist)/sizeof(gravity_dir_optlist[0]))
	{
		return default_str;
	}
	str = gravity_dir_optlist[d];

	if (str == NULL)
	{
		return default_str;
	}

	return str;
}
