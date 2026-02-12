current_quote(
    oparg_T	*oap,
    long	count,
    int		include,
    int		quotechar)
{
    char_u	*line = ml_get_curline();
    int		col_end;
    int		col_start = curwin->w_cursor.col;
    int		inclusive = FALSE;
    int		vis_empty = TRUE;
    int		vis_bef_curs = FALSE;
    int		did_exclusive_adj = FALSE;
    int		inside_quotes = FALSE;
    int		selected_quote = FALSE;
    int		i;
    int		restore_vis_bef = FALSE;


    if (VIsual_active)
    {

	if (VIsual.lnum != curwin->w_cursor.lnum)
	    return FALSE;

	vis_bef_curs = LT_POS(VIsual, curwin->w_cursor);
	vis_empty = EQUAL_POS(VIsual, curwin->w_cursor);
	if (*p_sel == 'e')
	{
	    if (vis_bef_curs)
	    {
		dec_cursor();
		did_exclusive_adj = TRUE;
	    }
	    else if (!vis_empty)
	    {
		dec(&VIsual);
		did_exclusive_adj = TRUE;
	    }
	    vis_empty = EQUAL_POS(VIsual, curwin->w_cursor);
	    if (!vis_bef_curs && !vis_empty)
	    {

		pos_T t = curwin->w_cursor;

		curwin->w_cursor = VIsual;
		VIsual = t;
		vis_bef_curs = TRUE;
		restore_vis_bef = TRUE;
	    }
	}
    }

    if (!vis_empty)
    {


	if (vis_bef_curs)
	{
	    inside_quotes = VIsual.col > 0
			&& line[VIsual.col - 1] == quotechar
			&& line[curwin->w_cursor.col] != NUL
			&& line[curwin->w_cursor.col + 1] == quotechar;
	    i = VIsual.col;
	    col_end = curwin->w_cursor.col;
	}
	else
	{
	    inside_quotes = curwin->w_cursor.col > 0
			&& line[curwin->w_cursor.col - 1] == quotechar
			&& line[VIsual.col] != NUL
			&& line[VIsual.col + 1] == quotechar;
	    i = curwin->w_cursor.col;
	    col_end = VIsual.col;
	}


	while (i <= col_end)
	    if (line[i++] == quotechar)
	    {
		selected_quote = TRUE;
		break;
	    }
    }

    if (!vis_empty && line[col_start] == quotechar)
    {


	if (vis_bef_curs)
	{


	    col_start = find_next_quote(line, col_start + 1, quotechar, NULL);
	    if (col_start < 0)
		goto abort_search;
	    col_end = find_next_quote(line, col_start + 1, quotechar,
							      curbuf->b_p_qe);
	    if (col_end < 0)
	    {

		col_end = col_start;
		col_start = curwin->w_cursor.col;
	    }
	}
	else
	{
	    col_end = find_prev_quote(line, col_start, quotechar, NULL);
	    if (line[col_end] != quotechar)
		goto abort_search;
	    col_start = find_prev_quote(line, col_end, quotechar,
							      curbuf->b_p_qe);
	    if (line[col_start] != quotechar)
	    {

		col_start = col_end;
		col_end = curwin->w_cursor.col;
	    }
	}
    }
    else

    if (line[col_start] == quotechar || !vis_empty)
    {
	int	first_col = col_start;

	if (!vis_empty)
	{
	    if (vis_bef_curs)
		first_col = find_next_quote(line, col_start, quotechar, NULL);
	    else
		first_col = find_prev_quote(line, col_start, quotechar, NULL);
	}


	col_start = 0;
	for (;;)
	{

	    col_start = find_next_quote(line, col_start, quotechar, NULL);
	    if (col_start < 0 || col_start > first_col)
		goto abort_search;

	    col_end = find_next_quote(line, col_start + 1, quotechar,
							      curbuf->b_p_qe);
	    if (col_end < 0)
		goto abort_search;


	    if (col_start <= first_col && first_col <= col_end)
		break;
	    col_start = col_end + 1;
	}
    }
    else
    {

	col_start = find_prev_quote(line, col_start, quotechar, curbuf->b_p_qe);
	if (line[col_start] != quotechar)
	{

	    col_start = find_next_quote(line, col_start, quotechar, NULL);
	    if (col_start < 0)
		goto abort_search;
	}


	col_end = find_next_quote(line, col_start + 1, quotechar,
							      curbuf->b_p_qe);
	if (col_end < 0)
	    goto abort_search;
    }


    if (include)
    {
	if (VIM_ISWHITE(line[col_end + 1]))
	    while (VIM_ISWHITE(line[col_end + 1]))
		++col_end;
	else
	    while (col_start > 0 && VIM_ISWHITE(line[col_start - 1]))
		--col_start;
    }


    if (!include && count < 2 && (vis_empty || !inside_quotes))
	++col_start;
    curwin->w_cursor.col = col_start;
    if (VIsual_active)
    {


	if (vis_empty
		|| (vis_bef_curs
		    && !selected_quote
		    && (inside_quotes
			|| (line[VIsual.col] != quotechar
			    && (VIsual.col == 0
				|| line[VIsual.col - 1] != quotechar)))))
	{
	    VIsual = curwin->w_cursor;
	    redraw_curbuf_later(INVERTED);
	}
    }
    else
    {
	oap->start = curwin->w_cursor;
	oap->motion_type = MCHAR;
    }


    curwin->w_cursor.col = col_end;
    if ((include || count > 1
		|| (!vis_empty && inside_quotes)
	) && inc_cursor() == 2)
	inclusive = TRUE;
    if (VIsual_active)
    {
	if (vis_empty || vis_bef_curs)
	{

	    if (*p_sel != 'e')
		dec_cursor();
	}
	else
	{


	    if (inside_quotes
		    || (!selected_quote
			&& line[VIsual.col] != quotechar
			&& (line[VIsual.col] == NUL
			    || line[VIsual.col + 1] != quotechar)))
	    {
		dec_cursor();
		VIsual = curwin->w_cursor;
	    }
	    curwin->w_cursor.col = col_start;
	}
	if (VIsual_mode == 'V')
	{
	    VIsual_mode = 'v';
	    redraw_cmdline = TRUE;
	}
    }
    else
    {

	oap->inclusive = inclusive;
    }

    return OK;

abort_search:
    if (VIsual_active && *p_sel == 'e')
    {
	if (did_exclusive_adj)
	    inc_cursor();
	if (restore_vis_bef)
	{
	    pos_T t = curwin->w_cursor;

	    curwin->w_cursor = VIsual;
	    VIsual = t;
	}
    }
    return FALSE;
}
