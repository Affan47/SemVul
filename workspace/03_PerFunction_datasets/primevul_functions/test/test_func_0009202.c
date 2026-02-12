do_shell(
    char_u	*cmd,
    int		flags)
{
    buf_T	*buf;
#if !defined(FEAT_GUI_MSWIN) || defined(VIMDLL)
    int		save_nwr;
#endif
#ifdef MSWIN
    int		winstart = FALSE;
#endif
    int		keep_termcap = !termcap_active;


    if (check_restricted() || check_secure())
    {
	msg_end();
	return;
    }

#ifdef MSWIN


    if (cmd != NULL)
	keep_termcap = winstart = (STRNICMP(cmd, "start ", 6) == 0);

# if defined(FEAT_GUI) && defined(FEAT_TERMINAL)

    if (gui.in_use && vim_strchr(p_go, GO_TERMINAL) != NULL)
	keep_termcap = TRUE;
# endif
#endif


    msg_putchar('\r');
    if (!autocmd_busy)
    {
	if (!keep_termcap)
	    stoptermcap();
    }
#ifdef MSWIN
    if (!winstart)
#endif
	msg_putchar('\n');


    if (p_warn && !autocmd_busy && msg_silent == 0)
	FOR_ALL_BUFFERS(buf)
	    if (bufIsChangedNotTerm(buf))
	    {
#ifdef FEAT_GUI_MSWIN
		if (!keep_termcap)
		    starttermcap();
#endif
		msg_puts(_("[No write since last change]\n"));
#ifdef FEAT_GUI_MSWIN
		if (!keep_termcap)
		    stoptermcap();
#endif
		break;
	    }


    if (!swapping_screen())
	windgoto(msg_row, msg_col);
    cursor_on();
    (void)call_shell(cmd, SHELL_COOKED | flags);
    did_check_timestamps = FALSE;
    need_check_timestamps = TRUE;


    if (!swapping_screen())
    {
	msg_row = Rows - 1;
	msg_col = 0;
    }

    if (autocmd_busy)
    {
	if (msg_silent == 0)
	    redraw_later_clear();
    }
    else
    {


#if !defined(FEAT_GUI_MSWIN) || defined(VIMDLL)
# ifdef VIMDLL
	if (!gui.in_use)
# endif
	{
	    if (cmd == NULL
# ifdef MSWIN
		    || (keep_termcap && !need_wait_return)
# endif
	       )
	    {
		if (msg_silent == 0)
		    redraw_later_clear();
		need_wait_return = FALSE;
	    }
	    else
	    {


		save_nwr = no_wait_return;
		if (swapping_screen())
		    no_wait_return = FALSE;
# ifdef AMIGA
		wait_return(term_console ? -1 : msg_silent == 0);
# else
		wait_return(msg_silent == 0);
# endif
		no_wait_return = save_nwr;
	    }
	}
#endif

	if (!keep_termcap)
	    starttermcap();


#ifdef AMIGA
	if (skip_redraw)
	{
	    if (msg_silent == 0)
		redraw_later_clear();
	}
	else if (term_console)
	{
	    OUT_STR(IF_EB("\033[0 q", ESC_STR "[0 q"));
	    if (got_int && msg_silent == 0)
		redraw_later_clear();
	    else
		must_redraw = 0;
	}
#endif
    }


    display_errors();

    apply_autocmds(EVENT_SHELLCMDPOST, NULL, NULL, FALSE, curbuf);
}
