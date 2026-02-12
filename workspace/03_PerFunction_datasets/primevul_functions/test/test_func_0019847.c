nv_visual(cmdarg_T *cap)
{
    if (cap->cmdchar == Ctrl_Q)
	cap->cmdchar = Ctrl_V;


    if (cap->oap->op_type != OP_NOP)
    {
	motion_force = cap->oap->motion_force = cap->cmdchar;
	finish_op = FALSE;
	return;
    }

    VIsual_select = cap->arg;
    if (VIsual_active)
    {
	if (VIsual_mode == cap->cmdchar)
	    end_visual_mode();
	else
	{
	    VIsual_mode = cap->cmdchar;
	    showmode();
	    trigger_modechanged();
	}
	redraw_curbuf_later(INVERTED);
    }
    else
    {
	check_visual_highlight();
	if (cap->count0 > 0 && resel_VIsual_mode != NUL)
	{

	    VIsual = curwin->w_cursor;

	    VIsual_active = TRUE;
	    VIsual_reselect = TRUE;
	    if (!cap->arg)

		may_start_select('c');
	    setmouse();
	    if (p_smd && msg_silent == 0)
		redraw_cmdline = TRUE;


	    if (resel_VIsual_mode != 'v' || resel_VIsual_line_count > 1)
	    {
		curwin->w_cursor.lnum +=
				    resel_VIsual_line_count * cap->count0 - 1;
		check_cursor();
	    }
	    VIsual_mode = resel_VIsual_mode;
	    if (VIsual_mode == 'v')
	    {
		if (resel_VIsual_line_count <= 1)
		{
		    validate_virtcol();
		    curwin->w_curswant = curwin->w_virtcol
					+ resel_VIsual_vcol * cap->count0 - 1;
		}
		else
		    curwin->w_curswant = resel_VIsual_vcol;
		coladvance(curwin->w_curswant);
	    }
	    if (resel_VIsual_vcol == MAXCOL)
	    {
		curwin->w_curswant = MAXCOL;
		coladvance((colnr_T)MAXCOL);
	    }
	    else if (VIsual_mode == Ctrl_V)
	    {
		validate_virtcol();
		curwin->w_curswant = curwin->w_virtcol
					+ resel_VIsual_vcol * cap->count0 - 1;
		coladvance(curwin->w_curswant);
	    }
	    else
		curwin->w_set_curswant = TRUE;
	    redraw_curbuf_later(INVERTED);
	}
	else
	{
	    if (!cap->arg)

		may_start_select('c');
	    n_start_visual_mode(cap->cmdchar);
	    if (VIsual_mode != 'V' && *p_sel == 'e')
		++cap->count1;
	    if (cap->count0 > 0 && --cap->count1 > 0)
	    {

		if (VIsual_mode == 'v' || VIsual_mode == Ctrl_V)
		    nv_right(cap);
		else if (VIsual_mode == 'V')
		    nv_down(cap);
	    }
	}
    }
}
