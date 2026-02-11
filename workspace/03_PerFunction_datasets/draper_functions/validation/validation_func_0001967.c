str_tolower(char *str)
{
	char *c;
	for (c = str; *c; ++c)
		*c = tolower(*c);
	return str;
}
