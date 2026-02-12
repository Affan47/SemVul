starttermcap(void)
{
    if (full_screen && !termcap_active)
    {
	MAY_WANT_TO_LOG_THIS;

	out_str(T_TI);
	out_str(T_CTI);
	out_str(T_KS);
	out_str(T_BE);

#if defined(UNIX) || defined(VMS)

	if (p_ek && *T_FE != NUL)
	    out_str(T_FE);
#endif

	out_flush();
	termcap_active = TRUE;
	screen_start();
#ifdef FEAT_TERMRESPONSE
# ifdef FEAT_GUI
	if (!gui.in_use && !gui.starting)
# endif
	{
	    may_req_termresponse();


	    if (crv_status.tr_progress == STATUS_SENT)
		check_for_codes_from_term();
	}
#endif
    }
}
