nv_next(cmdarg_T *cap)
{
    pos_T   old = curwin->w_cursor;
    int	    wrapped = FALSE;
    int	    i = normal_search(cap, 0, NULL, SEARCH_MARK | cap->arg, &wrapped);

    if (i == 1 && !wrapped && EQUAL_POS(old, curwin->w_cursor))
    {


	cap->count1 += 1;
	(void)normal_search(cap, 0, NULL, SEARCH_MARK | cap->arg, NULL);
	cap->count1 -= 1;
    }

#ifdef FEAT_SEARCH_EXTRA

    if (i > 0 && p_hls && !no_hlsearch)
	redraw_later(SOME_VALID);
#endif
}
