ins_tab(void)
{
    int		ind;
    int		i;
    int		temp;

    if (Insstart_blank_vcol == MAXCOL && curwin->w_cursor.lnum == Insstart.lnum)
	Insstart_blank_vcol = get_nolist_virtcol();
    if (echeck_abbr(TAB + ABBR_OFF))
	return FALSE;

    ind = inindent(0);
#ifdef FEAT_CINDENT
    if (ind)
	can_cindent = FALSE;
#endif


    if (!curbuf->b_p_et
#ifdef FEAT_VARTABS
	    && !(p_sta && ind

		&& ((tabstop_count(curbuf->b_p_vts_array) > 1)
		    || (tabstop_count(curbuf->b_p_vts_array) == 1
		        && tabstop_first(curbuf->b_p_vts_array)
						       != get_sw_value(curbuf))
	            || (tabstop_count(curbuf->b_p_vts_array) == 0
		        && curbuf->b_p_ts != get_sw_value(curbuf))))
	    && tabstop_count(curbuf->b_p_vsts_array) == 0
#else
	    && !(p_sta && ind && curbuf->b_p_ts != get_sw_value(curbuf))
#endif
	    && get_sts_value() == 0)
	return TRUE;

    if (stop_arrow() == FAIL)
	return TRUE;

    did_ai = FALSE;
#ifdef FEAT_SMARTINDENT
    did_si = FALSE;
    can_si = FALSE;
    can_si_back = FALSE;
#endif
    AppendToRedobuff((char_u *)"\t");

#ifdef FEAT_VARTABS
    if (p_sta && ind)
    {
	temp = (int)get_sw_value(curbuf);
	temp -= get_nolist_virtcol() % temp;
    }
    else if (tabstop_count(curbuf->b_p_vsts_array) > 0 || curbuf->b_p_sts != 0)

	temp = tabstop_padding(get_nolist_virtcol(), get_sts_value(),
						     curbuf->b_p_vsts_array);
    else
	temp = tabstop_padding(get_nolist_virtcol(), curbuf->b_p_ts,
						     curbuf->b_p_vts_array);
#else
    if (p_sta && ind)
	temp = (int)get_sw_value(curbuf);
    else if (curbuf->b_p_sts != 0)
	temp = (int)get_sts_value();
    else
	temp = (int)curbuf->b_p_ts;
    temp -= get_nolist_virtcol() % temp;
#endif


    ins_char(' ');
    while (--temp > 0)
    {
	if (State & VREPLACE_FLAG)
	    ins_char(' ');
	else
	{
	    ins_str((char_u *)" ");
	    if (State & REPLACE_FLAG)
		replace_push(NUL);
	}
    }


#ifdef FEAT_VARTABS
    if (!curbuf->b_p_et && (tabstop_count(curbuf->b_p_vsts_array) > 0
                            || get_sts_value() > 0
			    || (p_sta && ind)))
#else
    if (!curbuf->b_p_et && (get_sts_value() || (p_sta && ind)))
#endif
    {
	char_u		*ptr;
	char_u		*saved_line = NULL;
	pos_T		pos;
	pos_T		fpos;
	pos_T		*cursor;
	colnr_T		want_vcol, vcol;
	int		change_col = -1;
	int		save_list = curwin->w_p_list;


	if (State & VREPLACE_FLAG)
	{
	    pos = curwin->w_cursor;
	    cursor = &pos;
	    saved_line = vim_strsave(ml_get_curline());
	    if (saved_line == NULL)
		return FALSE;
	    ptr = saved_line + pos.col;
	}
	else
	{
	    ptr = ml_get_cursor();
	    cursor = &curwin->w_cursor;
	}


	if (vim_strchr(p_cpo, CPO_LISTWM) == NULL)
	    curwin->w_p_list = FALSE;


	fpos = curwin->w_cursor;
	while (fpos.col > 0 && VIM_ISWHITE(ptr[-1]))
	{
	    --fpos.col;
	    --ptr;
	}


	if ((State & REPLACE_FLAG)
		&& fpos.lnum == Insstart.lnum
		&& fpos.col < Insstart.col)
	{
	    ptr += Insstart.col - fpos.col;
	    fpos.col = Insstart.col;
	}


	getvcol(curwin, &fpos, &vcol, NULL, NULL);
	getvcol(curwin, cursor, &want_vcol, NULL, NULL);


	while (VIM_ISWHITE(*ptr))
	{
	    i = lbr_chartabsize(NULL, (char_u *)"\t", vcol);
	    if (vcol + i > want_vcol)
		break;
	    if (*ptr != TAB)
	    {
		*ptr = TAB;
		if (change_col < 0)
		{
		    change_col = fpos.col;

		    if (fpos.lnum == Insstart.lnum && fpos.col < Insstart.col)
			Insstart.col = fpos.col;
		}
	    }
	    ++fpos.col;
	    ++ptr;
	    vcol += i;
	}

	if (change_col >= 0)
	{
	    int repl_off = 0;
	    char_u *line = ptr;


	    while (vcol < want_vcol && *ptr == ' ')
	    {
		vcol += lbr_chartabsize(line, ptr, vcol);
		++ptr;
		++repl_off;
	    }
	    if (vcol > want_vcol)
	    {

		--ptr;
		--repl_off;
	    }
	    fpos.col += repl_off;


	    i = cursor->col - fpos.col;
	    if (i > 0)
	    {
#ifdef FEAT_PROP_POPUP
		if (!(State & VREPLACE_FLAG))
		{
		    char_u  *newp;
		    int	    col;

		    newp = alloc(curbuf->b_ml.ml_line_len - i);
		    if (newp == NULL)
			return FALSE;

		    col = ptr - curbuf->b_ml.ml_line_ptr;
		    if (col > 0)
			mch_memmove(newp, ptr - col, col);
		    mch_memmove(newp + col, ptr + i,
					   curbuf->b_ml.ml_line_len - col - i);

		    if (curbuf->b_ml.ml_flags & ML_LINE_DIRTY)
			vim_free(curbuf->b_ml.ml_line_ptr);
		    curbuf->b_ml.ml_line_ptr = newp;
		    curbuf->b_ml.ml_line_len -= i;
		    curbuf->b_ml.ml_flags =
			   (curbuf->b_ml.ml_flags | ML_LINE_DIRTY) & ~ML_EMPTY;
		}
		else
#endif
		    STRMOVE(ptr, ptr + i);

		if ((State & REPLACE_FLAG) && !(State & VREPLACE_FLAG))
		    for (temp = i; --temp >= 0; )
			replace_join(repl_off);
	    }
#ifdef FEAT_NETBEANS_INTG
	    if (netbeans_active())
	    {
		netbeans_removed(curbuf, fpos.lnum, cursor->col, (long)(i + 1));
		netbeans_inserted(curbuf, fpos.lnum, cursor->col,
							   (char_u *)"\t", 1);
	    }
#endif
	    cursor->col -= i;


	    if (State & VREPLACE_FLAG)
	    {

		backspace_until_column(change_col);


		ins_bytes_len(saved_line + change_col,
						    cursor->col - change_col);
	    }
	}

	if (State & VREPLACE_FLAG)
	    vim_free(saved_line);
	curwin->w_p_list = save_list;
    }

    return FALSE;
}
