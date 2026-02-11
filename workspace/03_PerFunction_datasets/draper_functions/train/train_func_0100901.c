script_autoload(name, reload)
    char_u	*name;
    int		reload;
{
    char_u	*p;
    char_u	*scriptname, *tofree;
    int		ret = FALSE;
    int		i;


    if (no_autoload)
	return FALSE;


    p = vim_strchr(name, AUTOLOAD_CHAR);
    if (p == NULL || p == name)
	return FALSE;

    tofree = scriptname = autoload_name(name);


    for (i = 0; i < ga_loaded.ga_len; ++i)
	if (STRCMP(((char_u **)ga_loaded.ga_data)[i] + 9, scriptname + 9) == 0)
	    break;
    if (!reload && i < ga_loaded.ga_len)
	ret = FALSE;
    else
    {

	if (i == ga_loaded.ga_len && ga_grow(&ga_loaded, 1) == OK)
	{
	    ((char_u **)ga_loaded.ga_data)[ga_loaded.ga_len++] = scriptname;
	    tofree = NULL;
	}


	if (source_runtime(scriptname, FALSE) == OK)
	    ret = TRUE;
    }

    vim_free(tofree);
    return ret;
}
