showmatch(
    int		c)
{
    pos_T	*lpos, save_cursor;
    pos_T	mpos;
    colnr_T	vcol;
    long	save_so;
    long	save_siso;
#ifdef CURSOR_SHAPE
    int		save_state;
#endif
    colnr_T	save_dollar_vcol;
    char_u	*p;
    long	*so = curwin->w_p_so >= 0 ? &curwin->w_p_so : &p_so;
    long	*siso = curwin->w_p_siso >= 0 ? &curwin->w_p_siso : &p_siso;


    for (p = curbuf->b_p_mps; *p != NUL; ++p)
    {
#ifdef FEAT_RIGHTLEFT
	if (PTR2CHAR(p) == c && (curwin->w_p_rl ^ p_ri))
	    break;
#endif
	p += mb_ptr2len(p) + 1;
	if (PTR2CHAR(p) == c
#ifdef FEAT_RIGHTLEFT
		&& !(curwin->w_p_rl ^ p_ri)
#endif
	   )
	    break;
	p += mb_ptr2len(p);
	if (*p == NUL)
	    return;
    }
    if (*p == NUL)
	return;

    if ((lpos = findmatch(NULL, NUL)) == NULL)
	vim_beep(BO_MATCH);
    else if (lpos->lnum >= curwin->w_topline && lpos->lnum < curwin->w_botline)
    {
	if (!curwin->w_p_wrap)
	    getvcol(curwin, lpos, NULL, &vcol, NULL);
	if (curwin->w_p_wrap || (vcol >= curwin->w_leftcol
			       && vcol < curwin->w_leftcol + curwin->w_width))
	{
	    mpos = *lpos;
	    save_cursor = curwin->w_cursor;
	    save_so = *so;
	    save_siso = *siso;


	    if (dollar_vcol >= 0 && dollar_vcol == curwin->w_virtcol)
		dollar_vcol = -1;
	    ++curwin->w_virtcol;
	    update_screen(VALID);

	    save_dollar_vcol = dollar_vcol;
#ifdef CURSOR_SHAPE
	    save_state = State;
	    State = MODE_SHOWMATCH;
	    ui_cursor_shape();
#endif
	    curwin->w_cursor = mpos;
	    *so = 0;
	    *siso = 0;
	    showruler(FALSE);
	    setcursor();
	    cursor_on();
	    out_flush_cursor(TRUE, FALSE);


	    dollar_vcol = save_dollar_vcol;


	    if (vim_strchr(p_cpo, CPO_SHOWMATCH) != NULL)
		ui_delay(p_mat * 100L + 8, TRUE);
	    else if (!char_avail())
		ui_delay(p_mat * 100L + 9, FALSE);
	    curwin->w_cursor = save_cursor;
	    *so = save_so;
	    *siso = save_siso;
#ifdef CURSOR_SHAPE
	    State = save_state;
	    ui_cursor_shape();
#endif
	}
    }
}
