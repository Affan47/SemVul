conninfo_uri_decode(const char *str, PQExpBuffer errorMessage)
{
	char	   *buf;
	char	   *p;
	const char *q = str;

	buf = malloc(strlen(str) + 1);
	if (buf == NULL)
	{
		appendPQExpBufferStr(errorMessage, libpq_gettext("out of memory\n"));
		return NULL;
	}
	p = buf;

	for (;;)
	{
		if (*q != '%')
		{

			if (!(*(p++) = *(q++)))
				break;
		}
		else
		{
			int			hi;
			int			lo;
			int			c;

			++q;


			if (!(get_hexdigit(*q++, &hi) && get_hexdigit(*q++, &lo)))
			{
				appendPQExpBuffer(errorMessage,
								  libpq_gettext("invalid percent-encoded token: \"%s\"\n"),
								  str);
				free(buf);
				return NULL;
			}

			c = (hi << 4) | lo;
			if (c == 0)
			{
				appendPQExpBuffer(errorMessage,
								  libpq_gettext("forbidden value %%00 in percent-encoded value: \"%s\"\n"),
								  str);
				free(buf);
				return NULL;
			}
			*(p++) = c;
		}
	}

	return buf;
}
