shift_block(oparg_T *oap, int amount)
{
    int			left = (oap->op_type == OP_LSHIFT);
    int			oldstate = State;
    int			total;
    char_u		*newp, *oldp;
    int			oldcol = curwin->w_cursor.col;
    int			sw_val = (int)get_sw_value_indent(curbuf);
    int			ts_val = (int)curbuf->b_p_ts;
    struct block_def	bd;
    int			incr;
    colnr_T		ws_vcol;
    int			i = 0, j = 0;
    int			len;
#ifdef FEAT_RIGHTLEFT
    int			old_p_ri = p_ri;

    p_ri = 0;
#endif

    State = INSERT;
    block_prep(oap, &bd, curwin->w_cursor.lnum, TRUE);
    if (bd.is_short)
	return;


    total = (int)((unsigned)amount * (unsigned)sw_val);
    if ((total / sw_val) != amount)
	return;

    oldp = ml_get_curline();

    if (!left)
    {


	total += bd.pre_whitesp;
	ws_vcol = bd.start_vcol - bd.pre_whitesp;
	if (bd.startspaces)
	{
	    if (has_mbyte)
	    {
		if ((*mb_ptr2len)(bd.textstart) == 1)
		    ++bd.textstart;
		else
		{
		    ws_vcol = 0;
		    bd.startspaces = 0;
		}
	    }
	    else
		++bd.textstart;
	}
	for ( ; VIM_ISWHITE(*bd.textstart); )
	{

	    incr = lbr_chartabsize_adv(bd.textstart, &bd.textstart,
						    (colnr_T)(bd.start_vcol));
	    total += incr;
	    bd.start_vcol += incr;
	}


#ifdef FEAT_VARTABS
	if (!curbuf->b_p_et)
	    tabstop_fromto(ws_vcol, ws_vcol + total,
					ts_val, curbuf->b_p_vts_array, &i, &j);
	else
	    j = total;
#else
	if (!curbuf->b_p_et)
	    i = ((ws_vcol % ts_val) + total) / ts_val;
	if (i)
	    j = ((ws_vcol % ts_val) + total) % ts_val;
	else
	    j = total;
#endif

	bd.textcol -= bd.pre_whitesp_c - (bd.startspaces != 0);
	len = (int)STRLEN(bd.textstart) + 1;
	newp = alloc(bd.textcol + i + j + len);
	if (newp == NULL)
	    return;
	vim_memset(newp, NUL, (size_t)(bd.textcol + i + j + len));
	mch_memmove(newp, oldp, (size_t)bd.textcol);
	vim_memset(newp + bd.textcol, TAB, (size_t)i);
	vim_memset(newp + bd.textcol + i, ' ', (size_t)j);

	mch_memmove(newp + bd.textcol + i + j, bd.textstart, (size_t)len);
    }
    else
    {
	colnr_T	    destination_col;

	char_u	    *verbatim_copy_end;

	colnr_T	    verbatim_copy_width;

	unsigned    fill;
	unsigned    new_line_len;

	size_t	    block_space_width;
	size_t	    shift_amount;
	char_u	    *non_white = bd.textstart;
	colnr_T	    non_white_col;


	if (bd.startspaces)
	    MB_PTR_ADV(non_white);


	non_white_col = bd.start_vcol;

	while (VIM_ISWHITE(*non_white))
	{
	    incr = lbr_chartabsize_adv(bd.textstart, &non_white, non_white_col);
	    non_white_col += incr;
	}

	block_space_width = non_white_col - oap->start_vcol;

	shift_amount = (block_space_width < (size_t)total
					 ? block_space_width : (size_t)total);


	destination_col = (colnr_T)(non_white_col - shift_amount);


	verbatim_copy_end = bd.textstart;
	verbatim_copy_width = bd.start_vcol;


	if (bd.startspaces)
	    verbatim_copy_width -= bd.start_char_vcols;
	while (verbatim_copy_width < destination_col)
	{
	    char_u *line = verbatim_copy_end;


	    incr = lbr_chartabsize(line, verbatim_copy_end,
							 verbatim_copy_width);
	    if (verbatim_copy_width + incr > destination_col)
		break;
	    verbatim_copy_width += incr;
	    MB_PTR_ADV(verbatim_copy_end);
	}


	fill = destination_col - verbatim_copy_width;


	new_line_len = (unsigned)(verbatim_copy_end - oldp)
		       + fill
		       + (unsigned)STRLEN(non_white) + 1;

	newp = alloc(new_line_len);
	if (newp == NULL)
	    return;
	mch_memmove(newp, oldp, (size_t)(verbatim_copy_end - oldp));
	vim_memset(newp + (verbatim_copy_end - oldp), ' ', (size_t)fill);
	STRMOVE(newp + (verbatim_copy_end - oldp) + fill, non_white);
    }

    ml_replace(curwin->w_cursor.lnum, newp, FALSE);
    changed_bytes(curwin->w_cursor.lnum, (colnr_T)bd.textcol);
    State = oldstate;
    curwin->w_cursor.col = oldcol;
#ifdef FEAT_RIGHTLEFT
    p_ri = old_p_ri;
#endif
}
