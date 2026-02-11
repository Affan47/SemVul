check_lnums(do_curwin)
    int		do_curwin;
{
    win_T	*wp;

#ifdef FEAT_WINDOWS
    tabpage_T	*tp;

    FOR_ALL_TAB_WINDOWS(tp, wp)
	if ((do_curwin || wp != curwin) && wp->w_buffer == curbuf)
#else
    wp = curwin;
    if (do_curwin)
#endif
	{
	    if (wp->w_cursor.lnum > curbuf->b_ml.ml_line_count)
		wp->w_cursor.lnum = curbuf->b_ml.ml_line_count;
	    if (wp->w_topline > curbuf->b_ml.ml_line_count)
		wp->w_topline = curbuf->b_ml.ml_line_count;
	}
}
