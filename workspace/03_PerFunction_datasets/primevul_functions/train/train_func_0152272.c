bck_word(long count, int bigword, int stop)
{
    int		sclass;

    curwin->w_cursor.coladd = 0;
    cls_bigword = bigword;
    while (--count >= 0)
    {
#ifdef FEAT_FOLDING


	if (hasFolding(curwin->w_cursor.lnum, &curwin->w_cursor.lnum, NULL))
	    curwin->w_cursor.col = 0;
#endif
	sclass = cls();
	if (dec_cursor() == -1)
	    return FAIL;

	if (!stop || sclass == cls() || sclass == 0)
	{


	    while (cls() == 0)
	    {
		if (curwin->w_cursor.col == 0
				      && LINEEMPTY(curwin->w_cursor.lnum))
		    goto finished;
		if (dec_cursor() == -1)
		    return OK;
	    }


	    if (skip_chars(cls(), BACKWARD))
		return OK;
	}

	inc_cursor();
finished:
	stop = FALSE;
    }
    return OK;
}
