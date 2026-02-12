fold_line(
    win_T	*wp,
    long	fold_count,
    foldinfo_T	*foldinfo,
    linenr_T	lnum,
    int		row)
{


    char_u	buf[MAX_MCO * 12 + 1];
    pos_T	*top, *bot;
    linenr_T	lnume = lnum + fold_count - 1;
    int		len;
    char_u	*text;
    int		fdc;
    int		col;
    int		txtcol;
    int		off = (int)(current_ScreenLine - ScreenLines);
    int		ri;


    col = 0;


#ifdef FEAT_CMDWIN
    if (cmdwin_type != 0 && wp == curwin)
    {
	ScreenLines[off] = cmdwin_type;
	ScreenAttrs[off] = HL_ATTR(HLF_AT);
	if (enc_utf8)
	    ScreenLinesUC[off] = 0;
	++col;
    }
#endif

#ifdef FEAT_RIGHTLEFT
# define RL_MEMSET(p, v, l) \
    do { \
	if (wp->w_p_rl) \
	    for (ri = 0; ri < l; ++ri) \
	       ScreenAttrs[off + (wp->w_width - (p) - (l)) + ri] = v; \
	 else \
	    for (ri = 0; ri < l; ++ri) \
	       ScreenAttrs[off + (p) + ri] = v; \
    } while (0)
#else
# define RL_MEMSET(p, v, l) \
    do { \
	for (ri = 0; ri < l; ++ri) \
	    ScreenAttrs[off + (p) + ri] = v; \
    } while (0)
#endif


    fdc = compute_foldcolumn(wp, col);
    if (fdc > 0)
    {
	char_u	*p;
	int	i;
	int	idx;

	fill_foldcolumn(buf, wp, TRUE, lnum);
	p = buf;
	for (i = 0; i < fdc; i++)
	{
	    int		ch;

	    if (has_mbyte)
		ch = mb_ptr2char_adv(&p);
	    else
		ch = *p++;
#ifdef FEAT_RIGHTLEFT
	    if (wp->w_p_rl)
		idx = off + wp->w_width - i - 1 - col;
	    else
#endif
		idx = off + col + i;
	    if (enc_utf8)
	    {
		if (ch >= 0x80)
		{
		    ScreenLinesUC[idx] = ch;
		    ScreenLinesC[0][idx] = 0;
		    ScreenLines[idx] = 0x80;
		}
		else
		{
		    ScreenLines[idx] = ch;
		    ScreenLinesUC[idx] = 0;
		}
	    }
	    else
		ScreenLines[idx] = ch;
	}

	RL_MEMSET(col, HL_ATTR(HLF_FC), fdc);
	col += fdc;
    }


    RL_MEMSET(col, HL_ATTR(HLF_FL), wp->w_width - col);

#ifdef FEAT_SIGNS

    if (signcolumn_on(wp))
    {
	len = wp->w_width - col;
	if (len > 0)
	{
	    if (len > 2)
		len = 2;
# ifdef FEAT_RIGHTLEFT
	    if (wp->w_p_rl)

		copy_text_attr(off + wp->w_width - len - col,
					(char_u *)"  ", len, HL_ATTR(HLF_FL));
	    else
# endif
		copy_text_attr(off + col, (char_u *)"  ", len, HL_ATTR(HLF_FL));
	    col += len;
	}
    }
#endif


    if (wp->w_p_nu || wp->w_p_rnu)
    {
	len = wp->w_width - col;
	if (len > 0)
	{
	    int	    w = number_width(wp);
	    long    num;
	    char    *fmt = "%*ld ";

	    if (len > w + 1)
		len = w + 1;

	    if (wp->w_p_nu && !wp->w_p_rnu)

		num = (long)lnum;
	    else
	    {

		num = labs((long)get_cursor_rel_lnum(wp, lnum));
		if (num == 0 && wp->w_p_nu && wp->w_p_rnu)
		{


		    num = lnum;
		    fmt = "%-*ld ";
		}
	    }

	    sprintf((char *)buf, fmt, w, num);
#ifdef FEAT_RIGHTLEFT
	    if (wp->w_p_rl)

		copy_text_attr(off + wp->w_width - len - col, buf, len,
							     HL_ATTR(HLF_FL));
	    else
#endif
		copy_text_attr(off + col, buf, len, HL_ATTR(HLF_FL));
	    col += len;
	}
    }


    text = get_foldtext(wp, lnum, lnume, foldinfo, buf);

    txtcol = col;


    col = text_to_screenline(wp, text, col);


#ifdef FEAT_RIGHTLEFT
    if (wp->w_p_rl)
	col -= txtcol;
#endif
    while (col < wp->w_width
#ifdef FEAT_RIGHTLEFT
		    - (wp->w_p_rl ? txtcol : 0)
#endif
	    )
    {
	if (enc_utf8)
	{
	    if (fill_fold >= 0x80)
	    {
		ScreenLinesUC[off + col] = fill_fold;
		ScreenLinesC[0][off + col] = 0;
		ScreenLines[off + col] = 0x80;
	    }
	    else
	    {
		ScreenLinesUC[off + col] = 0;
		ScreenLines[off + col] = fill_fold;
	    }
	    col++;
	}
	else
	    ScreenLines[off + col++] = fill_fold;
    }

    if (text != buf)
	vim_free(text);


    if (VIsual_active && wp->w_buffer == curwin->w_buffer)
    {
	if (LTOREQ_POS(curwin->w_cursor, VIsual))
	{

	    top = &curwin->w_cursor;
	    bot = &VIsual;
	}
	else
	{

	    top = &VIsual;
	    bot = &curwin->w_cursor;
	}
	if (lnum >= top->lnum
		&& lnume <= bot->lnum
		&& (VIsual_mode != 'v'
		    || ((lnum > top->lnum
			    || (lnum == top->lnum
				&& top->col == 0))
			&& (lnume < bot->lnum
			    || (lnume == bot->lnum
				&& (bot->col - (*p_sel == 'e'))
		>= (colnr_T)STRLEN(ml_get_buf(wp->w_buffer, lnume, FALSE)))))))
	{
	    if (VIsual_mode == Ctrl_V)
	    {

		if (wp->w_old_cursor_fcol + txtcol < (colnr_T)wp->w_width)
		{
		    if (wp->w_old_cursor_lcol != MAXCOL
			     && wp->w_old_cursor_lcol + txtcol
						       < (colnr_T)wp->w_width)
			len = wp->w_old_cursor_lcol;
		    else
			len = wp->w_width - txtcol;
		    RL_MEMSET(wp->w_old_cursor_fcol + txtcol, HL_ATTR(HLF_V),
					    len - (int)wp->w_old_cursor_fcol);
		}
	    }
	    else
	    {

		RL_MEMSET(txtcol, HL_ATTR(HLF_V), wp->w_width - txtcol);
	    }
	}
    }

#ifdef FEAT_SYN_HL

    if (wp->w_p_cc_cols)
    {
	int i = 0;
	int j = wp->w_p_cc_cols[i];
	int old_txtcol = txtcol;

	while (j > -1)
	{
	    txtcol += j;
	    if (wp->w_p_wrap)
		txtcol -= wp->w_skipcol;
	    else
		txtcol -= wp->w_leftcol;
	    if (txtcol >= 0 && txtcol < wp->w_width)
		ScreenAttrs[off + txtcol] = hl_combine_attr(
				    ScreenAttrs[off + txtcol], HL_ATTR(HLF_MC));
	    txtcol = old_txtcol;
	    j = wp->w_p_cc_cols[++i];
	}
    }


    if (wp->w_p_cuc)
    {
	txtcol += wp->w_virtcol;
	if (wp->w_p_wrap)
	    txtcol -= wp->w_skipcol;
	else
	    txtcol -= wp->w_leftcol;
	if (txtcol >= 0 && txtcol < wp->w_width)
	    ScreenAttrs[off + txtcol] = hl_combine_attr(
				 ScreenAttrs[off + txtcol], HL_ATTR(HLF_CUC));
    }
#endif

    screen_line(row + W_WINROW(wp), wp->w_wincol, (int)wp->w_width,
						     (int)wp->w_width, 0);


    if (wp == curwin
	    && lnum <= curwin->w_cursor.lnum
	    && lnume >= curwin->w_cursor.lnum)
    {
	curwin->w_cline_row = row;
	curwin->w_cline_height = 1;
	curwin->w_cline_folded = TRUE;
	curwin->w_valid |= (VALID_CHEIGHT|VALID_CROW);
    }

# ifdef FEAT_CONCEAL

    if (wp == curwin
	    && wp->w_cursor.lnum >= lnum
	    && wp->w_cursor.lnum <= lnume
	    && conceal_cursor_line(wp))
	curs_columns(TRUE);
# endif
}
