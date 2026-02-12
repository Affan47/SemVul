settmode(tmode_T tmode)
{
#ifdef FEAT_GUI

    if (gui.in_use)
	return;
#endif

    if (full_screen)
    {


	if (tmode != cur_tmode)
	{
#ifdef FEAT_TERMRESPONSE
# ifdef FEAT_GUI
	    if (!gui.in_use && !gui.starting)
# endif
	    {


		if (tmode != TMODE_RAW && termrequest_any_pending())
		    (void)vpeekc_nomap();
		check_for_codes_from_term();
	    }
#endif
	    if (tmode != TMODE_RAW)
		mch_setmouse(FALSE);


	    if (termcap_active && tmode != TMODE_SLEEP
						   && cur_tmode != TMODE_SLEEP)
	    {
		MAY_WANT_TO_LOG_THIS;

		if (tmode != TMODE_RAW)
		{
		    out_str(T_BD);
		    out_str(T_CTE);
		}
		else
		{
		    out_str(T_BE);

		    out_str(T_CTI);
		}
	    }
	    out_flush();
	    mch_settmode(tmode);
	    cur_tmode = tmode;
	    if (tmode == TMODE_RAW)
		setmouse();
	    out_flush();
	}
#ifdef FEAT_TERMRESPONSE
	may_req_termresponse();
#endif
    }
}
