ins_complete(int c, int enable_pum)
{
    int		n;
    int		save_w_wrow;
    int		save_w_leftcol;
    int		insert_match;

    compl_direction = ins_compl_key2dir(c);
    insert_match = ins_compl_use_match(c);

    if (!compl_started)
    {
	if (ins_compl_start() == FAIL)
	    return FAIL;
    }
    else if (insert_match && stop_arrow() == FAIL)
	return FAIL;

    compl_shown_match = compl_curr_match;
    compl_shows_dir = compl_direction;


    save_w_wrow = curwin->w_wrow;
    save_w_leftcol = curwin->w_leftcol;
    n = ins_compl_next(TRUE, ins_compl_key2count(c), insert_match, FALSE);


    ins_compl_upd_pum();

    if (n > 1)
	compl_matches = n;
    compl_curr_match = compl_shown_match;
    compl_direction = compl_shows_dir;


    if (got_int && !global_busy)
    {
	(void)vgetc();
	got_int = FALSE;
    }


    if (is_first_match(compl_first_match->cp_next))
    {


	if (compl_length > 1
		|| compl_status_adding()
		|| (ctrl_x_mode_not_default()
		    && !ctrl_x_mode_path_patterns()
		    && !ctrl_x_mode_path_defines()))
	    compl_cont_status &= ~CONT_N_ADDS;
    }

    if (compl_curr_match->cp_flags & CP_CONT_S_IPOS)
	compl_cont_status |= CONT_S_IPOS;
    else
	compl_cont_status &= ~CONT_S_IPOS;

    ins_compl_show_statusmsg();


    if (enable_pum && !compl_interrupted)
	show_pum(save_w_wrow, save_w_leftcol);

    compl_was_interrupted = compl_interrupted;
    compl_interrupted = FALSE;

    return OK;
}
