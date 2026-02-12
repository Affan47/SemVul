insert_value(char **str, char *pos, const char *substr, char **next)
{
	size_t subsz = strlen(substr);
	size_t strsz = strlen(*str);
	size_t possz = strlen(pos);
	size_t posoff;
	char *p;
	int sep;


	sep = !(pos > *str && *(pos - 1) == '=');


	posoff = pos - *str;

	p = realloc(*str, strsz + sep + subsz + 1);
	if (!p)
		return -ENOMEM;


	memset(p + strsz, 0, sep + subsz + 1);


	*str = p;
	pos = p + posoff;

	if (possz)

		memmove(pos + subsz + sep, pos, possz + 1);
	if (sep)
		*pos++ = '=';

	memcpy(pos, substr, subsz);

	if (next) {

		*next = pos + subsz;
		if (**next == ',')
			(*next)++;
	}
	return 0;
}
