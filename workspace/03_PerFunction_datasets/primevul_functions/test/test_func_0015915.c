scroll_cursor_bot(int min_scroll, int set_topbot)
{
    int		used;
    int		scrolled = 0;
    int		extra = 0;
    int		i;
    linenr_T	line_count;
    linenr_T	old_topline = curwin->w_topline;
    lineoff_T	loff;
    lineoff_T	boff;
#ifdef FEAT_DIFF
    int		old_topfill = curwin->w_topfill;
    int		fill_below_window;
#endif
    linenr_T	old_botline = curwin->w_botline;
    linenr_T	old_valid = curwin->w_valid;
    int		old_empty_rows = curwin->w_empty_rows;
    linenr_T	cln;
    long        so = get_scrolloff_value();

    cln = curwin->w_cursor.lnum;
    if (set_topbot)
    {
	used = 0;
	curwin->w_botline = cln + 1;
#ifdef FEAT_DIFF
	loff.fill = 0;
#endif
	for (curwin->w_topline = curwin->w_botline;
		curwin->w_topline > 1;
		curwin->w_topline = loff.lnum)
	{
	    loff.lnum = curwin->w_topline;
	    topline_back(&loff);
	    if (loff.height == MAXCOL || used + loff.height > curwin->w_height)
		break;
	    used += loff.height;
#ifdef FEAT_DIFF
	    curwin->w_topfill = loff.fill;
#endif
	}
	set_empty_rows(curwin, used);
	curwin->w_valid |= VALID_BOTLINE|VALID_BOTLINE_AP;
	if (curwin->w_topline != old_topline
#ifdef FEAT_DIFF
		|| curwin->w_topfill != old_topfill
#endif
		)
	    curwin->w_valid &= ~(VALID_WROW|VALID_CROW);
    }
    else
	validate_botline();


#ifdef FEAT_DIFF
    used = plines_nofill(cln);
#else
    validate_cheight();
    used = curwin->w_cline_height;
#endif


    if (cln >= curwin->w_botline)
    {
	scrolled = used;
	if (cln == curwin->w_botline)
	    scrolled -= curwin->w_empty_rows;
    }


#ifdef FEAT_FOLDING
    if (!hasFolding(curwin->w_cursor.lnum, &loff.lnum, &boff.lnum))
#endif
    {
	loff.lnum = cln;
	boff.lnum = cln;
    }
#ifdef FEAT_DIFF
    loff.fill = 0;
    boff.fill = 0;
    fill_below_window = diff_check_fill(curwin, curwin->w_botline)
						      - curwin->w_filler_rows;
#endif

    while (loff.lnum > 1)
    {


	if ((((scrolled <= 0 || scrolled >= min_scroll)
		    && extra >= (mouse_dragging > 0 ? mouse_dragging - 1 : so))
		    || boff.lnum + 1 > curbuf->b_ml.ml_line_count)
		&& loff.lnum <= curwin->w_botline
#ifdef FEAT_DIFF
		&& (loff.lnum < curwin->w_botline
		    || loff.fill >= fill_below_window)
#endif
		)
	    break;


	topline_back(&loff);
	if (loff.height == MAXCOL)
	    used = MAXCOL;
	else
	    used += loff.height;
	if (used > curwin->w_height)
	    break;
	if (loff.lnum >= curwin->w_botline
#ifdef FEAT_DIFF
		&& (loff.lnum > curwin->w_botline
		    || loff.fill <= fill_below_window)
#endif
		)
	{

	    scrolled += loff.height;
	    if (loff.lnum == curwin->w_botline
#ifdef FEAT_DIFF
			    && loff.fill == 0
#endif
		    )
		scrolled -= curwin->w_empty_rows;
	}

	if (boff.lnum < curbuf->b_ml.ml_line_count)
	{

	    botline_forw(&boff);
	    used += boff.height;
	    if (used > curwin->w_height)
		break;
	    if (extra < ( mouse_dragging > 0 ? mouse_dragging - 1 : so)
		    || scrolled < min_scroll)
	    {
		extra += boff.height;
		if (boff.lnum >= curwin->w_botline
#ifdef FEAT_DIFF
			|| (boff.lnum + 1 == curwin->w_botline
			    && boff.fill > curwin->w_filler_rows)
#endif
		   )
		{

		    scrolled += boff.height;
		    if (boff.lnum == curwin->w_botline
#ifdef FEAT_DIFF
			    && boff.fill == 0
#endif
			    )
			scrolled -= curwin->w_empty_rows;
		}
	    }
	}
    }


    if (scrolled <= 0)
	line_count = 0;

    else if (used > curwin->w_height)
	line_count = used;

    else
    {
	line_count = 0;
#ifdef FEAT_DIFF
	boff.fill = curwin->w_topfill;
#endif
	boff.lnum = curwin->w_topline - 1;
	for (i = 0; i < scrolled && boff.lnum < curwin->w_botline; )
	{
	    botline_forw(&boff);
	    i += boff.height;
	    ++line_count;
	}
	if (i < scrolled)
	    line_count = 9999;
    }


    if (line_count >= curwin->w_height && line_count > min_scroll)
	scroll_cursor_halfway(FALSE);
    else
	scrollup(line_count, TRUE);


    if (curwin->w_topline == old_topline && set_topbot)
    {
	curwin->w_botline = old_botline;
	curwin->w_empty_rows = old_empty_rows;
	curwin->w_valid = old_valid;
    }
    curwin->w_valid |= VALID_TOPLINE;
}
