conninfo_add_defaults(PQconninfoOption *options, PQExpBuffer errorMessage)
{
	PQconninfoOption *option;
	char	   *tmp;


	if (parseServiceInfo(options, errorMessage) != 0 && errorMessage)
		return false;


	for (option = options; option->keyword != NULL; option++)
	{
		if (option->val != NULL)
			continue;


		if (option->envvar != NULL)
		{
			if ((tmp = getenv(option->envvar)) != NULL)
			{
				option->val = strdup(tmp);
				if (!option->val)
				{
					if (errorMessage)
						appendPQExpBufferStr(errorMessage,
											 libpq_gettext("out of memory\n"));
					return false;
				}
				continue;
			}
		}


		if (strcmp(option->keyword, "sslmode") == 0)
		{
			const char *requiresslenv = getenv("PGREQUIRESSL");

			if (requiresslenv != NULL && requiresslenv[0] == '1')
			{
				option->val = strdup("require");
				if (!option->val)
				{
					if (errorMessage)
						appendPQExpBufferStr(errorMessage,
											 libpq_gettext("out of memory\n"));
					return false;
				}
				continue;
			}
		}


		if (option->compiled != NULL)
		{
			option->val = strdup(option->compiled);
			if (!option->val)
			{
				if (errorMessage)
					appendPQExpBufferStr(errorMessage,
										 libpq_gettext("out of memory\n"));
				return false;
			}
			continue;
		}


		if (strcmp(option->keyword, "user") == 0)
		{
			option->val = pg_fe_getauthname(NULL);
			continue;
		}
	}

	return true;
}
