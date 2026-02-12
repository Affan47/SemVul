make_filter_cmd(
    char_u	*cmd,
    char_u	*itmp,
    char_u	*otmp)
{
    char_u	*buf;
    long_u	len;

#if defined(UNIX)
    int		is_fish_shell;
    char_u	*shell_name = get_isolated_shell_name();

    if (shell_name == NULL)
	return NULL;


    is_fish_shell = (fnamecmp(shell_name, "fish") == 0);
    vim_free(shell_name);
    if (is_fish_shell)
	len = (long_u)STRLEN(cmd) + 13;
    else
#endif
	len = (long_u)STRLEN(cmd) + 3;
    if (itmp != NULL)
	len += (long_u)STRLEN(itmp) + 9;
    if (otmp != NULL)
	len += (long_u)STRLEN(otmp) + (long_u)STRLEN(p_srr) + 2;
    buf = alloc(len);
    if (buf == NULL)
	return NULL;

#if defined(UNIX)


    if (itmp != NULL || otmp != NULL)
    {
	if (is_fish_shell)
	    vim_snprintf((char *)buf, len, "begin; %s; end", (char *)cmd);
	else
	    vim_snprintf((char *)buf, len, "(%s)", (char *)cmd);
    }
    else
	STRCPY(buf, cmd);
    if (itmp != NULL)
    {
	STRCAT(buf, " < ");
	STRCAT(buf, itmp);
    }
#else


    if (*p_sxe != NUL && *p_sxq == '(')
    {
	if (itmp != NULL || otmp != NULL)
	    vim_snprintf((char *)buf, len, "(%s)", (char *)cmd);
	else
	    STRCPY(buf, cmd);
	if (itmp != NULL)
	{
	    STRCAT(buf, " < ");
	    STRCAT(buf, itmp);
	}
    }
    else
    {
	STRCPY(buf, cmd);
	if (itmp != NULL)
	{
	    char_u	*p;


	    if (*p_shq == NUL)
	    {
		p = find_pipe(buf);
		if (p != NULL)
		    *p = NUL;
	    }
	    STRCAT(buf, " <");
	    STRCAT(buf, itmp);
	    if (*p_shq == NUL)
	    {
		p = find_pipe(cmd);
		if (p != NULL)
		{
		    STRCAT(buf, " ");
		    STRCAT(buf, p);
		}
	    }
	}
    }
#endif
    if (otmp != NULL)
	append_redir(buf, (int)len, p_srr, otmp);

    return buf;
}
