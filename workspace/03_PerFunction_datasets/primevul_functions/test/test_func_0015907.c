curs_columns(
    int		may_scroll)
{
    int		diff;
    int		extra;
    int		off_left, off_right;
    int		n;
    int		p_lines;
    int		width = 0;
    int		textwidth;
    int		new_leftcol;
    colnr_T	startcol;
    colnr_T	endcol;
    colnr_T	prev_skipcol;
    long        so = get_scrolloff_value();
    long        siso = get_sidescrolloff_value();


    update_topline();


    if (!(curwin->w_valid & VALID_CROW))
	curs_rows(curwin);


#ifdef FEAT_FOLDING
    if (curwin->w_cline_folded)

	startcol = curwin->w_virtcol = endcol = curwin->w_leftcol;
    else
#endif
	getvvcol(curwin, &curwin->w_cursor,
				&startcol, &(curwin->w_virtcol), &endcol);


    if (startcol > dollar_vcol)
	dollar_vcol = -1;

    extra = curwin_col_off();
    curwin->w_wcol = curwin->w_virtcol + extra;
    endcol += extra;


    curwin->w_wrow = curwin->w_cline_row;

    textwidth = curwin->w_width - extra;
    if (textwidth <= 0)
    {


	curwin->w_wcol = curwin->w_width - 1;
	if (curwin->w_p_wrap)
	    curwin->w_wrow = curwin->w_height - 1;
	else
	    curwin->w_wrow = curwin->w_height - 1 - curwin->w_empty_rows;
    }
    else if (curwin->w_p_wrap && curwin->w_width != 0)
    {
	width = textwidth + curwin_col_off2();


	if (curwin->w_wcol >= curwin->w_width)
	{
#ifdef FEAT_LINEBREAK
	    char_u *sbr;
#endif


	    n = (curwin->w_wcol - curwin->w_width) / width + 1;
	    curwin->w_wcol -= n * width;
	    curwin->w_wrow += n;

#ifdef FEAT_LINEBREAK


	    sbr = get_showbreak_value(curwin);
	    if (*sbr && *ml_get_cursor() == NUL
				    && curwin->w_wcol == vim_strsize(sbr))
		curwin->w_wcol = 0;
#endif
	}
    }


    else if (may_scroll
#ifdef FEAT_FOLDING
	    && !curwin->w_cline_folded
#endif
	    )
    {


	off_left = (int)startcol - (int)curwin->w_leftcol - siso;
	off_right = (int)endcol - (int)(curwin->w_leftcol + curwin->w_width
								- siso) + 1;
	if (off_left < 0 || off_right > 0)
	{
	    if (off_left < 0)
		diff = -off_left;
	    else
		diff = off_right;


	    if (p_ss == 0 || diff >= textwidth / 2 || off_right >= off_left)
		new_leftcol = curwin->w_wcol - extra - textwidth / 2;
	    else
	    {
		if (diff < p_ss)
		    diff = p_ss;
		if (off_left < 0)
		    new_leftcol = curwin->w_leftcol - diff;
		else
		    new_leftcol = curwin->w_leftcol + diff;
	    }
	    if (new_leftcol < 0)
		new_leftcol = 0;
	    if (new_leftcol != (int)curwin->w_leftcol)
	    {
		curwin->w_leftcol = new_leftcol;

		redraw_later(NOT_VALID);
	    }
	}
	curwin->w_wcol -= curwin->w_leftcol;
    }
    else if (curwin->w_wcol > (int)curwin->w_leftcol)
	curwin->w_wcol -= curwin->w_leftcol;
    else
	curwin->w_wcol = 0;

#ifdef FEAT_DIFF


    if (curwin->w_cursor.lnum == curwin->w_topline)
	curwin->w_wrow += curwin->w_topfill;
    else
	curwin->w_wrow += diff_check_fill(curwin, curwin->w_cursor.lnum);
#endif

    prev_skipcol = curwin->w_skipcol;

    p_lines = 0;

    if ((curwin->w_wrow >= curwin->w_height
		|| ((prev_skipcol > 0
			|| curwin->w_wrow + so >= curwin->w_height)
		    && (p_lines =
#ifdef FEAT_DIFF
			plines_win_nofill
#else
			plines_win
#endif
			(curwin, curwin->w_cursor.lnum, FALSE))
						    - 1 >= curwin->w_height))
	    && curwin->w_height != 0
	    && curwin->w_cursor.lnum == curwin->w_topline
	    && width > 0
	    && curwin->w_width != 0)
    {


	extra = 0;
	if (curwin->w_skipcol + so * width > curwin->w_virtcol)
	    extra = 1;


	if (p_lines == 0)
	    p_lines = plines_win(curwin, curwin->w_cursor.lnum, FALSE);
	--p_lines;
	if (p_lines > curwin->w_wrow + so)
	    n = curwin->w_wrow + so;
	else
	    n = p_lines;
	if ((colnr_T)n >= curwin->w_height + curwin->w_skipcol / width - so)
	    extra += 2;

	if (extra == 3 || p_lines <= so * 2)
	{

	    n = curwin->w_virtcol / width;
	    if (n > curwin->w_height / 2)
		n -= curwin->w_height / 2;
	    else
		n = 0;

	    if (n > p_lines - curwin->w_height + 1)
		n = p_lines - curwin->w_height + 1;
	    curwin->w_skipcol = n * width;
	}
	else if (extra == 1)
	{

	    extra = (curwin->w_skipcol + so * width - curwin->w_virtcol
				     + width - 1) / width;
	    if (extra > 0)
	    {
		if ((colnr_T)(extra * width) > curwin->w_skipcol)
		    extra = curwin->w_skipcol / width;
		curwin->w_skipcol -= extra * width;
	    }
	}
	else if (extra == 2)
	{

	    endcol = (n - curwin->w_height + 1) * width;
	    while (endcol > curwin->w_virtcol)
		endcol -= width;
	    if (endcol > curwin->w_skipcol)
		curwin->w_skipcol = endcol;
	}

	curwin->w_wrow -= curwin->w_skipcol / width;
	if (curwin->w_wrow >= curwin->w_height)
	{

	    extra = curwin->w_wrow - curwin->w_height + 1;
	    curwin->w_skipcol += extra * width;
	    curwin->w_wrow -= extra;
	}

	extra = ((int)prev_skipcol - (int)curwin->w_skipcol) / width;
	if (extra > 0)
	    win_ins_lines(curwin, 0, extra, FALSE, FALSE);
	else if (extra < 0)
	    win_del_lines(curwin, 0, -extra, FALSE, FALSE, 0);
    }
    else
	curwin->w_skipcol = 0;
    if (prev_skipcol != curwin->w_skipcol)
	redraw_later(NOT_VALID);

#ifdef FEAT_SYN_HL

    if (curwin->w_p_cuc && (curwin->w_valid & VALID_VIRTCOL) == 0
	    && !pum_visible())
	redraw_later(SOME_VALID);
#endif
#if defined(FEAT_PROP_POPUP) && defined(FEAT_TERMINAL)
    if (popup_is_popup(curwin) && curbuf->b_term != NULL)
    {
	curwin->w_wrow += popup_top_extra(curwin);
	curwin->w_wcol += popup_left_extra(curwin);
	curwin->w_flags |= WFLAG_WCOL_OFF_ADDED + WFLAG_WROW_OFF_ADDED;
    }
    else
	curwin->w_flags &= ~(WFLAG_WCOL_OFF_ADDED + WFLAG_WROW_OFF_ADDED);
#endif


    curwin->w_valid_leftcol = curwin->w_leftcol;

    curwin->w_valid |= VALID_WCOL|VALID_WROW|VALID_VIRTCOL;
}
