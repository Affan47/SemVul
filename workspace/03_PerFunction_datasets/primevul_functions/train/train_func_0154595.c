opt_strings_flags(
    char_u	*val,
    char	**values,
    unsigned	*flagp,
    int		list)
{
    int		i;
    int		len;
    unsigned	new_flags = 0;

    while (*val)
    {
	for (i = 0; ; ++i)
	{
	    if (values[i] == NULL)
		return FAIL;

	    len = (int)STRLEN(values[i]);
	    if (STRNCMP(values[i], val, len) == 0
		    && ((list && val[len] == ',') || val[len] == NUL))
	    {
		val += len + (val[len] == ',');
		new_flags |= (1 << i);
		break;
	    }
	}
    }
    if (flagp != NULL)
	*flagp = new_flags;

    return OK;
}
