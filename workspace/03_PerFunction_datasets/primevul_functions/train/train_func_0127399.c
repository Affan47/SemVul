find_ident_at_pos(
    win_T	*wp,
    linenr_T	lnum,
    colnr_T	startcol,
    char_u	**text,
    int		*textcol,
    int		find_type)
{
    char_u	*ptr;
    int		col = 0;
    int		i;
    int		this_class = 0;
    int		prev_class;
    int		prevcol;
    int		bn = 0;


    ptr = ml_get_buf(wp->w_buffer, lnum, FALSE);
    for (i = (find_type & FIND_IDENT) ? 0 : 1;	i < 2; ++i)
    {


	col = startcol;
	if (has_mbyte)
	{
	    while (ptr[col] != NUL)
	    {

		if ((find_type & FIND_EVAL) && ptr[col] == ']')
		    break;
		this_class = mb_get_class(ptr + col);
		if (this_class != 0 && (i == 1 || this_class != 1))
		    break;
		col += (*mb_ptr2len)(ptr + col);
	    }
	}
	else
	    while (ptr[col] != NUL
		    && (i == 0 ? !vim_iswordc(ptr[col]) : VIM_ISWHITE(ptr[col]))
		    && (!(find_type & FIND_EVAL) || ptr[col] != ']')
		    )
		++col;


	bn = ptr[col] == ']';


	if (has_mbyte)
	{

	    if ((find_type & FIND_EVAL) && ptr[col] == ']')
		this_class = mb_get_class((char_u *)"a");
	    else
		this_class = mb_get_class(ptr + col);
	    while (col > 0 && this_class != 0)
	    {
		prevcol = col - 1 - (*mb_head_off)(ptr, ptr + col - 1);
		prev_class = mb_get_class(ptr + prevcol);
		if (this_class != prev_class
			&& (i == 0
			    || prev_class == 0
			    || (find_type & FIND_IDENT))
			&& (!(find_type & FIND_EVAL)
			    || prevcol == 0
			    || !find_is_eval_item(ptr + prevcol, &prevcol,
							       &bn, BACKWARD))
			)
		    break;
		col = prevcol;
	    }


	    if (this_class > 2)
		this_class = 2;
	    if (!(find_type & FIND_STRING) || this_class == 2)
		break;
	}
	else
	{
	    while (col > 0
		    && ((i == 0
			    ? vim_iswordc(ptr[col - 1])
			    : (!VIM_ISWHITE(ptr[col - 1])
				&& (!(find_type & FIND_IDENT)
				    || !vim_iswordc(ptr[col - 1]))))
			|| ((find_type & FIND_EVAL)
			    && col > 1
			    && find_is_eval_item(ptr + col - 1, &col,
							       &bn, BACKWARD))
			))
		--col;


	    if (!(find_type & FIND_STRING) || vim_iswordc(ptr[col]))
		break;
	}
    }

    if (ptr[col] == NUL || (i == 0
		&& (has_mbyte ? this_class != 2 : !vim_iswordc(ptr[col]))))
    {

	if ((find_type & FIND_NOERROR) == 0)
	{
	    if (find_type & FIND_STRING)
		emsg(_("E348: No string under cursor"));
	    else
		emsg(_(e_noident));
	}
	return 0;
    }
    ptr += col;
    *text = ptr;
    if (textcol != NULL)
	*textcol = col;


    bn = 0;
    startcol -= col;
    col = 0;
    if (has_mbyte)
    {

	this_class = mb_get_class(ptr);
	while (ptr[col] != NUL
		&& ((i == 0 ? mb_get_class(ptr + col) == this_class
			    : mb_get_class(ptr + col) != 0)
		    || ((find_type & FIND_EVAL)
			&& col <= (int)startcol
			&& find_is_eval_item(ptr + col, &col, &bn, FORWARD))
		))
	    col += (*mb_ptr2len)(ptr + col);
    }
    else
	while ((i == 0 ? vim_iswordc(ptr[col])
		       : (ptr[col] != NUL && !VIM_ISWHITE(ptr[col])))
		    || ((find_type & FIND_EVAL)
			&& col <= (int)startcol
			&& find_is_eval_item(ptr + col, &col, &bn, FORWARD))
		)
	    ++col;

    return col;
}
