ins_try_si(int c)
{
    pos_T	*pos, old_pos;
    char_u	*ptr;
    int		i;
    int		temp;

    if (((did_si || can_si_back) && c == '{')
	    || (can_si && c == '}' && inindent(0)))
    {

	if (c == '}' && (pos = findmatch(NULL, '{')) != NULL)
	{
	    old_pos = curwin->w_cursor;

	    ptr = ml_get(pos->lnum);
	    i = pos->col;
	    if (i > 0)
		while (--i > 0 && VIM_ISWHITE(ptr[i]))
		    ;
	    curwin->w_cursor.lnum = pos->lnum;
	    curwin->w_cursor.col = i;
	    if (ptr[i] == ')' && (pos = findmatch(NULL, '(')) != NULL)
		curwin->w_cursor = *pos;
	    i = get_indent();
	    curwin->w_cursor = old_pos;
	    if (State & VREPLACE_FLAG)
		change_indent(INDENT_SET, i, FALSE, NUL, TRUE);
	    else
		(void)set_indent(i, SIN_CHANGED);
	}
	else if (curwin->w_cursor.col > 0)
	{

	    temp = TRUE;
	    if (c == '{' && can_si_back && curwin->w_cursor.lnum > 1)
	    {
		old_pos = curwin->w_cursor;
		i = get_indent();
		while (curwin->w_cursor.lnum > 1)
		{
		    ptr = skipwhite(ml_get(--(curwin->w_cursor.lnum)));

		    if (*ptr != '#' && *ptr != NUL)
			break;
		}
		if (get_indent() >= i)
		    temp = FALSE;
		curwin->w_cursor = old_pos;
	    }
	    if (temp)
		shift_line(TRUE, FALSE, 1, TRUE);
	}
    }

    if (curwin->w_cursor.col > 0 && can_si && c == '#' && inindent(0))
    {

	old_indent = get_indent();
	(void)set_indent(0, SIN_CHANGED);
    }

    if (ai_col > curwin->w_cursor.col)
	ai_col = curwin->w_cursor.col;
}
}
