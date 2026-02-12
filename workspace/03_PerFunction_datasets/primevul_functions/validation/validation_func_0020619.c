do_autocmd(char_u *arg_in, int forceit)
{
    char_u	*arg = arg_in;
    char_u	*pat;
    char_u	*envpat = NULL;
    char_u	*cmd;
    event_T	event;
    int		need_free = FALSE;
    int		nested = FALSE;
    int		group;

    if (*arg == '|')
    {
	arg = (char_u *)"";
	group = AUGROUP_ALL;
    }
    else
    {


	group = au_get_grouparg(&arg);
	if (arg == NULL)
	    return;
    }


    pat = find_end_event(arg, group != AUGROUP_ALL);
    if (pat == NULL)
	return;

    pat = skipwhite(pat);
    if (*pat == '|')
    {
	pat = (char_u *)"";
	cmd = (char_u *)"";
    }
    else
    {


	cmd = pat;
	while (*cmd && (!VIM_ISWHITE(*cmd) || cmd[-1] == '\\'))
	    cmd++;
	if (*cmd)
	    *cmd++ = NUL;


	if (vim_strchr(pat, '$') != NULL || vim_strchr(pat, '~') != NULL)
	{
#ifdef BACKSLASH_IN_FILENAME
	    int	p_ssl_save = p_ssl;

	    p_ssl = TRUE;
#endif
	    envpat = expand_env_save(pat);
#ifdef BACKSLASH_IN_FILENAME
	    p_ssl = p_ssl_save;
#endif
	    if (envpat != NULL)
		pat = envpat;
	}


	cmd = skipwhite(cmd);
	if (*cmd != NUL && STRNCMP(cmd, "nested", 6) == 0 && VIM_ISWHITE(cmd[6]))
	{
	    nested = TRUE;
	    cmd = skipwhite(cmd + 6);
	}


	if (*cmd != NUL)
	{
	    cmd = expand_sfile(cmd);
	    if (cmd == NULL)
		return;
	    need_free = TRUE;
	}
    }


    if (!forceit && *cmd == NUL)
    {

	MSG_PUTS_TITLE(_("\n--- Auto-Commands ---"));
    }


    last_event = (event_T)-1;
    last_group = AUGROUP_ERROR;
    if (*arg == '*' || *arg == NUL || *arg == '|')
    {
	for (event = (event_T)0; (int)event < (int)NUM_EVENTS;
					    event = (event_T)((int)event + 1))
	    if (do_autocmd_event(event, pat,
					 nested, cmd, forceit, group) == FAIL)
		break;
    }
    else
    {
	while (*arg && *arg != '|' && !VIM_ISWHITE(*arg))
	    if (do_autocmd_event(event_name2nr(arg, &arg), pat,
					nested,	cmd, forceit, group) == FAIL)
		break;
    }

    if (need_free)
	vim_free(cmd);
    vim_free(envpat);
}
