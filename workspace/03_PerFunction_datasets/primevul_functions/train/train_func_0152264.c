bckend_word(
    long	count,
    int		bigword,
    int		eol)
{
    int		sclass;
    int		i;

    curwin->w_cursor.coladd = 0;
    cls_bigword = bigword;
    while (--count >= 0)
    {
	sclass = cls();
	if ((i = dec_cursor()) == -1)
	    return FAIL;
	if (eol && i == 1)
	    return OK;


	if (sclass != 0)
	{
	    while (cls() == sclass)
		if ((i = dec_cursor()) == -1 || (eol && i == 1))
		    return OK;
	}


	while (cls() == 0)
	{
	    if (curwin->w_cursor.col == 0 && LINEEMPTY(curwin->w_cursor.lnum))
		break;
	    if ((i = dec_cursor()) == -1 || (eol && i == 1))
		return OK;
	}
    }
    return OK;
}
