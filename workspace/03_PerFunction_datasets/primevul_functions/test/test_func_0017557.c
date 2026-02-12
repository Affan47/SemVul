stoptermcap(void)
{
    screen_stop_highlight();
    reset_cterm_colors();
    if (termcap_active)
    {
#ifdef FEAT_TERMRESPONSE
# ifdef FEAT_GUI
	if (!gui.in_use && !gui.starting)
# endif
	{

	    if (termrequest_any_pending())
	    {
# ifdef UNIX

		mch_delay(100L, 0);
# endif
# ifdef TCIFLUSH

		if (exiting)
		    tcflush(fileno(stdin), TCIFLUSH);
# endif
	    }


	    check_for_codes_from_term();
	}
#endif
	MAY_WANT_TO_LOG_THIS;

#if defined(UNIX) || defined(VMS)

	if (p_ek && *T_FD != NUL)
	    out_str(T_FD);
#endif

	out_str(T_BD);
	out_str(T_KE);
	out_flush();
	termcap_active = FALSE;
	cursor_on();
	out_str(T_CTE);
	out_str(T_TE);
	screen_start();
	out_flush();
    }
}
