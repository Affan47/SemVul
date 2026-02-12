set_termname(char_u *term)
{
    struct builtin_term *termp;
#ifdef HAVE_TGETENT
    int		builtin_first = p_tbi;
    int		try;
    int		termcap_cleared = FALSE;
#endif
    int		width = 0, height = 0;
    char	*error_msg = NULL;
    char_u	*bs_p, *del_p;


    if (silent_mode)
	return OK;

    detected_8bit = FALSE;

    if (term_is_builtin(term))
    {
	term += 8;
#ifdef HAVE_TGETENT
	builtin_first = 1;
#endif
    }


#ifdef HAVE_TGETENT
    for (try = builtin_first ? 0 : 1; try < 3; ++try)
    {


	if (try == 1)
	{
	    char_u	    tbuf[TBUFSZ];


	    if ((error_msg = invoke_tgetent(tbuf, term)) == NULL)
	    {
		if (!termcap_cleared)
		{
		    clear_termoptions();
		    termcap_cleared = TRUE;
		}

		get_term_entries(&height, &width);
	    }
	}
	else
#endif


	{
#ifdef HAVE_TGETENT


	    if (try == 2 && builtin_first && termcap_cleared)
		break;
#endif


	    termp = find_builtin_term(term);
	    if (termp->bt_string == NULL)
	    {
#ifdef HAVE_TGETENT


		if (try == 0)
		    continue;
		if (termcap_cleared)
		    break;
#endif
		report_term_error(error_msg, term);


		if (starting != NO_SCREEN)
		{
		    screen_start();
		    wait_return(TRUE);
		    return FAIL;
		}
		term = DEFAULT_TERM;
		report_default_term(term);
		set_string_option_direct((char_u *)"term", -1, term,
								 OPT_FREE, 0);
		display_errors();
	    }
	    out_flush();
#ifdef HAVE_TGETENT
	    if (!termcap_cleared)
	    {
#endif
		clear_termoptions();
#ifdef HAVE_TGETENT
		termcap_cleared = TRUE;
	    }
#endif
	    parse_builtin_tcap(term);
#ifdef FEAT_GUI
	    if (term_is_gui(term))
	    {
		out_flush();
		gui_init();


		if (!gui.in_use)
		    return FAIL;
#ifdef HAVE_TGETENT
		break;
#endif
	    }
#endif
	}
#ifdef HAVE_TGETENT
    }
#endif


    if (STRCMP(term, "pcterm") == 0)
	T_CCS = (char_u *)"yes";
    else
	T_CCS = empty_option;

#ifdef UNIX


# ifdef FEAT_GUI
    if (!gui.in_use)
# endif
	get_stty();
#endif


#ifdef FEAT_GUI
    if (!gui.in_use)
#endif
    {
	bs_p = find_termcode((char_u *)"kb");
	del_p = find_termcode((char_u *)"kD");
	if (bs_p == NULL || *bs_p == NUL)
	    add_termcode((char_u *)"kb", (bs_p = (char_u *)CTRL_H_STR), FALSE);
	if ((del_p == NULL || *del_p == NUL) &&
					    (bs_p == NULL || *bs_p != DEL))
	    add_termcode((char_u *)"kD", (char_u *)DEL_STR, FALSE);
    }

#if defined(UNIX) || defined(VMS)
    term_is_xterm = vim_is_xterm(term);
#endif
#ifdef FEAT_TERMRESPONSE


    init_term_props(FALSE);
#endif

#if defined(UNIX) || defined(VMS)


    {
	char_u	*p = (char_u *)"";

# ifdef FEAT_MOUSE_XTERM
	if (use_xterm_like_mouse(term))
	{
	    if (use_xterm_mouse())
		p = NULL;
	    else
		p = (char_u *)"xterm";
	}
# endif
	if (p != NULL)
	{
	    set_option_value_give_err((char_u *)"ttym", 0L, p, 0);


	    reset_option_was_set((char_u *)"ttym");
	}
	if (p == NULL
#  ifdef FEAT_GUI
		|| gui.in_use
#  endif
		)
	    check_mouse_termcode();
    }
#else
    set_mouse_termcode(KS_MOUSE, (char_u *)"\233M");
#endif

#ifdef FEAT_MOUSE_XTERM

    if (use_xterm_like_mouse(term))
    {
	char_u name[3];


	name[0] = KS_EXTRA;
	name[1] = KE_FOCUSGAINED;
	name[2] = NUL;
	add_termcode(name, (char_u *)"\033[I", FALSE);


	name[1] = KE_FOCUSLOST;
	add_termcode(name, (char_u *)"\033[O", FALSE);

	need_gather = TRUE;
    }
#endif
#if (defined(UNIX) || defined(VMS))

    focus_state = MAYBE;
#endif

#ifdef USE_TERM_CONSOLE

    if (STRCMP(term, DEFAULT_TERM) != 0)
	term_console = FALSE;
    else
    {
	term_console = TRUE;
# ifdef AMIGA
	win_resize_on();
# endif
    }
#endif

#if defined(UNIX) || defined(VMS)


    if (vim_is_fastterm(term))
	p_tf = TRUE;
#endif
#ifdef USE_TERM_CONSOLE


    if (term_console)
	p_tf = TRUE;
#endif

    ttest(TRUE);

    full_screen = TRUE;
    set_term_defaults();
#ifdef FEAT_TERMRESPONSE
    LOG_TR(("setting crv_status to STATUS_GET"));
    crv_status.tr_progress = STATUS_GET;
    write_t_8u_state = FALSE;
#endif


    if (starting != NO_SCREEN)
    {
	starttermcap();
	setmouse();
	maketitle();
    }


    if (width <= 0 || height <= 0)
    {


	width = 80;
#if defined(MSWIN)
	height = 25;
#else
	height = 24;
#endif
    }
    set_shellsize(width, height, FALSE);
    if (starting != NO_SCREEN)
    {
	if (scroll_region)
	    scroll_region_reset();
	check_map_keycodes();

	{
	    buf_T	*buf;
	    aco_save_T	aco;


	    FOR_ALL_BUFFERS(buf)
	    {
		if (curbuf->b_ml.ml_mfp != NULL)
		{
		    aucmd_prepbuf(&aco, buf);
		    apply_autocmds(EVENT_TERMCHANGED, NULL, NULL, FALSE,
								      curbuf);

		    aucmd_restbuf(&aco);
		}
	    }
	}
    }

#ifdef FEAT_TERMRESPONSE
    may_req_termresponse();
#endif

    return OK;
}
