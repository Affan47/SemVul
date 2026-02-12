do_source_ext(
    char_u	*fname,
    int		check_other,
    int		is_vimrc,
    int		*ret_sid UNUSED,
    exarg_T	*eap,
    int		clearvars UNUSED)
{
    source_cookie_T	    cookie;
    char_u		    *p;
    char_u		    *fname_exp;
    char_u		    *firstline = NULL;
    int			    retval = FAIL;
    sctx_T		    save_current_sctx;
#ifdef FEAT_EVAL
    funccal_entry_T	    funccalp_entry;
    int			    save_debug_break_level = debug_break_level;
    int			    sid;
    scriptitem_T	    *si = NULL;
    int			    save_estack_compiling = estack_compiling;
#endif
#ifdef STARTUPTIME
    struct timeval	    tv_rel;
    struct timeval	    tv_start;
#endif
#ifdef FEAT_PROFILE
    proftime_T		    wait_start;
#endif
    int			    save_sticky_cmdmod_flags = sticky_cmdmod_flags;
    int			    trigger_source_post = FALSE;
    ESTACK_CHECK_DECLARATION

    CLEAR_FIELD(cookie);
    if (fname == NULL)
    {

	fname_exp = do_source_buffer_init(&cookie, eap);
	if (fname_exp == NULL)
	    return FAIL;
    }
    else
    {
	p = expand_env_save(fname);
	if (p == NULL)
	    return retval;
	fname_exp = fix_fname(p);
	vim_free(p);
	if (fname_exp == NULL)
	    return retval;
	if (mch_isdir(fname_exp))
	{
	    smsg(_("Cannot source a directory: \"%s\""), fname);
	    goto theend;
	}
    }
#ifdef FEAT_EVAL
    estack_compiling = FALSE;


    sid = find_script_by_name(fname_exp);
    if (sid > 0 && ret_sid != NULL
			  && SCRIPT_ITEM(sid)->sn_state != SN_STATE_NOT_LOADED)
    {

	*ret_sid = sid;
	retval = OK;
	goto theend;
    }
#endif


    if (has_autocmd(EVENT_SOURCECMD, fname_exp, NULL)
	    && apply_autocmds(EVENT_SOURCECMD, fname_exp, fname_exp,
							       FALSE, curbuf))
    {
#ifdef FEAT_EVAL
	retval = aborting() ? FAIL : OK;
#else
	retval = OK;
#endif
	if (retval == OK)

	    apply_autocmds(EVENT_SOURCEPOST, fname_exp, fname_exp,
								FALSE, curbuf);
	goto theend;
    }


    apply_autocmds(EVENT_SOURCEPRE, fname_exp, fname_exp, FALSE, curbuf);

    if (!cookie.source_from_buf)
    {
#ifdef USE_FOPEN_NOINH
	cookie.fp = fopen_noinh_readbin((char *)fname_exp);
#else
	cookie.fp = mch_fopen((char *)fname_exp, READBIN);
#endif
    }
    if (cookie.fp == NULL && check_other)
    {


	p = gettail(fname_exp);
	if ((*p == '.' || *p == '_')
		&& (STRICMP(p + 1, "vimrc") == 0
		    || STRICMP(p + 1, "gvimrc") == 0
		    || STRICMP(p + 1, "exrc") == 0))
	{
	    if (*p == '_')
		*p = '.';
	    else
		*p = '_';
#ifdef USE_FOPEN_NOINH
	    cookie.fp = fopen_noinh_readbin((char *)fname_exp);
#else
	    cookie.fp = mch_fopen((char *)fname_exp, READBIN);
#endif
	}
    }

    if (cookie.fp == NULL && !cookie.source_from_buf)
    {
	if (p_verbose > 0)
	{
	    verbose_enter();
	    if (SOURCING_NAME == NULL)
		smsg(_("could not source \"%s\""), fname);
	    else
		smsg(_("line %ld: could not source \"%s\""),
							SOURCING_LNUM, fname);
	    verbose_leave();
	}
	goto theend;
    }


    if (p_verbose > 1)
    {
	verbose_enter();
	if (SOURCING_NAME == NULL)
	    smsg(_("sourcing \"%s\""), fname);
	else
	    smsg(_("line %ld: sourcing \"%s\""), SOURCING_LNUM, fname);
	verbose_leave();
    }
    if (is_vimrc == DOSO_VIMRC)
	vimrc_found(fname_exp, (char_u *)"MYVIMRC");
    else if (is_vimrc == DOSO_GVIMRC)
	vimrc_found(fname_exp, (char_u *)"MYGVIMRC");

#ifdef USE_CRNL

    if (*p_ffs == NUL)
	cookie.fileformat = EOL_DOS;
    else
	cookie.fileformat = EOL_UNKNOWN;
#endif

    if (fname == NULL)


	cookie.sourcing_lnum = eap->line1 - 1;
    else
	cookie.sourcing_lnum = 0;

#ifdef FEAT_EVAL

    cookie.breakpoint = dbg_find_breakpoint(TRUE, fname_exp, (linenr_T)0);
    cookie.fname = fname_exp;
    cookie.dbg_tick = debug_tick;

    cookie.level = ex_nesting_level;
#endif


    estack_push(ETYPE_SCRIPT, fname_exp, 0);
    ESTACK_CHECK_SETUP

#ifdef STARTUPTIME
    if (time_fd != NULL)
	time_push(&tv_rel, &tv_start);
#endif


    sticky_cmdmod_flags = 0;

    save_current_sctx = current_sctx;
    if (cmdmod.cmod_flags & CMOD_VIM9CMD)


	current_sctx.sc_version = SCRIPT_VERSION_VIM9;
    else
	current_sctx.sc_version = 1;

#ifdef FEAT_EVAL
# ifdef FEAT_PROFILE
    if (do_profiling == PROF_YES)
	prof_child_enter(&wait_start);
# endif


    save_funccal(&funccalp_entry);

    current_sctx.sc_lnum = 0;


    current_sctx.sc_seq = ++last_current_SID_seq;
    if (sid > 0)
    {
	hashtab_T	*ht;
	int		todo;
	hashitem_T	*hi;
	dictitem_T	*di;


	current_sctx.sc_sid = sid;
	si = SCRIPT_ITEM(sid);
	if (si->sn_state == SN_STATE_NOT_LOADED)
	{

	    si->sn_state = SN_STATE_NEW;
	}
	else
	{
	    si->sn_state = SN_STATE_RELOAD;

	    if (!clearvars)
	    {


		ht = &SCRIPT_VARS(sid);
		todo = (int)ht->ht_used;
		for (hi = ht->ht_array; todo > 0; ++hi)
		    if (!HASHITEM_EMPTY(hi))
		    {
			--todo;
			di = HI2DI(hi);
			di->di_flags |= DI_FLAGS_RELOAD;
		    }

		mark_imports_for_reload(sid);
	    }
	    else
		clear_vim9_scriptlocal_vars(sid);


	    si->sn_version = 1;
	}
    }
    else
    {
	int error = OK;


	current_sctx.sc_sid = get_new_scriptitem(&error);
	if (error == FAIL)
	    goto almosttheend;
	si = SCRIPT_ITEM(current_sctx.sc_sid);
	si->sn_name = fname_exp;
	fname_exp = vim_strsave(si->sn_name);
	if (ret_sid != NULL)
	    *ret_sid = current_sctx.sc_sid;


	si->sn_is_vimrc = is_vimrc;
    }

# ifdef FEAT_PROFILE
    if (do_profiling == PROF_YES)
    {
	int	forceit;


	if (!si->sn_prof_on && has_profiling(TRUE, si->sn_name, &forceit))
	{
	    script_do_profile(si);
	    si->sn_pr_force = forceit;
	}
	if (si->sn_prof_on)
	{
	    ++si->sn_pr_count;
	    profile_start(&si->sn_pr_start);
	    profile_zero(&si->sn_pr_children);
	}
    }
# endif
#endif

    cookie.conv.vc_type = CONV_NONE;


    firstline = getsourceline(0, (void *)&cookie, 0, TRUE);
    if (firstline != NULL && STRLEN(firstline) >= 3 && firstline[0] == 0xef
			      && firstline[1] == 0xbb && firstline[2] == 0xbf)
    {

	convert_setup(&cookie.conv, (char_u *)"utf-8", p_enc);
	p = string_convert(&cookie.conv, firstline + 3, NULL);
	if (p == NULL)
	    p = vim_strsave(firstline + 3);
	if (p != NULL)
	{
	    vim_free(firstline);
	    firstline = p;
	}
    }


    do_cmdline(firstline, getsourceline, (void *)&cookie,
				     DOCMD_VERBOSE|DOCMD_NOWAIT|DOCMD_REPEAT);
    retval = OK;

#ifdef FEAT_PROFILE
    if (do_profiling == PROF_YES)
    {

	si = SCRIPT_ITEM(current_sctx.sc_sid);
	if (si->sn_prof_on)
	{
	    profile_end(&si->sn_pr_start);
	    profile_sub_wait(&wait_start, &si->sn_pr_start);
	    profile_add(&si->sn_pr_total, &si->sn_pr_start);
	    profile_self(&si->sn_pr_self, &si->sn_pr_start,
							 &si->sn_pr_children);
	}
    }
#endif

    if (got_int)
	emsg(_(e_interrupted));
    ESTACK_CHECK_NOW
    estack_pop();
    if (p_verbose > 1)
    {
	verbose_enter();
	smsg(_("finished sourcing %s"), fname);
	if (SOURCING_NAME != NULL)
	    smsg(_("continuing in %s"), SOURCING_NAME);
	verbose_leave();
    }
#ifdef STARTUPTIME
    if (time_fd != NULL)
    {
	vim_snprintf((char *)IObuff, IOSIZE, "sourcing %s", fname);
	time_msg((char *)IObuff, &tv_start);
	time_pop(&tv_rel);
    }
#endif

    if (!got_int)
	trigger_source_post = TRUE;

#ifdef FEAT_EVAL


    if (save_debug_break_level > ex_nesting_level
	    && debug_break_level == ex_nesting_level)
	++debug_break_level;
#endif

#ifdef FEAT_EVAL
almosttheend:


    si = SCRIPT_ITEM(current_sctx.sc_sid);
    if (si->sn_save_cpo != NULL && si->sn_is_vimrc == DOSO_NONE)
    {
	if (STRCMP(p_cpo, CPO_VIM) != 0)
	{
	    char_u *f;
	    char_u *t;


	    for (f = (char_u *)CPO_VIM; *f != NUL; ++f)
		if (vim_strchr(p_cpo, *f) == NULL
			&& (t = vim_strchr(si->sn_save_cpo, *f)) != NULL)

		    mch_memmove(t, t + 1, STRLEN(t));
	    for (f = p_cpo; *f != NUL; ++f)
		if (vim_strchr((char_u *)CPO_VIM, *f) == NULL
			&& vim_strchr(si->sn_save_cpo, *f) == NULL)
		{

		    t = alloc(STRLEN(si->sn_save_cpo) + 2);
		    if (t != NULL)
		    {
			*t = *f;
			STRCPY(t + 1, si->sn_save_cpo);
			vim_free(si->sn_save_cpo);
			si->sn_save_cpo = t;
		    }
		}
	}
	set_option_value((char_u *)"cpo", 0L, si->sn_save_cpo, OPT_NO_REDRAW);
    }
    VIM_CLEAR(si->sn_save_cpo);

    restore_funccal();
# ifdef FEAT_PROFILE
    if (do_profiling == PROF_YES)
	prof_child_exit(&wait_start);
# endif
#endif
    current_sctx = save_current_sctx;

    if (cookie.fp != NULL)
	fclose(cookie.fp);
    if (cookie.source_from_buf)
	ga_clear_strings(&cookie.buflines);
    vim_free(cookie.nextline);
    vim_free(firstline);
    convert_setup(&cookie.conv, NULL, NULL);

    if (trigger_source_post)
	apply_autocmds(EVENT_SOURCEPOST, fname_exp, fname_exp, FALSE, curbuf);

theend:
    vim_free(fname_exp);
    sticky_cmdmod_flags = save_sticky_cmdmod_flags;
#ifdef FEAT_EVAL
    estack_compiling = save_estack_compiling;
#endif
    return retval;
}
