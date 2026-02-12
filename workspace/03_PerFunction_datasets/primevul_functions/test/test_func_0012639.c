get_op_vcol(
    oparg_T	*oap,
    colnr_T	redo_VIsual_vcol,
    int		initial)
{
    colnr_T	    start, end;

    if (VIsual_mode != Ctrl_V
	    || (!initial && oap->end.col < curwin->w_width))
	return;

    oap->block_mode = TRUE;


    if (has_mbyte)
	mb_adjustpos(curwin->w_buffer, &oap->end);

    getvvcol(curwin, &(oap->start), &oap->start_vcol, NULL, &oap->end_vcol);

    if (!redo_VIsual_busy)
    {
	getvvcol(curwin, &(oap->end), &start, NULL, &end);

	if (start < oap->start_vcol)
	    oap->start_vcol = start;
	if (end > oap->end_vcol)
	{
	    if (initial && *p_sel == 'e' && start >= 1
				    && start - 1 >= oap->end_vcol)
		oap->end_vcol = start - 1;
	    else
		oap->end_vcol = end;
	}
    }


    if (curwin->w_curswant == MAXCOL)
    {
	curwin->w_cursor.col = MAXCOL;
	oap->end_vcol = 0;
	for (curwin->w_cursor.lnum = oap->start.lnum;
		curwin->w_cursor.lnum <= oap->end.lnum;
					++curwin->w_cursor.lnum)
	{
	    getvvcol(curwin, &curwin->w_cursor, NULL, NULL, &end);
	    if (end > oap->end_vcol)
		oap->end_vcol = end;
	}
    }
    else if (redo_VIsual_busy)
	oap->end_vcol = oap->start_vcol + redo_VIsual_vcol - 1;


    curwin->w_cursor.lnum = oap->end.lnum;
    coladvance(oap->end_vcol);
    oap->end = curwin->w_cursor;

    curwin->w_cursor = oap->start;
    coladvance(oap->start_vcol);
    oap->start = curwin->w_cursor;
}
