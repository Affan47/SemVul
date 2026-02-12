open_cmdwin(void)
{
    bufref_T		old_curbuf;
    win_T		*old_curwin = curwin;
    bufref_T		bufref;
    win_T		*wp;
    int			i;
    linenr_T		lnum;
    int			histtype;
    garray_T		winsizes;
    int			save_restart_edit = restart_edit;
    int			save_State = State;
    int			save_exmode = exmode_active;
#ifdef FEAT_RIGHTLEFT
    int			save_cmdmsg_rl = cmdmsg_rl;
#endif
#ifdef FEAT_FOLDING
    int			save_KeyTyped;
#endif


    if (cmdwin_type != 0
# if defined(FEAT_CRYPT) || defined(FEAT_EVAL)
	    || cmdline_star > 0
# endif
	    )
    {
	beep_flush();
	return K_IGNORE;
    }
    set_bufref(&old_curbuf, curbuf);


    win_size_save(&winsizes);


    pum_undisplay();


    cmdmod.cmod_tab = 0;
    cmdmod.cmod_flags |= CMOD_NOSWAPFILE;


    if (win_split((int)p_cwh, WSP_BOT) == FAIL)
    {
	beep_flush();
	ga_clear(&winsizes);
	return K_IGNORE;
    }

    got_int = FALSE;


    cmdwin_type = get_cmdline_type();


    if (do_ecmd(0, NULL, NULL, NULL, ECMD_ONE, ECMD_HIDE, NULL) == FAIL)
    {

	win_close(curwin, TRUE);
	ga_clear(&winsizes);
	cmdwin_type = 0;
	return Ctrl_C;
    }

    apply_autocmds(EVENT_BUFFILEPRE, NULL, NULL, FALSE, curbuf);
    (void)setfname(curbuf, (char_u *)_("[Command Line]"), NULL, TRUE);
    apply_autocmds(EVENT_BUFFILEPOST, NULL, NULL, FALSE, curbuf);
    set_option_value_give_err((char_u *)"bt",
					    0L, (char_u *)"nofile", OPT_LOCAL);
    curbuf->b_p_ma = TRUE;
#ifdef FEAT_FOLDING
    curwin->w_p_fen = FALSE;
#endif
# ifdef FEAT_RIGHTLEFT
    curwin->w_p_rl = cmdmsg_rl;
    cmdmsg_rl = FALSE;
# endif
    RESET_BINDING(curwin);


    ++curbuf_lock;


    need_wait_return = FALSE;

    histtype = hist_char2type(cmdwin_type);
    if (histtype == HIST_CMD || histtype == HIST_DEBUG)
    {
	if (p_wc == TAB)
	{
	    add_map((char_u *)"<buffer> <Tab> <C-X><C-V>", INSERT);
	    add_map((char_u *)"<buffer> <Tab> a<C-X><C-V>", NORMAL);
	}
	set_option_value_give_err((char_u *)"ft",
					       0L, (char_u *)"vim", OPT_LOCAL);
    }
    --curbuf_lock;


    curbuf->b_p_tw = 0;


    init_history();
    if (get_hislen() > 0)
    {
	i = *get_hisidx(histtype);
	if (i >= 0)
	{
	    lnum = 0;
	    do
	    {
		if (++i == get_hislen())
		    i = 0;
		if (get_histentry(histtype)[i].hisstr != NULL)
		    ml_append(lnum++, get_histentry(histtype)[i].hisstr,
							   (colnr_T)0, FALSE);
	    }
	    while (i != *get_hisidx(histtype));
	}
    }


    ml_replace(curbuf->b_ml.ml_line_count, ccline.cmdbuff, TRUE);
    curwin->w_cursor.lnum = curbuf->b_ml.ml_line_count;
    curwin->w_cursor.col = ccline.cmdpos;
    changed_line_abv_curs();
    invalidate_botline();
    redraw_later(SOME_VALID);


    exmode_active = 0;

    State = NORMAL;
    setmouse();


    cmdwin_result = 0;


    trigger_cmd_autocmd(cmdwin_type, EVENT_CMDWINENTER);
    if (restart_edit != 0)
	stuffcharReadbuff(K_NOP);

    i = RedrawingDisabled;
    RedrawingDisabled = 0;


    main_loop(TRUE, FALSE);

    RedrawingDisabled = i;

# ifdef FEAT_FOLDING
    save_KeyTyped = KeyTyped;
# endif


    trigger_cmd_autocmd(cmdwin_type, EVENT_CMDWINLEAVE);

# ifdef FEAT_FOLDING

    KeyTyped = save_KeyTyped;
# endif

    cmdwin_type = 0;
    exmode_active = save_exmode;


    if (!win_valid(old_curwin) || !bufref_valid(&old_curbuf))
    {
	cmdwin_result = Ctrl_C;
	emsg(_(e_active_window_or_buffer_deleted));
    }
    else
    {
# if defined(FEAT_EVAL)

	if (aborting() && cmdwin_result != K_IGNORE)
	    cmdwin_result = Ctrl_C;
# endif

	vim_free(ccline.cmdbuff);
	if (cmdwin_result == K_XF1 || cmdwin_result == K_XF2)
	{
	    char *p = (cmdwin_result == K_XF2) ? "qa" : "qa!";

	    if (histtype == HIST_CMD)
	    {

		ccline.cmdbuff = vim_strsave((char_u *)p);
		cmdwin_result = CAR;
	    }
	    else
	    {

		ccline.cmdbuff = NULL;
		stuffcharReadbuff(':');
		stuffReadbuff((char_u *)p);
		stuffcharReadbuff(CAR);
	    }
	}
	else if (cmdwin_result == K_XF2)
	{
	    ccline.cmdbuff = vim_strsave((char_u *)"qa");
	    cmdwin_result = CAR;
	}
	else if (cmdwin_result == Ctrl_C)
	{


	    ccline.cmdbuff = NULL;
	}
	else
	    ccline.cmdbuff = vim_strsave(ml_get_curline());
	if (ccline.cmdbuff == NULL)
	{
	    ccline.cmdbuff = vim_strsave((char_u *)"");
	    ccline.cmdlen = 0;
	    ccline.cmdbufflen = 1;
	    ccline.cmdpos = 0;
	    cmdwin_result = Ctrl_C;
	}
	else
	{
	    ccline.cmdlen = (int)STRLEN(ccline.cmdbuff);
	    ccline.cmdbufflen = ccline.cmdlen + 1;
	    ccline.cmdpos = curwin->w_cursor.col;
	    if (ccline.cmdpos > ccline.cmdlen)
		ccline.cmdpos = ccline.cmdlen;
	    if (cmdwin_result == K_IGNORE)
	    {
		set_cmdspos_cursor();
		redrawcmd();
	    }
	}

# ifdef FEAT_CONCEAL

	curwin->w_p_cole = 0;
# endif

	wp = curwin;
	set_bufref(&bufref, curbuf);
	win_goto(old_curwin);


	if (win_valid(wp) && wp != curwin)
	    win_close(wp, TRUE);


	if (bufref_valid(&bufref) && bufref.br_buf != curbuf)
	    close_buffer(NULL, bufref.br_buf, DOBUF_WIPE, FALSE, FALSE);


	win_size_restore(&winsizes);
    }

    ga_clear(&winsizes);
    restart_edit = save_restart_edit;
# ifdef FEAT_RIGHTLEFT
    cmdmsg_rl = save_cmdmsg_rl;
# endif

    State = save_State;
    setmouse();

    return cmdwin_result;
}
