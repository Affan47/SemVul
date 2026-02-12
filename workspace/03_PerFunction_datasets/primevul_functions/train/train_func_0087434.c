scroll_to_fraction(win_T *wp, int prev_height)
{
    linenr_T	lnum;
    int		sline, line_size;
    int		height = wp->w_height;


    if (height > 0
        && (!wp->w_p_scb || wp == curwin)
        && (height < wp->w_buffer->b_ml.ml_line_count || wp->w_topline > 1))
    {


	lnum = wp->w_cursor.lnum;
	if (lnum < 1)
	    lnum = 1;
	wp->w_wrow = ((long)wp->w_fraction * (long)height - 1L)
							       / FRACTION_MULT;
	line_size = plines_win_col(wp, lnum, (long)(wp->w_cursor.col)) - 1;
	sline = wp->w_wrow - line_size;

	if (sline >= 0)
	{

	    int rows = plines_win(wp, lnum, FALSE);

	    if (sline > wp->w_height - rows)
	    {
		sline = wp->w_height - rows;
		wp->w_wrow -= rows - line_size;
	    }
	}

	if (sline < 0)
	{


	    wp->w_wrow = line_size;
	    if (wp->w_wrow >= wp->w_height
				       && (wp->w_width - win_col_off(wp)) > 0)
	    {
		wp->w_skipcol += wp->w_width - win_col_off(wp);
		--wp->w_wrow;
		while (wp->w_wrow >= wp->w_height)
		{
		    wp->w_skipcol += wp->w_width - win_col_off(wp)
							   + win_col_off2(wp);
		    --wp->w_wrow;
		}
	    }
	}
	else if (sline > 0)
	{
	    while (sline > 0 && lnum > 1)
	    {
#ifdef FEAT_FOLDING
		hasFoldingWin(wp, lnum, &lnum, NULL, TRUE, NULL);
		if (lnum == 1)
		{

		    line_size = 1;
		    --sline;
		    break;
		}
#endif
		--lnum;
#ifdef FEAT_DIFF
		if (lnum == wp->w_topline)
		    line_size = plines_win_nofill(wp, lnum, TRUE)
							      + wp->w_topfill;
		else
#endif
		    line_size = plines_win(wp, lnum, TRUE);
		sline -= line_size;
	    }

	    if (sline < 0)
	    {


#ifdef FEAT_FOLDING
		hasFoldingWin(wp, lnum, NULL, &lnum, TRUE, NULL);
#endif
		lnum++;
		wp->w_wrow -= line_size + sline;
	    }
	    else if (sline > 0)
	    {

		lnum = 1;
		wp->w_wrow -= sline;
	    }
	}
	set_topline(wp, lnum);
    }

    if (wp == curwin)
    {
	if (get_scrolloff_value())
	    update_topline();
	curs_columns(FALSE);
    }
    if (prev_height > 0)
	wp->w_prev_fraction_row = wp->w_wrow;

    win_comp_scroll(wp);
    redraw_win_later(wp, SOME_VALID);
    wp->w_redr_status = TRUE;
    invalidate_botline_win(wp);
}
