current_search(
    long	count,
    int		forward)
{
    pos_T	start_pos;
    pos_T	end_pos;
    pos_T	orig_pos;
    pos_T	pos;
    int		i;
    int		dir;
    int		result;
    char_u	old_p_ws = p_ws;
    int		flags = 0;
    pos_T	save_VIsual = VIsual;
    int		zero_width;
    int		skip_first_backward;


    if (VIsual_active && *p_sel == 'e' && LT_POS(VIsual, curwin->w_cursor))
	dec_cursor();


    skip_first_backward = forward && VIsual_active
					   && LT_POS(curwin->w_cursor, VIsual);

    orig_pos = pos = curwin->w_cursor;
    if (VIsual_active)
    {
	if (forward)
	    incl(&pos);
	else
	    decl(&pos);
    }


    zero_width = is_zero_width(spats[last_idx].pat, TRUE, &curwin->w_cursor,
								      FORWARD);
    if (zero_width == -1)
	return FAIL;


    for (i = 0; i < 2; i++)
    {
	if (forward)
	{
	    if (i == 0 && skip_first_backward)
		continue;
	    dir = i;
	}
	else
	    dir = !i;

	flags = 0;
	if (!dir && !zero_width)
	    flags = SEARCH_END;
	end_pos = pos;


	if (i == 0)
	    p_ws = FALSE;

	result = searchit(curwin, curbuf, &pos, &end_pos,
		(dir ? FORWARD : BACKWARD),
		spats[last_idx].pat, (long) (i ? count : 1),
		SEARCH_KEEP | flags, RE_SEARCH, NULL);

	p_ws = old_p_ws;


	if (i == 1 && !result)
	{
	    curwin->w_cursor = orig_pos;
	    if (VIsual_active)
		VIsual = save_VIsual;
	    return FAIL;
	}
	else if (i == 0 && !result)
	{
	    if (forward)
	    {

		CLEAR_POS(&pos);
	    }
	    else
	    {


		pos.lnum = curwin->w_buffer->b_ml.ml_line_count;
		pos.col  = (colnr_T)STRLEN(
				ml_get(curwin->w_buffer->b_ml.ml_line_count));
	    }
	}
    }

    start_pos = pos;

    if (!VIsual_active)
	VIsual = start_pos;


    curwin->w_cursor = end_pos;
    if (LT_POS(VIsual, end_pos) && forward)
    {
	if (skip_first_backward)

	    curwin->w_cursor = pos;
	else

	    dec_cursor();
    }
    else if (VIsual_active && LT_POS(curwin->w_cursor, VIsual) && forward)
	curwin->w_cursor = pos;
    VIsual_active = TRUE;
    VIsual_mode = 'v';

    if (*p_sel == 'e')
    {

	if (forward && LTOREQ_POS(VIsual, curwin->w_cursor))
	    inc_cursor();
	else if (!forward && LTOREQ_POS(curwin->w_cursor, VIsual))
	    inc(&VIsual);
    }

#ifdef FEAT_FOLDING
    if (fdo_flags & FDO_SEARCH && KeyTyped)
	foldOpenCursor();
#endif

    may_start_select('c');
    setmouse();
#ifdef FEAT_CLIPBOARD


    clip_star.vmode = NUL;
#endif
    redraw_curbuf_later(INVERTED);
    showmode();

    return OK;
}
