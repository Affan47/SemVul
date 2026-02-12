current_word(
    oparg_T	*oap,
    long	count,
    int		include,
    int		bigword)
{
    pos_T	start_pos;
    pos_T	pos;
    int		inclusive = TRUE;
    int		include_white = FALSE;

    cls_bigword = bigword;
    CLEAR_POS(&start_pos);


    if (VIsual_active && *p_sel == 'e' && LT_POS(VIsual, curwin->w_cursor))
	dec_cursor();


    if (!VIsual_active || EQUAL_POS(curwin->w_cursor, VIsual))
    {


	back_in_line();
	start_pos = curwin->w_cursor;


	if ((cls() == 0) == include)
	{
	    if (end_word(1L, bigword, TRUE, TRUE) == FAIL)
		return FAIL;
	}
	else
	{


	    fwd_word(1L, bigword, TRUE);
	    if (curwin->w_cursor.col == 0)
		decl(&curwin->w_cursor);
	    else
		oneleft();

	    if (include)
		include_white = TRUE;
	}

	if (VIsual_active)
	{

	    VIsual = start_pos;
	    redraw_curbuf_later(INVERTED);
	}
	else
	{
	    oap->start = start_pos;
	    oap->motion_type = MCHAR;
	}
	--count;
    }


    while (count > 0)
    {
	inclusive = TRUE;
	if (VIsual_active && LT_POS(curwin->w_cursor, VIsual))
	{


	    if (decl(&curwin->w_cursor) == -1)
		return FAIL;
	    if (include != (cls() != 0))
	    {
		if (bck_word(1L, bigword, TRUE) == FAIL)
		    return FAIL;
	    }
	    else
	    {
		if (bckend_word(1L, bigword, TRUE) == FAIL)
		    return FAIL;
		(void)incl(&curwin->w_cursor);
	    }
	}
	else
	{


	    if (incl(&curwin->w_cursor) == -1)
		return FAIL;
	    if (include != (cls() == 0))
	    {
		if (fwd_word(1L, bigword, TRUE) == FAIL && count > 1)
		    return FAIL;


		if (oneleft() == FAIL)
		    inclusive = FALSE;
	    }
	    else
	    {
		if (end_word(1L, bigword, TRUE, TRUE) == FAIL)
		    return FAIL;
	    }
	}
	--count;
    }

    if (include_white && (cls() != 0
		 || (curwin->w_cursor.col == 0 && !inclusive)))
    {


	pos = curwin->w_cursor;
	curwin->w_cursor = start_pos;
	if (oneleft() == OK)
	{
	    back_in_line();
	    if (cls() == 0 && curwin->w_cursor.col > 0)
	    {
		if (VIsual_active)
		    VIsual = curwin->w_cursor;
		else
		    oap->start = curwin->w_cursor;
	    }
	}
	curwin->w_cursor = pos;
    }

    if (VIsual_active)
    {
	if (*p_sel == 'e' && inclusive && LTOREQ_POS(VIsual, curwin->w_cursor))
	    inc_cursor();
	if (VIsual_mode == 'V')
	{
	    VIsual_mode = 'v';
	    redraw_cmdline = TRUE;
	}
    }
    else
	oap->inclusive = inclusive;

    return OK;
}
