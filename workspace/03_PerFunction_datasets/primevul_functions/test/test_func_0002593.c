conninfo_uri_parse_options(PQconninfoOption *options, const char *uri,
						   PQExpBuffer errorMessage)
{
	int			prefix_len;
	char	   *p;
	char	   *buf = NULL;
	char	   *start;
	char		prevchar = '\0';
	char	   *user = NULL;
	char	   *host = NULL;
	bool		retval = false;
	PQExpBufferData hostbuf;
	PQExpBufferData portbuf;

	initPQExpBuffer(&hostbuf);
	initPQExpBuffer(&portbuf);
	if (PQExpBufferDataBroken(hostbuf) || PQExpBufferDataBroken(portbuf))
	{
		appendPQExpBufferStr(errorMessage,
							 libpq_gettext("out of memory\n"));
		goto cleanup;
	}


	buf = strdup(uri);
	if (buf == NULL)
	{
		appendPQExpBufferStr(errorMessage,
							 libpq_gettext("out of memory\n"));
		goto cleanup;
	}
	start = buf;


	prefix_len = uri_prefix_length(uri);
	if (prefix_len == 0)
	{

		appendPQExpBuffer(errorMessage,
						  libpq_gettext("invalid URI propagated to internal parser routine: \"%s\"\n"),
						  uri);
		goto cleanup;
	}
	start += prefix_len;
	p = start;


	while (*p && *p != '@' && *p != '/')
		++p;
	if (*p == '@')
	{


		user = start;

		p = user;
		while (*p != ':' && *p != '@')
			++p;


		prevchar = *p;
		*p = '\0';

		if (*user &&
			!conninfo_storeval(options, "user", user,
							   errorMessage, false, true))
			goto cleanup;

		if (prevchar == ':')
		{
			const char *password = p + 1;

			while (*p != '@')
				++p;
			*p = '\0';

			if (*password &&
				!conninfo_storeval(options, "password", password,
								   errorMessage, false, true))
				goto cleanup;
		}


		++p;
	}
	else
	{


		p = start;
	}


	for (;;)
	{


		if (*p == '[')
		{
			host = ++p;
			while (*p && *p != ']')
				++p;
			if (!*p)
			{
				appendPQExpBuffer(errorMessage,
								  libpq_gettext("end of string reached when looking for matching \"]\" in IPv6 host address in URI: \"%s\"\n"),
								  uri);
				goto cleanup;
			}
			if (p == host)
			{
				appendPQExpBuffer(errorMessage,
								  libpq_gettext("IPv6 host address may not be empty in URI: \"%s\"\n"),
								  uri);
				goto cleanup;
			}


			*(p++) = '\0';


			if (*p && *p != ':' && *p != '/' && *p != '?' && *p != ',')
			{
				appendPQExpBuffer(errorMessage,
								  libpq_gettext("unexpected character \"%c\" at position %d in URI (expected \":\" or \"/\"): \"%s\"\n"),
								  *p, (int) (p - buf + 1), uri);
				goto cleanup;
			}
		}
		else
		{

			host = p;


			while (*p && *p != ':' && *p != '/' && *p != '?' && *p != ',')
				++p;
		}


		prevchar = *p;
		*p = '\0';

		appendPQExpBufferStr(&hostbuf, host);

		if (prevchar == ':')
		{
			const char *port = ++p;

			while (*p && *p != '/' && *p != '?' && *p != ',')
				++p;

			prevchar = *p;
			*p = '\0';

			appendPQExpBufferStr(&portbuf, port);
		}

		if (prevchar != ',')
			break;
		++p;
		appendPQExpBufferChar(&hostbuf, ',');
		appendPQExpBufferChar(&portbuf, ',');
	}


	if (PQExpBufferDataBroken(hostbuf) || PQExpBufferDataBroken(portbuf))
		goto cleanup;
	if (hostbuf.data[0] &&
		!conninfo_storeval(options, "host", hostbuf.data,
						   errorMessage, false, true))
		goto cleanup;
	if (portbuf.data[0] &&
		!conninfo_storeval(options, "port", portbuf.data,
						   errorMessage, false, true))
		goto cleanup;

	if (prevchar && prevchar != '?')
	{
		const char *dbname = ++p;


		while (*p && *p != '?')
			++p;

		prevchar = *p;
		*p = '\0';


		if (*dbname &&
			!conninfo_storeval(options, "dbname", dbname,
							   errorMessage, false, true))
			goto cleanup;
	}

	if (prevchar)
	{
		++p;

		if (!conninfo_uri_parse_params(p, options, errorMessage))
			goto cleanup;
	}


	retval = true;

cleanup:
	termPQExpBuffer(&hostbuf);
	termPQExpBuffer(&portbuf);
	if (buf)
		free(buf);
	return retval;
}
