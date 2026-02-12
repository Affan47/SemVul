ins_compl_start(void)
{
    char_u	*line;
    int		startcol = 0;
    colnr_T	curs_col;
    int		line_invalid = FALSE;
    int		save_did_ai = did_ai;
    int		flags = CP_ORIGINAL_TEXT;


    did_ai = FALSE;
    did_si = FALSE;
    can_si = FALSE;
    can_si_back = FALSE;
    if (stop_arrow() == FAIL)
	return FAIL;

    line = ml_get(curwin->w_cursor.lnum);
    curs_col = curwin->w_cursor.col;
    compl_pending = 0;

    if ((compl_cont_status & CONT_INTRPT) == CONT_INTRPT
	    && compl_cont_mode == ctrl_x_mode)


	ins_compl_continue_search(line);
    else
	compl_cont_status &= CONT_LOCAL;

    if (!compl_status_adding())
    {
	compl_cont_mode = ctrl_x_mode;
	if (ctrl_x_mode_not_default())

	    compl_cont_status = 0;
	compl_cont_status |= CONT_N_ADDS;
	compl_startpos = curwin->w_cursor;
	startcol = (int)curs_col;
	compl_col = 0;
    }


    if (compl_get_info(line, startcol, curs_col, &line_invalid) == FAIL)
    {
	if (ctrl_x_mode_function() || ctrl_x_mode_omni()
				|| thesaurus_func_complete(ctrl_x_mode))

	    did_ai = save_did_ai;
	return FAIL;
    }

    if (line_invalid)
	line = ml_get(curwin->w_cursor.lnum);

    if (compl_status_adding())
    {
	edit_submode_pre = (char_u *)_(" Adding");
	if (ctrl_x_mode_line_or_eval())
	{

	    char_u *old = curbuf->b_p_com;

	    curbuf->b_p_com = (char_u *)"";
	    compl_startpos.lnum = curwin->w_cursor.lnum;
	    compl_startpos.col = compl_col;
	    ins_eol('\r');
	    curbuf->b_p_com = old;
	    compl_length = 0;
	    compl_col = curwin->w_cursor.col;
	}
    }
    else
    {
	edit_submode_pre = NULL;
	compl_startpos.col = compl_col;
    }

    if (compl_cont_status & CONT_LOCAL)
	edit_submode = (char_u *)_(ctrl_x_msgs[CTRL_X_LOCAL_MSG]);
    else
	edit_submode = (char_u *)_(CTRL_X_MSG(ctrl_x_mode));


    ins_compl_fixRedoBufForLeader(NULL);


    vim_free(compl_orig_text);
    compl_orig_text = vim_strnsave(line + compl_col, compl_length);
    if (p_ic)
	flags |= CP_ICASE;
    if (compl_orig_text == NULL || ins_compl_add(compl_orig_text,
		-1, NULL, NULL, NULL, 0, flags, FALSE) != OK)
    {
	VIM_CLEAR(compl_pattern);
	VIM_CLEAR(compl_orig_text);
	return FAIL;
    }


    edit_submode_extra = (char_u *)_("-- Searching...");
    edit_submode_highl = HLF_COUNT;
    showmode();
    edit_submode_extra = NULL;
    out_flush();

    return OK;
}
