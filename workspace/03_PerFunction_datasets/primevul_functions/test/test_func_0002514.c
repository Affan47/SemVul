conninfo_array_parse(const char *const *keywords, const char *const *values,
					 PQExpBuffer errorMessage, bool use_defaults,
					 int expand_dbname)
{
	PQconninfoOption *options;
	PQconninfoOption *dbname_options = NULL;
	PQconninfoOption *option;
	int			i = 0;


	while (expand_dbname && keywords[i])
	{
		const char *pname = keywords[i];
		const char *pvalue = values[i];


		if (strcmp(pname, "dbname") == 0 && pvalue)
		{


			if (recognized_connection_string(pvalue))
			{
				dbname_options = parse_connection_string(pvalue, errorMessage, false);
				if (dbname_options == NULL)
					return NULL;
			}
			break;
		}
		++i;
	}


	options = conninfo_init(errorMessage);
	if (options == NULL)
	{
		PQconninfoFree(dbname_options);
		return NULL;
	}


	i = 0;
	while (keywords[i])
	{
		const char *pname = keywords[i];
		const char *pvalue = values[i];

		if (pvalue != NULL && pvalue[0] != '\0')
		{

			for (option = options; option->keyword != NULL; option++)
			{
				if (strcmp(option->keyword, pname) == 0)
					break;
			}


			if (option->keyword == NULL)
			{
				appendPQExpBuffer(errorMessage,
								  libpq_gettext("invalid connection option \"%s\"\n"),
								  pname);
				PQconninfoFree(options);
				PQconninfoFree(dbname_options);
				return NULL;
			}


			if (strcmp(pname, "dbname") == 0 && dbname_options)
			{
				PQconninfoOption *str_option;

				for (str_option = dbname_options; str_option->keyword != NULL; str_option++)
				{
					if (str_option->val != NULL)
					{
						int			k;

						for (k = 0; options[k].keyword; k++)
						{
							if (strcmp(options[k].keyword, str_option->keyword) == 0)
							{
								if (options[k].val)
									free(options[k].val);
								options[k].val = strdup(str_option->val);
								if (!options[k].val)
								{
									appendPQExpBufferStr(errorMessage,
														 libpq_gettext("out of memory\n"));
									PQconninfoFree(options);
									PQconninfoFree(dbname_options);
									return NULL;
								}
								break;
							}
						}
					}
				}


				PQconninfoFree(dbname_options);
				dbname_options = NULL;
			}
			else
			{


				if (option->val)
					free(option->val);
				option->val = strdup(pvalue);
				if (!option->val)
				{
					appendPQExpBufferStr(errorMessage,
										 libpq_gettext("out of memory\n"));
					PQconninfoFree(options);
					PQconninfoFree(dbname_options);
					return NULL;
				}
			}
		}
		++i;
	}
	PQconninfoFree(dbname_options);


	if (use_defaults)
	{
		if (!conninfo_add_defaults(options, errorMessage))
		{
			PQconninfoFree(options);
			return NULL;
		}
	}

	return options;
}
