get_method_path(const char *p,
	const char **method,
	unsigned *methodl,
	const char **path)
{
unsigned	i;

	for (i=0; p && p[i]; i++)
	{
		if (p[i] == ':')
		{
			*method=p;
			*methodl= ++i;
			*path=p+i;
			return;
		}

		if (!isalpha( (int)(unsigned char)p[i]))
			break;
	}

	*method=0;
	*methodl=0;
	*path=p;
}
