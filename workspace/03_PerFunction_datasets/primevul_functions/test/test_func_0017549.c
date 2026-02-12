handle_version_response(int first, int *arg, int argc, char_u *tp)
{


    int version = arg[1];

    LOG_TR(("Received CRV response: %s", tp));
    crv_status.tr_progress = STATUS_GOT;
    did_cursorhold = TRUE;


    init_term_props(
#ifdef FEAT_EVAL
	    reset_term_props_on_termresponse
#else
	    FALSE
#endif
	    );


    if (tp[0] == CSI)
	switch_to_8bit();


    if (version > 20000)
	version = 0;


    if (first == '>' && argc == 3)
    {
	int need_flush = FALSE;


	if (arg[0] == 77)
	{

	    term_props[TPR_MOUSE].tpr_status = TPR_MOUSE_SGR;
	}


	if (version >= 141 && p_xtermcodes)
	{
	    LOG_TR(("Enable checking for XT codes"));
	    check_for_codes = TRUE;
	    need_gather = TRUE;
	    req_codes_from_term();
	}


	if (version == 100 && arg[0] == 0 && arg[2] == 0)
	{


	    if (mch_getenv((char_u *)"COLORS") == NULL)
		may_adjust_color_count(256);

	    term_props[TPR_MOUSE].tpr_status = TPR_MOUSE_SGR;
	}

	if (version == 95)
	{

	    if (arg[0] == 1 && arg[2] == 0)
	    {
		term_props[TPR_UNDERLINE_RGB].tpr_status = TPR_YES;
		term_props[TPR_MOUSE].tpr_status = TPR_MOUSE_SGR;
	    }

	    else if (arg[0] == 0 && arg[2] == 0)
	    {

		term_props[TPR_MOUSE].tpr_status = TPR_MOUSE_SGR;
	    }

	    else if (arg[0] == 0 && arg[2] == -1)
		term_props[TPR_UNDERLINE_RGB].tpr_status = TPR_YES;
	}


	if (arg[0] == 83)
	{

	    if (arg[1] >= 40700)
		term_props[TPR_MOUSE].tpr_status = TPR_MOUSE_SGR;
	    else
		term_props[TPR_MOUSE].tpr_status = TPR_MOUSE_XTERM;
	}


	if (term_props[TPR_MOUSE].tpr_status == TPR_UNKNOWN)
	{


	    if (version >= 277)
		term_props[TPR_MOUSE].tpr_status = TPR_MOUSE_SGR;
	    else if (version >= 95)
		term_props[TPR_MOUSE].tpr_status = TPR_MOUSE_XTERM2;
	}


	if (arg[1] >= 2500)
	    term_props[TPR_UNDERLINE_RGB].tpr_status = TPR_YES;

	else if (version == 136 && arg[2] == 0)
	{
	    term_props[TPR_UNDERLINE_RGB].tpr_status = TPR_YES;


	    if (arg[0] == 0)
	    {

		term_props[TPR_MOUSE].tpr_status = TPR_MOUSE_SGR;
	    }

	}


	if (arg[0] == 83 && arg[1] >= 30600)
	{
	    term_props[TPR_CURSOR_STYLE].tpr_status = TPR_NO;
	    term_props[TPR_CURSOR_BLINK].tpr_status = TPR_NO;
	}


	if (version < 95)
	    term_props[TPR_UNDERLINE_RGB].tpr_status = TPR_YES;


	if (version < 279)
	    term_props[TPR_CURSOR_STYLE].tpr_status = TPR_NO;


	if (term_props[TPR_UNDERLINE_RGB].tpr_status != TPR_YES
			&& *T_8U != NUL
			&& !option_was_set((char_u *)"t_8u"))
	{
	    set_string_option_direct((char_u *)"t_8u", -1, (char_u *)"",
								  OPT_FREE, 0);
	}
	if (*T_8U != NUL && write_t_8u_state == MAYBE)

	    redraw_later_clear();
	write_t_8u_state = OK;


	if (!option_was_set((char_u *)"ttym")
		&& (term_props[TPR_MOUSE].tpr_status == TPR_MOUSE_XTERM2
		    || term_props[TPR_MOUSE].tpr_status == TPR_MOUSE_SGR))
	{
	    set_option_value_give_err((char_u *)"ttym", 0L,
		    term_props[TPR_MOUSE].tpr_status == TPR_MOUSE_SGR
				    ? (char_u *)"sgr" : (char_u *)"xterm2", 0);
	}


	if (rcs_status.tr_progress == STATUS_GET
		&& term_props[TPR_CURSOR_STYLE].tpr_status == TPR_YES
		&& *T_CSH != NUL
		&& *T_CRS != NUL)
	{
	    MAY_WANT_TO_LOG_THIS;
	    LOG_TR(("Sending cursor style request"));
	    out_str(T_CRS);
	    termrequest_sent(&rcs_status);
	    need_flush = TRUE;
	}


	if (rbm_status.tr_progress == STATUS_GET
		&& term_props[TPR_CURSOR_BLINK].tpr_status == TPR_YES
		&& *T_CRC != NUL)
	{
	    MAY_WANT_TO_LOG_THIS;
	    LOG_TR(("Sending cursor blink mode request"));
	    out_str(T_CRC);
	    termrequest_sent(&rbm_status);
	    need_flush = TRUE;
	}

	if (need_flush)
	    out_flush();
    }
}
