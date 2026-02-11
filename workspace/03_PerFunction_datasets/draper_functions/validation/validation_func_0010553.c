totem_pl_parser_uri_to_dos (const char *uri, GFile *output)
{
	char *retval, *i;


	retval = totem_pl_parser_relative (output, uri);

	if (retval == NULL)
		retval = g_strdup (uri);


	if (g_str_has_prefix (retval, "smb://") != FALSE) {
		char *tmp;
		tmp = g_strdup (retval + strlen ("smb:"));
		g_free (retval);
		retval = tmp;
	}

	if (strstr (retval, "://") != NULL)
		return retval;

	i = retval;
	while (*i != '\0')
	{
		if (*i == '/')
			*i = '\\';
		i++;
	}

	return retval;
}
