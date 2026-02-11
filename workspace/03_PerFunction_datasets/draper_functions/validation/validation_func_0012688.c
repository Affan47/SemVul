get_map_mode(cmdp, forceit)
    char_u	**cmdp;
    int		forceit;
{
    char_u	*p;
    int		modec;
    int		mode;

    p = *cmdp;
    modec = *p++;
    if (modec == 'i')
	mode = INSERT;
    else if (modec == 'l')
	mode = LANGMAP;
    else if (modec == 'c')
	mode = CMDLINE;
    else if (modec == 'n' && *p != 'o')
	mode = NORMAL;
    else if (modec == 'v')
	mode = VISUAL + SELECTMODE;
    else if (modec == 'x')
	mode = VISUAL;
    else if (modec == 's')
	mode = SELECTMODE;
    else if (modec == 'o')
	mode = OP_PENDING;
    else
    {
	--p;
	if (forceit)
	    mode = INSERT + CMDLINE;
	else
	    mode = VISUAL + SELECTMODE + NORMAL + OP_PENDING;
    }

    *cmdp = p;
    return mode;
}
