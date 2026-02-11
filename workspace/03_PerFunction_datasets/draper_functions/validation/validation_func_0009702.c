get_enum(const char *name, const confenum_t *tbl, int deflt)
{
    string_var val = get_string(name, 0);

    if (val == (char *)0)
    	return deflt;

    for ( ; tbl->string != 0 ; tbl++)
    {
    	if (!strcasecmp(tbl->string, val))
	    return tbl->value;
    }

    if (isdigit(val.data()[0]))
    {
	char *end = 0;
	int ival = (int)strtol(val, &end, 0);
	if (end != 0 && end != val && *end == '\0')
	    return ival;
    }
    return deflt;
}
