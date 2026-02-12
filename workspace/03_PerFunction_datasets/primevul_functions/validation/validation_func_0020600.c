do_doautocmd(
    char_u	*arg,
    int		do_msg,
    int		*did_something)
{
    char_u	*fname;
    int		nothing_done = TRUE;
    int		group;

    if (did_something != NULL)
	*did_something = FALSE;


    group = au_get_grouparg(&arg);
    if (arg == NULL)
	return FAIL;

    if (*arg == '*')
    {
	EMSG(_("E217: Can't execute autocommands for ALL events"));
	return FAIL;
    }


    fname = find_end_event(arg, group != AUGROUP_ALL);
    if (fname == NULL)
	return FAIL;

    fname = skipwhite(fname);


    while (*arg && !ends_excmd(*arg) && !VIM_ISWHITE(*arg))
	if (apply_autocmds_group(event_name2nr(arg, &arg),
				      fname, NULL, TRUE, group, curbuf, NULL))
	    nothing_done = FALSE;

    if (nothing_done && do_msg)
	MSG(_("No matching autocommands"));
    if (did_something != NULL)
	*did_something = !nothing_done;

#ifdef FEAT_EVAL
    return aborting() ? FAIL : OK;
#else
    return OK;
#endif
}
