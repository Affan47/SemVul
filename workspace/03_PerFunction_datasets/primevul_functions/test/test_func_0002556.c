conninfo_uri_parse_params(char *params,
						  PQconninfoOption *connOptions,
						  PQExpBuffer errorMessage)
{
	while (*params)
	{
		char	   *keyword = params;
		char	   *value = NULL;
		char	   *p = params;
		bool		malloced = false;
		int			oldmsglen;


		for (;;)
		{
			if (*p == '=')
			{

				if (value != NULL)
				{
					appendPQExpBuffer(errorMessage,
									  libpq_gettext("extra key/value separator \"=\" in URI query parameter: \"%s\"\n"),
									  keyword);
					return false;
				}

				*p++ = '\0';
				value = p;
			}
			else if (*p == '&' || *p == '\0')
			{


				if (*p != '\0')
					*p++ = '\0';

				if (value == NULL)
				{
					appendPQExpBuffer(errorMessage,
									  libpq_gettext("missing key/value separator \"=\" in URI query parameter: \"%s\"\n"),
									  keyword);
					return false;
				}

				break;
			}
			else
				++p;
		}

		keyword = conninfo_uri_decode(keyword, errorMessage);
		if (keyword == NULL)
		{

			return false;
		}
		value = conninfo_uri_decode(value, errorMessage);
		if (value == NULL)
		{

			free(keyword);
			return false;
		}
		malloced = true;


		if (strcmp(keyword, "ssl") == 0 &&
			strcmp(value, "true") == 0)
		{
			free(keyword);
			free(value);
			malloced = false;

			keyword = "sslmode";
			value = "require";
		}


		oldmsglen = errorMessage->len;
		if (!conninfo_storeval(connOptions, keyword, value,
							   errorMessage, true, false))
		{

			if (errorMessage->len == oldmsglen)
				appendPQExpBuffer(errorMessage,
								  libpq_gettext("invalid URI query parameter: \"%s\"\n"),
								  keyword);

			if (malloced)
			{
				free(keyword);
				free(value);
			}
			return false;
		}

		if (malloced)
		{
			free(keyword);
			free(value);
		}


		params = p;
	}

	return true;
}
