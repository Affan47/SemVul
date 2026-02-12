add_llist_tags(
    char_u	*tag,
    int		num_matches,
    char_u	**matches)
{
    list_T	*list;
    char_u	tag_name[128 + 1];
    char_u	*fname;
    char_u	*cmd;
    int		i;
    char_u	*p;
    tagptrs_T	tagp;

    fname = alloc(MAXPATHL + 1);
    cmd = alloc(CMDBUFFSIZE + 1);
    list = list_alloc();
    if (list == NULL || fname == NULL || cmd == NULL)
    {
	vim_free(cmd);
	vim_free(fname);
	if (list != NULL)
	    list_free(list);
	return FAIL;
    }

    for (i = 0; i < num_matches; ++i)
    {
	int	    len, cmd_len;
	long    lnum;
	dict_T  *dict;

	parse_match(matches[i], &tagp);


	len = (int)(tagp.tagname_end - tagp.tagname);
	if (len > 128)
	    len = 128;
	vim_strncpy(tag_name, tagp.tagname, len);
	tag_name[len] = NUL;


	p = tag_full_fname(&tagp);
	if (p == NULL)
	    continue;
	vim_strncpy(fname, p, MAXPATHL);
	vim_free(p);


	lnum = 0;
	if (isdigit(*tagp.command))

	    lnum = atol((char *)tagp.command);
	else
	{
	    char_u *cmd_start, *cmd_end;


	    cmd_start = tagp.command;
	    cmd_end = tagp.command_end;
	    if (cmd_end == NULL)
	    {
		for (p = tagp.command;
		     *p && *p != '\r' && *p != '\n'; ++p)
		    ;
		cmd_end = p;
	    }


	    cmd_end--;


	    if (*cmd_start == '/' || *cmd_start == '?')
		cmd_start++;

	    if (*cmd_end == '/' || *cmd_end == '?')
		cmd_end--;

	    len = 0;
	    cmd[0] = NUL;


	    if (*cmd_start == '^')
	    {
		STRCPY(cmd, "^");
		cmd_start++;
		len++;
	    }


	    STRCAT(cmd, "\\V");
	    len += 2;

	    cmd_len = (int)(cmd_end - cmd_start + 1);
	    if (cmd_len > (CMDBUFFSIZE - 5))
		cmd_len = CMDBUFFSIZE - 5;
	    STRNCAT(cmd, cmd_start, cmd_len);
	    len += cmd_len;

	    if (cmd[len - 1] == '$')
	    {


		cmd[len - 1] = '\\';
		cmd[len] = '$';
		len++;
	    }

	    cmd[len] = NUL;
	}

	if ((dict = dict_alloc()) == NULL)
	    continue;
	if (list_append_dict(list, dict) == FAIL)
	{
	    vim_free(dict);
	    continue;
	}

	dict_add_string(dict, "text", tag_name);
	dict_add_string(dict, "filename", fname);
	dict_add_number(dict, "lnum", lnum);
	if (lnum == 0)
	    dict_add_string(dict, "pattern", cmd);
    }

    vim_snprintf((char *)IObuff, IOSIZE, "ltag %s", tag);
    set_errorlist(curwin, list, ' ', IObuff, NULL);

    list_free(list);
    vim_free(fname);
    vim_free(cmd);

    return OK;
}
