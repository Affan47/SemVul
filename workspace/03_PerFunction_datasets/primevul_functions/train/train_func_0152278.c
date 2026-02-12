fwd_word(
    long	count,
    int		bigword,
    int		eol)
{
    int		sclass;
    int		i;
    int		last_line;

    curwin->w_cursor.coladd = 0;
    cls_bigword = bigword;
    while (--count >= 0)
    {
#ifdef FEAT_FOLDING


	if (hasFolding(curwin->w_cursor.lnum, NULL, &curwin->w_cursor.lnum))
	    coladvance((colnr_T)MAXCOL);
#endif
	sclass = cls();


	last_line = (curwin->w_cursor.lnum == curbuf->b_ml.ml_line_count);
	i = inc_cursor();
	if (i == -1 || (i >= 1 && last_line))
	    return FAIL;
	if (i >= 1 && eol && count == 0)
	    return OK;


	if (sclass != 0)
	    while (cls() == sclass)
	    {
		i = inc_cursor();
		if (i == -1 || (i >= 1 && eol && count == 0))
		    return OK;
	    }


	while (cls() == 0)
	{


	    if (curwin->w_cursor.col == 0 && *ml_get_curline() == NUL)
		break;

	    i = inc_cursor();
	    if (i == -1 || (i >= 1 && eol && count == 0))
		return OK;
	}
    }
    return OK;
}
