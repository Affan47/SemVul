current_par(
    oparg_T	*oap,
    long	count,
    int		include,
    int		type)
{
    linenr_T	start_lnum;
    linenr_T	end_lnum;
    int		white_in_front;
    int		dir;
    int		start_is_white;
    int		prev_start_is_white;
    int		retval = OK;
    int		do_white = FALSE;
    int		t;
    int		i;

    if (type == 'S')
	return FAIL;

    start_lnum = curwin->w_cursor.lnum;


    if (VIsual_active && start_lnum != VIsual.lnum)
    {
extend:
	if (start_lnum < VIsual.lnum)
	    dir = BACKWARD;
	else
	    dir = FORWARD;
	for (i = count; --i >= 0; )
	{
	    if (start_lnum ==
			   (dir == BACKWARD ? 1 : curbuf->b_ml.ml_line_count))
	    {
		retval = FAIL;
		break;
	    }

	    prev_start_is_white = -1;
	    for (t = 0; t < 2; ++t)
	    {
		start_lnum += dir;
		start_is_white = linewhite(start_lnum);
		if (prev_start_is_white == start_is_white)
		{
		    start_lnum -= dir;
		    break;
		}
		for (;;)
		{
		    if (start_lnum == (dir == BACKWARD
					    ? 1 : curbuf->b_ml.ml_line_count))
			break;
		    if (start_is_white != linewhite(start_lnum + dir)
			    || (!start_is_white
				    && startPS(start_lnum + (dir > 0
							     ? 1 : 0), 0, 0)))
			break;
		    start_lnum += dir;
		}
		if (!include)
		    break;
		if (start_lnum == (dir == BACKWARD
					    ? 1 : curbuf->b_ml.ml_line_count))
		    break;
		prev_start_is_white = start_is_white;
	    }
	}
	curwin->w_cursor.lnum = start_lnum;
	curwin->w_cursor.col = 0;
	return retval;
    }


    white_in_front = linewhite(start_lnum);
    while (start_lnum > 1)
    {
	if (white_in_front)
	{
	    if (!linewhite(start_lnum - 1))
		break;
	}
	else
	{
	    if (linewhite(start_lnum - 1) || startPS(start_lnum, 0, 0))
		break;
	}
	--start_lnum;
    }


    end_lnum = start_lnum;
    while (end_lnum <= curbuf->b_ml.ml_line_count && linewhite(end_lnum))
	++end_lnum;

    --end_lnum;
    i = count;
    if (!include && white_in_front)
	--i;
    while (i--)
    {
	if (end_lnum == curbuf->b_ml.ml_line_count)
	    return FAIL;

	if (!include)
	    do_white = linewhite(end_lnum + 1);

	if (include || !do_white)
	{
	    ++end_lnum;


	    while (end_lnum < curbuf->b_ml.ml_line_count
		    && !linewhite(end_lnum + 1)
		    && !startPS(end_lnum + 1, 0, 0))
		++end_lnum;
	}

	if (i == 0 && white_in_front && include)
	    break;


	if (include || do_white)
	    while (end_lnum < curbuf->b_ml.ml_line_count
						   && linewhite(end_lnum + 1))
		++end_lnum;
    }


    if (!white_in_front && !linewhite(end_lnum) && include)
	while (start_lnum > 1 && linewhite(start_lnum - 1))
	    --start_lnum;

    if (VIsual_active)
    {


	if (VIsual_mode == 'V' && start_lnum == curwin->w_cursor.lnum)
	    goto extend;
	if (VIsual.lnum != start_lnum)
	{
	    VIsual.lnum = start_lnum;
	    VIsual.col = 0;
	}
	VIsual_mode = 'V';
	redraw_curbuf_later(INVERTED);
	showmode();
    }
    else
    {
	oap->start.lnum = start_lnum;
	oap->start.col = 0;
	oap->motion_type = MLINE;
    }
    curwin->w_cursor.lnum = end_lnum;
    curwin->w_cursor.col = 0;

    return OK;
}
