is_long_option(const char *arg, char option, char *long_option)
{
	if (is_option(arg, option))
		return TRUE;
	else
		return (arg[0] == '-' && arg[1] == '-' && !strcmp(&arg[2], long_option));
}
