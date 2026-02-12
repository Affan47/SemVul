set_context_in_autocmd(
    expand_T	*xp,
    char_u	*arg,
    int		doautocmd)
{
    char_u	*p;
    int		group;


    include_groups = FALSE;
    p = arg;
    group = au_get_grouparg(&arg);
    if (group == AUGROUP_ERROR)
	return NULL;

    if (*arg == NUL && group != AUGROUP_ALL && !VIM_ISWHITE(arg[-1]))
    {
	arg = p;
	group = AUGROUP_ALL;
    }


    for (p = arg; *p != NUL && !VIM_ISWHITE(*p); ++p)
	if (*p == ',')
	    arg = p + 1;
    if (*p == NUL)
    {
	if (group == AUGROUP_ALL)
	    include_groups = TRUE;
	xp->xp_context = EXPAND_EVENTS;
	xp->xp_pattern = arg;
	return NULL;
    }


    arg = skipwhite(p);
    while (*arg && (!VIM_ISWHITE(*arg) || arg[-1] == '\\'))
	arg++;
    if (*arg)
	return arg;

    if (doautocmd)
	xp->xp_context = EXPAND_FILES;
    else
	xp->xp_context = EXPAND_NOTHING;
    return NULL;
}
