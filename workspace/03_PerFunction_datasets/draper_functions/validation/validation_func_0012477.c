setManualFold(lnum, opening, recurse, donep)
    linenr_T	lnum;
    int		opening;
    int		recurse;
    int		*donep;
{
#ifdef FEAT_DIFF
    if (foldmethodIsDiff(curwin) && curwin->w_p_scb)
    {
	win_T	    *wp;
	linenr_T    dlnum;


	FOR_ALL_WINDOWS(wp)
	{
	    if (wp != curwin && foldmethodIsDiff(wp) && wp->w_p_scb)
	    {
		dlnum = diff_lnum_win(curwin->w_cursor.lnum, wp);
		if (dlnum != 0)
		    (void)setManualFoldWin(wp, dlnum, opening, recurse, NULL);
	    }
	}
    }
#endif

    return setManualFoldWin(curwin, lnum, opening, recurse, donep);
}
