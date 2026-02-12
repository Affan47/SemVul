current_block(
    oparg_T	*oap,
    long	count,
    int		include,
    int		what,
    int		other)
{
    pos_T	old_pos;
    pos_T	*pos = NULL;
    pos_T	start_pos;
    pos_T	*end_pos;
    pos_T	old_start, old_end;
    char_u	*save_cpo;
    int		sol = FALSE;

    old_pos = curwin->w_cursor;
    old_end = curwin->w_cursor;
    old_start = old_end;

    if (!VIsual_active || EQUAL_POS(VIsual, curwin->w_cursor))
    {
	setpcmark();
	if (what == '{')
	    while (inindent(1))
		if (inc_cursor() != 0)
		    break;
	if (gchar_cursor() == what)

	    ++curwin->w_cursor.col;
    }
    else if (LT_POS(VIsual, curwin->w_cursor))
    {
	old_start = VIsual;
	curwin->w_cursor = VIsual;
    }
    else
	old_end = VIsual;

    save_cpo = p_cpo;
    p_cpo = (char_u *)(vim_strchr(p_cpo, CPO_MATCHBSL) != NULL ? "%M" : "%");
    if ((pos = findmatch(NULL, what)) != NULL)
    {
	while (count-- > 0)
	{
	    if ((pos = findmatch(NULL, what)) == NULL)
		break;
	    curwin->w_cursor = *pos;
	    start_pos = *pos;
	}
    }
    else
    {
	while (count-- > 0)
	{
	    if ((pos = findmatchlimit(NULL, what, FM_FORWARD, 0)) == NULL)
		break;
	    curwin->w_cursor = *pos;
	    start_pos = *pos;
	}
    }
    p_cpo = save_cpo;

    if (pos == NULL || (end_pos = findmatch(NULL, other)) == NULL)
    {
	curwin->w_cursor = old_pos;
	return FAIL;
    }
    curwin->w_cursor = *end_pos;

    while (!include)
    {
	incl(&start_pos);
	sol = (curwin->w_cursor.col == 0);
	decl(&curwin->w_cursor);
	while (inindent(1))
	{
	    sol = TRUE;
	    if (decl(&curwin->w_cursor) != 0)
		break;
	}

	if (!LT_POS(start_pos, old_start) && !LT_POS(old_end, curwin->w_cursor)
		&& VIsual_active)
	{
	    curwin->w_cursor = old_start;
	    decl(&curwin->w_cursor);
	    if ((pos = findmatch(NULL, what)) == NULL)
	    {
		curwin->w_cursor = old_pos;
		return FAIL;
	    }
	    start_pos = *pos;
	    curwin->w_cursor = *pos;
	    if ((end_pos = findmatch(NULL, other)) == NULL)
	    {
		curwin->w_cursor = old_pos;
		return FAIL;
	    }
	    curwin->w_cursor = *end_pos;
	}
	else
	    break;
    }

    if (VIsual_active)
    {
	if (*p_sel == 'e')
	    inc(&curwin->w_cursor);
	if (sol && gchar_cursor() != NUL)
	    inc(&curwin->w_cursor);
	VIsual = start_pos;
	VIsual_mode = 'v';
	redraw_curbuf_later(INVERTED);
	showmode();
    }
    else
    {
	oap->start = start_pos;
	oap->motion_type = MCHAR;
	oap->inclusive = FALSE;
	if (sol)
	    incl(&curwin->w_cursor);
	else if (LTOREQ_POS(start_pos, curwin->w_cursor))

	    oap->inclusive = TRUE;
	else

	    curwin->w_cursor = start_pos;
    }

    return OK;
}
}
