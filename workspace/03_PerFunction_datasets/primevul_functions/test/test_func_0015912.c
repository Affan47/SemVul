do_check_cursorbind(void)
{
    linenr_T	line = curwin->w_cursor.lnum;
    colnr_T	col = curwin->w_cursor.col;
    colnr_T	coladd = curwin->w_cursor.coladd;
    colnr_T	curswant = curwin->w_curswant;
    int		set_curswant = curwin->w_set_curswant;
    win_T	*old_curwin = curwin;
    buf_T	*old_curbuf = curbuf;
    int		restart_edit_save;
    int		old_VIsual_select = VIsual_select;
    int		old_VIsual_active = VIsual_active;


    VIsual_select = VIsual_active = 0;
    FOR_ALL_WINDOWS(curwin)
    {
	curbuf = curwin->w_buffer;

	if (curwin != old_curwin && curwin->w_p_crb)
	{
# ifdef FEAT_DIFF
	    if (curwin->w_p_diff)
		curwin->w_cursor.lnum =
				 diff_get_corresponding_line(old_curbuf, line);
	    else
# endif
		curwin->w_cursor.lnum = line;
	    curwin->w_cursor.col = col;
	    curwin->w_cursor.coladd = coladd;
	    curwin->w_curswant = curswant;
	    curwin->w_set_curswant = set_curswant;


	    restart_edit_save = restart_edit;
	    restart_edit = TRUE;
	    check_cursor();
# ifdef FEAT_SYN_HL
	    if (curwin->w_p_cul || curwin->w_p_cuc)
		validate_cursor();
# endif
	    restart_edit = restart_edit_save;

	    if (has_mbyte)
		mb_adjust_cursor();
	    redraw_later(VALID);


	    if (!curwin->w_p_scb)
		update_topline();
	    curwin->w_redr_status = TRUE;
	}
    }


    VIsual_select = old_VIsual_select;
    VIsual_active = old_VIsual_active;
    curwin = old_curwin;
    curbuf = old_curbuf;
}
