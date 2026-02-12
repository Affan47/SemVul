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
    int			added;
    unsigned		new_line_len;

#ifdef FEAT_RIGHTLEFT
    int			old_p_ri = p_ri;

    p_ri = 0;
#endif

    State = MODE_INSERT;
    block_prep(oap, &bd, curwin->w_cursor.lnum, TRUE);
    if (bd.is_short)
	return;


    total = (int)((unsigned)amount * (unsigned)sw_val);
    if ((total / sw_val) != amount)
	return;

    oldp = ml_get_curline();

    if (!left)
    {
	int		tabs = 0, spaces = 0;
	chartabsize_T	cts;


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


	init_chartabsize_arg(&cts, curwin, curwin->w_cursor.lnum,
				   bd.start_vcol, bd.textstart, bd.textstart);
	for ( ; VIM_ISWHITE(*cts.cts_ptr); )
	{
	    incr = lbr_chartabsize_adv(&cts);
	    total += incr;
	    cts.cts_vcol += incr;
	}
	bd.textstart = cts.cts_ptr;
	bd.start_vcol = cts.cts_vcol;
	clear_chartabsize_arg(&cts);


#ifdef FEAT_VARTABS
	if (!curbuf->b_p_et)
	    tabstop_fromto(ws_vcol, ws_vcol + total,
				ts_val, curbuf->b_p_vts_array, &tabs, &spaces);
	else
	    spaces = total;
#else
	if (!curbuf->b_p_et)
	    tabs = ((ws_vcol % ts_val) + total) / ts_val;
	if (tabs > 0)
	    spaces = ((ws_vcol % ts_val) + total) % ts_val;
	else
	    spaces = total;
#endif

	bd.textcol -= bd.pre_whitesp_c - (bd.startspaces != 0);

	new_line_len = bd.textcol + tabs + spaces + (int)STRLEN(bd.textstart);
	newp = alloc(new_line_len + 1);
	if (newp == NULL)
	    return;
	mch_memmove(newp, oldp, (size_t)bd.textcol);
	vim_memset(newp + bd.textcol, TAB, (size_t)tabs);
	vim_memset(newp + bd.textcol + tabs, ' ', (size_t)spaces);

	STRMOVE(newp + bd.textcol + tabs + spaces, bd.textstart);
    }
    else
    {
	colnr_T	    destination_col;

	char_u	    *verbatim_copy_end;

	colnr_T	    verbatim_copy_width;

	unsigned    fill;
	size_t	    block_space_width;
	size_t	    shift_amount;
	char_u	    *non_white = bd.textstart;
	colnr_T	    non_white_col;
	chartabsize_T cts;


	if (bd.startspaces)
	    MB_PTR_ADV(non_white);


	non_white_col = bd.start_vcol;

	init_chartabsize_arg(&cts, curwin, curwin->w_cursor.lnum,
				   non_white_col, bd.textstart, non_white);
	while (VIM_ISWHITE(*cts.cts_ptr))
	{
	    incr = lbr_chartabsize_adv(&cts);
	    cts.cts_vcol += incr;
	}
	non_white_col = cts.cts_vcol;
	non_white = cts.cts_ptr;
	clear_chartabsize_arg(&cts);

	block_space_width = non_white_col - oap->start_vcol;

	shift_amount = (block_space_width < (size_t)total
					 ? block_space_width : (size_t)total);


	destination_col = (colnr_T)(non_white_col - shift_amount);


	verbatim_copy_end = bd.textstart;
	verbatim_copy_width = bd.start_vcol;


	if (bd.startspaces)
	    verbatim_copy_width -= bd.start_char_vcols;
	init_chartabsize_arg(&cts, curwin, 0, verbatim_copy_width,
					     bd.textstart, verbatim_copy_end);
	while (cts.cts_vcol < destination_col)
	{
	    incr = lbr_chartabsize(&cts);
	    if (cts.cts_vcol + incr > destination_col)
		break;
	    cts.cts_vcol += incr;
	    MB_PTR_ADV(cts.cts_ptr);
	}
	verbatim_copy_width = cts.cts_vcol;
	verbatim_copy_end = cts.cts_ptr;
	clear_chartabsize_arg(&cts);


	fill = destination_col - verbatim_copy_width;


	new_line_len = (unsigned)(verbatim_copy_end - oldp)
		       + fill
		       + (unsigned)STRLEN(non_white);

	newp = alloc(new_line_len + 1);
	if (newp == NULL)
	    return;
	mch_memmove(newp, oldp, (size_t)(verbatim_copy_end - oldp));
	vim_memset(newp + (verbatim_copy_end - oldp), ' ', (size_t)fill);

	STRMOVE(newp + (verbatim_copy_end - oldp) + fill, non_white);
    }

    added = new_line_len - (int)STRLEN(oldp);
    ml_replace(curwin->w_cursor.lnum, newp, FALSE);
    inserted_bytes(curwin->w_cursor.lnum, bd.textcol, added);
    State = oldstate;
    curwin->w_cursor.col = oldcol;
#ifdef FEAT_RIGHTLEFT
    p_ri = old_p_ri;
#endif
}
