locale_xxx_assign(int category, const char *value, bool doit, GucSource source)
{
	char	   *save;

	save = setlocale(category, NULL);
	if (!save)
		return NULL;


	save = pstrdup(save);

	if (!setlocale(category, value))
		value = NULL;

	setlocale(category, save);
	pfree(save);


	if (doit && value != NULL)
		CurrentLocaleConvValid = false;

	return value;
}
