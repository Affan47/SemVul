cmdline_wildchar_complete(
	int		c,
	int		escape,
	int		*did_wild_list,
	int		*wim_index_p,
	expand_T	*xp,
	int		*gotesc)
{
    int		wim_index = *wim_index_p;
    int		res;
    int		j;
    int		options = WILD_NO_BEEP;

    if (wim_flags[wim_index] & WIM_BUFLASTUSED)
	options |= WILD_BUFLASTUSED;
    if (xp->xp_numfiles > 0)
    {

	if (xp->xp_numfiles > 1
		&& !*did_wild_list
		&& ((wim_flags[wim_index] & WIM_LIST)
		    || (p_wmnu && (wim_flags[wim_index] & WIM_FULL) != 0)))
	{
	    (void)showmatches(xp,
		    p_wmnu && ((wim_flags[wim_index] & WIM_LIST) == 0));
	    redrawcmd();
	    *did_wild_list = TRUE;
	}
	if (wim_flags[wim_index] & WIM_LONGEST)
	    res = nextwild(xp, WILD_LONGEST, options, escape);
	else if (wim_flags[wim_index] & WIM_FULL)
	    res = nextwild(xp, WILD_NEXT, options, escape);
	else
	    res = OK;
    }
    else
    {
	wim_index = 0;
	j = ccline.cmdpos;


	if (wim_flags[0] & WIM_LONGEST)
	    res = nextwild(xp, WILD_LONGEST, options, escape);
	else
	    res = nextwild(xp, WILD_EXPAND_KEEP, options, escape);


	if (got_int)
	{
	    (void)vpeekc();
	    got_int = FALSE;
	    (void)ExpandOne(xp, NULL, NULL, 0, WILD_FREE);
	    xp->xp_context = EXPAND_NOTHING;
	    *wim_index_p = wim_index;
	    return CMDLINE_CHANGED;
	}


	if (res == OK && xp->xp_numfiles > 1)
	{


	    if (wim_flags[0] == WIM_LONGEST && ccline.cmdpos == j)
		wim_index = 1;
	    if ((wim_flags[wim_index] & WIM_LIST)
		    || (p_wmnu && (wim_flags[wim_index] & WIM_FULL) != 0))
	    {
		if (!(wim_flags[0] & WIM_LONGEST))
		{
		    int p_wmnu_save = p_wmnu;

		    p_wmnu = 0;


		    nextwild(xp, WILD_PREV, 0, escape);
		    p_wmnu = p_wmnu_save;
		}
		(void)showmatches(xp, p_wmnu
			&& ((wim_flags[wim_index] & WIM_LIST) == 0));
		redrawcmd();
		*did_wild_list = TRUE;
		if (wim_flags[wim_index] & WIM_LONGEST)
		    nextwild(xp, WILD_LONGEST, options, escape);
		else if (wim_flags[wim_index] & WIM_FULL)
		    nextwild(xp, WILD_NEXT, options, escape);
	    }
	    else
		vim_beep(BO_WILD);
	}
	else if (xp->xp_numfiles == -1)
	    xp->xp_context = EXPAND_NOTHING;
    }
    if (wim_index < 3)
	++wim_index;
    if (c == ESC)
	*gotesc = TRUE;

    *wim_index_p = wim_index;
    return (res == OK) ? CMDLINE_CHANGED : CMDLINE_NOT_CHANGED;
}
