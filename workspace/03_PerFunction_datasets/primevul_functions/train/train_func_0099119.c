arrayname(const char *str)
{
	const char *p;
	char *rv;

	if ((p = cstrchr(str, '[')) == 0)

		strdupx(rv, str, ATEMP);
	else
		strndupx(rv, str, p - str, ATEMP);

	return (rv);
}
