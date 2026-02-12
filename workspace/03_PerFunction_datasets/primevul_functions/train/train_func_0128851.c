cursor_up(
    long	n,
    int		upd_topline)
{
    linenr_T	lnum;

    if (n > 0)
    {
	lnum = curwin->w_cursor.lnum;


	if (lnum <= 1 || (n >= lnum && vim_strchr(p_cpo, CPO_MINUS) != NULL))
	    return FAIL;
	if (n >= lnum)
	    lnum = 1;
	else
#ifdef FEAT_FOLDING
	    if (hasAnyFolding(curwin))
	{


	    (void)hasFolding(lnum, &lnum, NULL);

	    while (n--)
	    {

		--lnum;
		if (lnum <= 1)
		    break;


		if (n > 0 || !((State & INSERT) || (fdo_flags & FDO_ALL)))
		    (void)hasFolding(lnum, &lnum, NULL);
	    }
	    if (lnum < 1)
		lnum = 1;
	}
	else
#endif
	    lnum -= n;
	curwin->w_cursor.lnum = lnum;
    }


    coladvance(curwin->w_curswant);

    if (upd_topline)
	update_topline();

    return OK;
}
