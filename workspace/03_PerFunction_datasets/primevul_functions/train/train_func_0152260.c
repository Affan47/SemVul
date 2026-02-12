end_word(
    long	count,
    int		bigword,
    int		stop,
    int		empty)
{
    int		sclass;

    curwin->w_cursor.coladd = 0;
    cls_bigword = bigword;
    while (--count >= 0)
    {
#ifdef FEAT_FOLDING


	if (hasFolding(curwin->w_cursor.lnum, NULL, &curwin->w_cursor.lnum))
	    coladvance((colnr_T)MAXCOL);
#endif
	sclass = cls();
	if (inc_cursor() == -1)
	    return FAIL;


	if (cls() == sclass && sclass != 0)
	{


	    if (skip_chars(sclass, FORWARD))
		return FAIL;
	}
	else if (!stop || sclass == 0)
	{


	    while (cls() == 0)
	    {
		if (empty && curwin->w_cursor.col == 0
					  && LINEEMPTY(curwin->w_cursor.lnum))
		    goto finished;
		if (inc_cursor() == -1)
		    return FAIL;
	    }


	    if (skip_chars(cls(), FORWARD))
		return FAIL;
	}
	dec_cursor();
finished:
	stop = FALSE;
    }
    return OK;
}
