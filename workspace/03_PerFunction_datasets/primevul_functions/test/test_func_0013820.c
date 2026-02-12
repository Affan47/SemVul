autoload_name(char_u *name)
{
    char_u	*p, *q = NULL;
    char_u	*scriptname;


    scriptname = alloc(STRLEN(name) + 14);
    if (scriptname == NULL)
	return NULL;
    STRCPY(scriptname, "autoload/");
    STRCAT(scriptname, name[0] == 'g' && name[1] == ':' ? name + 2: name);
    for (p = scriptname + 9; (p = vim_strchr(p, AUTOLOAD_CHAR)) != NULL;
								    q = p, ++p)
	*p = '/';
    STRCPY(q, ".vim");
    return scriptname;
}
