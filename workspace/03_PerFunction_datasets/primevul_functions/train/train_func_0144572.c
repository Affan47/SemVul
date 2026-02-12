int git_config_perm(const char *var, const char *value)
{
	int i;
	char *endptr;

	if (value == NULL)
		return PERM_GROUP;

	if (!strcmp(value, "umask"))
		return PERM_UMASK;
	if (!strcmp(value, "group"))
		return PERM_GROUP;
	if (!strcmp(value, "all") ||
	    !strcmp(value, "world") ||
	    !strcmp(value, "everybody"))
		return PERM_EVERYBODY;


	i = strtol(value, &endptr, 8);


	if (*endptr != 0)
		return git_config_bool(var, value) ? PERM_GROUP : PERM_UMASK;


	switch (i) {
	case PERM_UMASK:
		return PERM_UMASK;
	case OLD_PERM_GROUP:
		return PERM_GROUP;
	case OLD_PERM_EVERYBODY:
		return PERM_EVERYBODY;
	}


	if ((i & 0600) != 0600)
		die("Problem with core.sharedRepository filemode value "
		    "(0%.3o).\nThe owner of files must always have "
		    "read and write permissions.", i);


	return -(i & 0666);
}
