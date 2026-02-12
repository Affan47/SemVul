get_c_indent(void)
{
    pos_T	cur_curpos;
    int		amount;
    int		scope_amount;
    int		cur_amount = MAXCOL;
    colnr_T	col;
    char_u	*theline;
    char_u	*linecopy;
    pos_T	*trypos;
    pos_T	*comment_pos;
    pos_T	*tryposBrace = NULL;
    pos_T	tryposCopy;
    pos_T	our_paren_pos;
    char_u	*start;
    int		start_brace;
#define BRACE_IN_COL0		1
#define BRACE_AT_START		2
#define BRACE_AT_END		3
    linenr_T	ourscope;
    char_u	*l;
    char_u	*look;
    char_u	terminated;
    int		lookfor;
    int		whilelevel;
    linenr_T	lnum;
    int		n;
    int		iscase;
    int		lookfor_break;
    int		lookfor_cpp_namespace = FALSE;
    int		cont_amount = 0;
    int		original_line_islabel;
    int		added_to_amount = 0;
    int		js_cur_has_key = 0;
    linenr_T	raw_string_start = 0;
    cpp_baseclass_cache_T cache_cpp_baseclass = { FALSE, { MAXLNUM, 0 } };

    int		ind_continuation = curbuf->b_ind_continuation;

    cur_curpos = curwin->w_cursor;

    if (cur_curpos.lnum == 1)
	return 0;

    linecopy = vim_strsave(ml_get(cur_curpos.lnum));
    if (linecopy == NULL)
	return 0;

    if ((State & MODE_INSERT)
	    && curwin->w_cursor.col < (colnr_T)STRLEN(linecopy)
	    && linecopy[curwin->w_cursor.col] == ')')
	linecopy[curwin->w_cursor.col] = NUL;

    theline = skipwhite(linecopy);

    curwin->w_cursor.col = 0;

    original_line_islabel = cin_islabel();

    comment_pos = ind_find_start_comment();
    if (comment_pos != NULL)
    {

	tryposCopy = *comment_pos;
	comment_pos = &tryposCopy;
    }
    trypos = find_start_rawstring(curbuf->b_ind_maxcomment);
    if (trypos != NULL && (comment_pos == NULL
					     || LT_POS(*trypos, *comment_pos)))
    {
	amount = -1;
	goto laterend;
    }

    if (*theline == '#' && (*linecopy == '#' || in_cinkeys('#', ' ', TRUE)))
    {
	char_u *directive = skipwhite(theline + 1);
	if (curbuf->b_ind_pragma == 0 || STRNCMP(directive, "pragma", 6) != 0)
	{
	    amount = curbuf->b_ind_hash_comment;
	    goto theend;
	}
    }

    if (original_line_islabel && !curbuf->b_ind_js
					      && curbuf->b_ind_jump_label < 0)
    {
	amount = 0;
	goto theend;
    }

    if (cin_islinecomment(theline))
    {
	pos_T	linecomment_pos;

	trypos = find_line_comment();
	if (trypos == NULL && curwin->w_cursor.lnum > 1)
	{

	    linecomment_pos.col =
			  check_linecomment(ml_get(curwin->w_cursor.lnum - 1));
	    if (linecomment_pos.col != MAXCOL)
	    {
		trypos = &linecomment_pos;
		trypos->lnum = curwin->w_cursor.lnum - 1;
	    }
	}
	if (trypos  != NULL)
	{

	    getvcol(curwin, trypos, &col, NULL, NULL);
	    amount = col;
	    goto theend;
	}
    }

    if (!cin_iscomment(theline) && comment_pos != NULL)
    {
	int	lead_start_len = 2;
	int	lead_middle_len = 1;
	char_u	lead_start[COM_MAX_LEN];
	char_u	lead_middle[COM_MAX_LEN];
	char_u	lead_end[COM_MAX_LEN];
	char_u	*p;
	int	start_align = 0;
	int	start_off = 0;
	int	done = FALSE;

	getvcol(curwin, comment_pos, &col, NULL, NULL);
	amount = col;
	*lead_start = NUL;
	*lead_middle = NUL;

	p = curbuf->b_p_com;
	while (*p != NUL)
	{
	    int	align = 0;
	    int	off = 0;
	    int what = 0;

	    while (*p != NUL && *p != ':')
	    {
		if (*p == COM_START || *p == COM_END || *p == COM_MIDDLE)
		    what = *p++;
		else if (*p == COM_LEFT || *p == COM_RIGHT)
		    align = *p++;
		else if (VIM_ISDIGIT(*p) || *p == '-')
		    off = getdigits(&p);
		else
		    ++p;
	    }

	    if (*p == ':')
		++p;
	    (void)copy_option_part(&p, lead_end, COM_MAX_LEN, ",");
	    if (what == COM_START)
	    {
		STRCPY(lead_start, lead_end);
		lead_start_len = (int)STRLEN(lead_start);
		start_off = off;
		start_align = align;
	    }
	    else if (what == COM_MIDDLE)
	    {
		STRCPY(lead_middle, lead_end);
		lead_middle_len = (int)STRLEN(lead_middle);
	    }
	    else if (what == COM_END)
	    {

		if (STRNCMP(theline, lead_middle, lead_middle_len) == 0
			&& STRNCMP(theline, lead_end, STRLEN(lead_end)) != 0)
		{
		    done = TRUE;
		    if (curwin->w_cursor.lnum > 1)
		    {

			look = skipwhite(ml_get(curwin->w_cursor.lnum - 1));
			if (STRNCMP(look, lead_start, lead_start_len) == 0)
			    amount = get_indent_lnum(curwin->w_cursor.lnum - 1);
			else if (STRNCMP(look, lead_middle,
							lead_middle_len) == 0)
			{
			    amount = get_indent_lnum(curwin->w_cursor.lnum - 1);
			    break;
			}

			else if (STRNCMP(ml_get(comment_pos->lnum) + comment_pos->col,
					     lead_start, lead_start_len) != 0)
			    continue;
		    }
		    if (start_off != 0)
			amount += start_off;
		    else if (start_align == COM_RIGHT)
			amount += vim_strsize(lead_start)
						   - vim_strsize(lead_middle);
		    break;
		}

		if (STRNCMP(theline, lead_middle, lead_middle_len) != 0
			&& STRNCMP(theline, lead_end, STRLEN(lead_end)) == 0)
		{
		    amount = get_indent_lnum(curwin->w_cursor.lnum - 1);

		    if (off != 0)
			amount += off;
		    else if (align == COM_RIGHT)
			amount += vim_strsize(lead_start)
						   - vim_strsize(lead_middle);
		    done = TRUE;
		    break;
		}
	    }
	}

	if (done)
	    ;
	else if (theline[0] == '*')
	    amount += 1;
	else
	{

	    amount = -1;
	    for (lnum = cur_curpos.lnum - 1; lnum > comment_pos->lnum; --lnum)
	    {
		if (linewhite(lnum))
		    continue;
		amount = get_indent_lnum(lnum);
		break;
	    }
	    if (amount == -1)
	    {
		if (!curbuf->b_ind_in_comment2)
		{
		    start = ml_get(comment_pos->lnum);
		    look = start + comment_pos->col + 2;
		    if (*look != NUL)
			comment_pos->col = (colnr_T)(skipwhite(look) - start);
		}
		getvcol(curwin, comment_pos, &col, NULL, NULL);
		amount = col;
		if (curbuf->b_ind_in_comment2 || *look == NUL)
		    amount += curbuf->b_ind_in_comment;
	    }
	}
	goto theend;
    }

    if (*skipwhite(theline) == ']'
	    && (trypos = find_match_char('[', curbuf->b_ind_maxparen)) != NULL)
    {

	amount = get_indent_lnum(trypos->lnum);
	goto theend;
    }

    if (((trypos = find_match_paren(curbuf->b_ind_maxparen)) != NULL
		&& curbuf->b_ind_java == 0)
	    || (tryposBrace = find_start_brace()) != NULL
	    || trypos != NULL)
    {
      if (trypos != NULL && tryposBrace != NULL)
      {

	  if (trypos->lnum != tryposBrace->lnum
		  ? trypos->lnum < tryposBrace->lnum
		  : trypos->col < tryposBrace->col)
	      trypos = NULL;
	  else
	      tryposBrace = NULL;
      }

      if (trypos != NULL)
      {

	if (theline[0] == ')' && curbuf->b_ind_paren_prev)
	{

	    amount = get_indent_lnum(curwin->w_cursor.lnum - 1);
	}
	else
	{
	    amount = -1;
	    our_paren_pos = *trypos;
	    for (lnum = cur_curpos.lnum - 1; lnum > our_paren_pos.lnum; --lnum)
	    {
		l = skipwhite(ml_get(lnum));
		if (cin_nocode(l))
		    continue;
		if (cin_ispreproc_cont(&l, &lnum, &amount))
		    continue;
		curwin->w_cursor.lnum = lnum;

		if ((trypos = ind_find_start_CORS(NULL)) != NULL)
		{
		    lnum = trypos->lnum + 1;
		    continue;
		}

		if ((trypos = find_match_paren(
			corr_ind_maxparen(&cur_curpos))) != NULL
			&& trypos->lnum == our_paren_pos.lnum
			&& trypos->col == our_paren_pos.col)
		{
			amount = get_indent_lnum(lnum);

			if (theline[0] == ')')
			{
			    if (our_paren_pos.lnum != lnum
						       && cur_amount > amount)
				cur_amount = amount;
			    amount = -1;
			}
		    break;
		}
	    }
	}

	if (amount == -1)
	{
	    int	    ignore_paren_col = 0;
	    int	    is_if_for_while = 0;

	    if (curbuf->b_ind_if_for_while)
	    {

		pos_T	    cursor_save = curwin->w_cursor;
		pos_T	    outermost;
		char_u	    *line;

		trypos = &our_paren_pos;
		do {
		    outermost = *trypos;
		    curwin->w_cursor.lnum = outermost.lnum;
		    curwin->w_cursor.col = outermost.col;

		    trypos = find_match_paren(curbuf->b_ind_maxparen);
		} while (trypos && trypos->lnum == outermost.lnum);

		curwin->w_cursor = cursor_save;

		line = ml_get(outermost.lnum);

		is_if_for_while =
		    cin_is_if_for_while_before_offset(line, &outermost.col);
	    }

	    amount = skip_label(our_paren_pos.lnum, &look);
	    look = skipwhite(look);
	    if (*look == '(')
	    {
		linenr_T    save_lnum = curwin->w_cursor.lnum;
		char_u	    *line;
		int	    look_col;

		curwin->w_cursor.lnum = our_paren_pos.lnum;
		line = ml_get_curline();
		look_col = (int)(look - line);
		curwin->w_cursor.col = look_col + 1;
		if ((trypos = findmatchlimit(NULL, ')', 0,
						      curbuf->b_ind_maxparen))
								      != NULL
			  && trypos->lnum == our_paren_pos.lnum
			  && trypos->col < our_paren_pos.col)
		    ignore_paren_col = trypos->col + 1;

		curwin->w_cursor.lnum = save_lnum;
		look = ml_get(our_paren_pos.lnum) + look_col;
	    }
	    if (theline[0] == ')' || (curbuf->b_ind_unclosed == 0
						      && is_if_for_while == 0)
		    || (!curbuf->b_ind_unclosed_noignore && *look == '('
						    && ignore_paren_col == 0))
	    {

		if (theline[0] != ')')
		{
		    cur_amount = MAXCOL;
		    l = ml_get(our_paren_pos.lnum);
		    if (curbuf->b_ind_unclosed_wrapped
				       && cin_ends_in(l, (char_u *)"(", NULL))
		    {

			n = 1;
			for (col = 0; col < our_paren_pos.col; ++col)
			{
			    switch (l[col])
			    {
				case '(':
				case '{': ++n;
					  break;

				case ')':
				case '}': if (n > 1)
					      --n;
					  break;
			    }
			}

			our_paren_pos.col = 0;
			amount += n * curbuf->b_ind_unclosed_wrapped;
		    }
		    else if (curbuf->b_ind_unclosed_whiteok)
			our_paren_pos.col++;
		    else
		    {
			col = our_paren_pos.col + 1;
			while (VIM_ISWHITE(l[col]))
			    col++;
			if (l[col] != NUL)
			    our_paren_pos.col = col;
			else
			    our_paren_pos.col++;
		    }
		}

		if (our_paren_pos.col > 0)
		{
		    getvcol(curwin, &our_paren_pos, &col, NULL, NULL);
		    if (cur_amount > (int)col)
			cur_amount = col;
		}
	    }

	    if (theline[0] == ')' && curbuf->b_ind_matching_paren)
	    {

	    }
	    else if ((curbuf->b_ind_unclosed == 0 && is_if_for_while == 0)
		     || (!curbuf->b_ind_unclosed_noignore
				    && *look == '(' && ignore_paren_col == 0))
	    {
		if (cur_amount != MAXCOL)
		    amount = cur_amount;
	    }
	    else
	    {

		col = our_paren_pos.col;
		while ((int)our_paren_pos.col > ignore_paren_col)
		{
		    --our_paren_pos.col;
		    switch (*ml_get_pos(&our_paren_pos))
		    {
			case '(': amount += curbuf->b_ind_unclosed2;
				  col = our_paren_pos.col;
				  break;
			case ')': amount -= curbuf->b_ind_unclosed2;
				  col = MAXCOL;
				  break;
		    }
		}

		if (col == MAXCOL)
		    amount += curbuf->b_ind_unclosed;
		else
		{
		    curwin->w_cursor.lnum = our_paren_pos.lnum;
		    curwin->w_cursor.col = col;
		    if (find_match_paren_after_brace(curbuf->b_ind_maxparen)
								      != NULL)
			amount += curbuf->b_ind_unclosed2;
		    else
		    {
			if (is_if_for_while)
			    amount += curbuf->b_ind_if_for_while;
			else
			    amount += curbuf->b_ind_unclosed;
		    }
		}

		if (cur_amount < amount)
		    amount = cur_amount;
	    }
	}

	if (cin_iscomment(theline))
	    amount += curbuf->b_ind_comment;
      }
      else
      {

	tryposCopy = *tryposBrace;
	tryposBrace = &tryposCopy;
	trypos = tryposBrace;
	ourscope = trypos->lnum;
	start = ml_get(ourscope);

	look = skipwhite(start);
	if (*look == '{')
	{
	    getvcol(curwin, trypos, &col, NULL, NULL);
	    amount = col;
	    if (*start == '{')
		start_brace = BRACE_IN_COL0;
	    else
		start_brace = BRACE_AT_START;
	}
	else
	{

	    curwin->w_cursor.lnum = ourscope;

	    lnum = ourscope;
	    if (find_last_paren(start, '(', ')')
			&& (trypos = find_match_paren(curbuf->b_ind_maxparen))
								      != NULL)
		lnum = trypos->lnum;

	    if ((curbuf->b_ind_js || curbuf->b_ind_keep_case_label)
			   && cin_iscase(skipwhite(ml_get_curline()), FALSE))
		amount = get_indent();
	    else if (curbuf->b_ind_js)
		amount = get_indent_lnum(lnum);
	    else
		amount = skip_label(lnum, &l);

	    start_brace = BRACE_AT_END;
	}

	if (curbuf->b_ind_js)
	    js_cur_has_key = cin_has_js_key(theline);

	if (theline[0] == '}')
	{

	    amount += curbuf->b_ind_close_extra;
	}
	else
	{

	    lookfor = LOOKFOR_INITIAL;
	    if (cin_iselse(theline))
		lookfor = LOOKFOR_IF;
	    else if (cin_iswhileofdo(theline, cur_curpos.lnum))
		lookfor = LOOKFOR_DO;
	    if (lookfor != LOOKFOR_INITIAL)
	    {
		curwin->w_cursor.lnum = cur_curpos.lnum;
		if (find_match(lookfor, ourscope) == OK)
		{
		    amount = get_indent();
		    goto theend;
		}
	    }

	    if (start_brace == BRACE_IN_COL0)
	    {
		amount = curbuf->b_ind_open_left_imag;
		lookfor_cpp_namespace = TRUE;
	    }
	    else if (start_brace == BRACE_AT_START &&
		    lookfor_cpp_namespace)
	    {

		lookfor_cpp_namespace = TRUE;
	    }
	    else
	    {
		if (start_brace == BRACE_AT_END)
		{
		    amount += curbuf->b_ind_open_imag;

		    l = skipwhite(ml_get_curline());
		    if (cin_is_cpp_namespace(l))
			amount += curbuf->b_ind_cpp_namespace;
		    else if (cin_is_cpp_extern_c(l))
			amount += curbuf->b_ind_cpp_extern_c;
		}
		else
		{

		    amount -= curbuf->b_ind_open_extra;
		    if (amount < 0)
			amount = 0;
		}
	    }

	    lookfor_break = FALSE;

	    if (cin_iscase(theline, FALSE))
	    {
		lookfor = LOOKFOR_CASE;
		amount += curbuf->b_ind_case;
	    }
	    else if (cin_isscopedecl(theline))
	    {
		lookfor = LOOKFOR_SCOPEDECL;
		amount += curbuf->b_ind_scopedecl;
	    }
	    else
	    {
		if (curbuf->b_ind_case_break && cin_isbreak(theline))

		    lookfor_break = TRUE;

		lookfor = LOOKFOR_INITIAL;

		amount += curbuf->b_ind_level;
	    }
	    scope_amount = amount;
	    whilelevel = 0;

	    curwin->w_cursor = cur_curpos;
	    for (;;)
	    {
		curwin->w_cursor.lnum--;
		curwin->w_cursor.col = 0;

		if (curwin->w_cursor.lnum <= ourscope)
		{

		    if (lookfor == LOOKFOR_ENUM_OR_INIT)
		    {
			if (curwin->w_cursor.lnum == 0
				|| curwin->w_cursor.lnum
					  < ourscope - curbuf->b_ind_maxparen)
			{

			    if (cont_amount > 0)
				amount = cont_amount;
			    else if (!curbuf->b_ind_js)
				amount += ind_continuation;
			    break;
			}

			l = ml_get_curline();

			trypos = ind_find_start_CORS(NULL);
			if (trypos != NULL)
			{
			    curwin->w_cursor.lnum = trypos->lnum + 1;
			    curwin->w_cursor.col = 0;
			    continue;
			}

			if (cin_ispreproc_cont(&l, &curwin->w_cursor.lnum,
								    &amount))
			    continue;

			if (cin_nocode(l))
			    continue;

			terminated = cin_isterminated(l, FALSE, TRUE);

			if (start_brace != BRACE_IN_COL0
			     || !cin_isfuncdecl(&l, curwin->w_cursor.lnum, 0))
			{

			    if (terminated == ',')
				break;

			    if (terminated != ';' && cin_isinit())
				break;

			    if (terminated == 0 || terminated == '{')
				continue;
			}

			if (terminated != ';')
			{

			    trypos = NULL;
			    if (find_last_paren(l, '(', ')'))
				trypos = find_match_paren(
						      curbuf->b_ind_maxparen);

			    if (trypos == NULL && find_last_paren(l, '{', '}'))
				trypos = find_start_brace();

			    if (trypos != NULL)
			    {
				curwin->w_cursor.lnum = trypos->lnum + 1;
				curwin->w_cursor.col = 0;
				continue;
			    }
			}

			if (cont_amount > 0)
			    amount = cont_amount;
			else
			    amount += ind_continuation;
		    }
		    else if (lookfor == LOOKFOR_UNTERM)
		    {
			if (cont_amount > 0)
			    amount = cont_amount;
			else
			    amount += ind_continuation;
		    }
		    else
		    {
			if (lookfor != LOOKFOR_TERM
					&& lookfor != LOOKFOR_CPP_BASECLASS
					&& lookfor != LOOKFOR_COMMA)
			{
			    amount = scope_amount;
			    if (theline[0] == '{')
			    {
				amount += curbuf->b_ind_open_extra;
				added_to_amount = curbuf->b_ind_open_extra;
			    }
			}

			if (lookfor_cpp_namespace)
			{

			    if (curwin->w_cursor.lnum == ourscope)
				continue;

			    if (curwin->w_cursor.lnum == 0
				    || curwin->w_cursor.lnum
					      < ourscope - FIND_NAMESPACE_LIM)
				break;

			    l = ml_get_curline();

			    trypos = ind_find_start_CORS(NULL);
			    if (trypos != NULL)
			    {
				curwin->w_cursor.lnum = trypos->lnum + 1;
				curwin->w_cursor.col = 0;
				continue;
			    }

			    if (cin_ispreproc_cont(&l, &curwin->w_cursor.lnum,
								    &amount))
				continue;

			    if (cin_is_cpp_namespace(l))
			    {
				amount += curbuf->b_ind_cpp_namespace
							    - added_to_amount;
				break;
			    }
			    else if (cin_is_cpp_extern_c(l))
			    {
				amount += curbuf->b_ind_cpp_extern_c
							    - added_to_amount;
				break;
			    }

			    if (cin_nocode(l))
				continue;
			}
		    }
		    break;
		}

		if ((trypos = ind_find_start_CORS(&raw_string_start)) != NULL)
		{
		    curwin->w_cursor.lnum = trypos->lnum + 1;
		    curwin->w_cursor.col = 0;
		    continue;
		}

		l = ml_get_curline();

		iscase = cin_iscase(l, FALSE);
		if (iscase || cin_isscopedecl(l))
		{

		    if (lookfor == LOOKFOR_CPP_BASECLASS)
			break;

		    if (whilelevel > 0)
			continue;

		    if (lookfor == LOOKFOR_UNTERM
					   || lookfor == LOOKFOR_ENUM_OR_INIT)
		    {
			if (cont_amount > 0)
			    amount = cont_amount;
			else
			    amount += ind_continuation;
			break;
		    }

		    if (       (iscase && lookfor == LOOKFOR_CASE)
			    || (iscase && lookfor_break)
			    || (!iscase && lookfor == LOOKFOR_SCOPEDECL))
		    {

			if ((trypos = find_start_brace()) == NULL
						  || trypos->lnum == ourscope)
			{
			    amount = get_indent();
			    break;
			}
			continue;
		    }

		    n = get_indent_nolabel(curwin->w_cursor.lnum);

		    if (lookfor == LOOKFOR_TERM)
		    {
			if (n)
			    amount = n;

			if (!lookfor_break)
			    break;
		    }

		    if (n)
		    {
			amount = n;
			l = after_label(ml_get_curline());
			if (l != NULL && cin_is_cinword(l))
			{
			    if (theline[0] == '{')
				amount += curbuf->b_ind_open_extra;
			    else
				amount += curbuf->b_ind_level
						     + curbuf->b_ind_no_brace;
			}
			break;
		    }

		    scope_amount = get_indent() + (iscase
					? curbuf->b_ind_case_code
					: curbuf->b_ind_scopedecl_code);
		    lookfor = curbuf->b_ind_case_break
					      ? LOOKFOR_NOBREAK : LOOKFOR_ANY;
		    continue;
		}

		if (lookfor == LOOKFOR_CASE || lookfor == LOOKFOR_SCOPEDECL)
		{
		    if (find_last_paren(l, '{', '}')
				     && (trypos = find_start_brace()) != NULL)
		    {
			curwin->w_cursor.lnum = trypos->lnum + 1;
			curwin->w_cursor.col = 0;
		    }
		    continue;
		}

		if (!curbuf->b_ind_js && cin_islabel())
		{
		    l = after_label(ml_get_curline());
		    if (l == NULL || cin_nocode(l))
			continue;
		}

		l = ml_get_curline();
		if (cin_ispreproc_cont(&l, &curwin->w_cursor.lnum, &amount)
							     || cin_nocode(l))
		    continue;

		n = FALSE;
		if (lookfor != LOOKFOR_TERM && curbuf->b_ind_cpp_baseclass > 0)
		{
		    n = cin_is_cpp_baseclass(&cache_cpp_baseclass);
		    l = ml_get_curline();
		}
		if (n)
		{
		    if (lookfor == LOOKFOR_UNTERM)
		    {
			if (cont_amount > 0)
			    amount = cont_amount;
			else
			    amount += ind_continuation;
		    }
		    else if (theline[0] == '{')
		    {

			lookfor = LOOKFOR_UNTERM;
			ind_continuation = 0;
			continue;
		    }
		    else

			amount = get_baseclass_amount(
						cache_cpp_baseclass.lpos.col);
		    break;
		}
		else if (lookfor == LOOKFOR_CPP_BASECLASS)
		{

		    if (cin_isterminated(l, TRUE, FALSE))
			break;
		    else
			continue;
		}

		terminated = cin_isterminated(l, FALSE, TRUE);

		if (js_cur_has_key)
		{
		    js_cur_has_key = 0;
		    if (curbuf->b_ind_js && terminated == ',')
		    {

			lookfor = LOOKFOR_JS_KEY;
		    }
		}
		if (lookfor == LOOKFOR_JS_KEY && cin_has_js_key(l))
		{
		    amount = get_indent();
		    break;
		}
		if (lookfor == LOOKFOR_COMMA)
		{
		    if (tryposBrace != NULL && tryposBrace->lnum
						    >= curwin->w_cursor.lnum)
			break;
		    if (terminated == ',')

			break;
		    else
		    {
			amount = get_indent();
			if (curwin->w_cursor.lnum - 1 == ourscope)

			    break;
		    }
		}

		if (terminated == 0 || (lookfor != LOOKFOR_UNTERM
							&& terminated == ','))
		{
		    if (lookfor != LOOKFOR_ENUM_OR_INIT &&
			    (*skipwhite(l) == '[' || l[STRLEN(l) - 1] == '['))
			amount += ind_continuation;

		    (void)find_last_paren(l, '(', ')');
		    trypos = find_match_paren(corr_ind_maxparen(&cur_curpos));
		    if (trypos != NULL && (trypos->lnum < tryposBrace->lnum
				|| (trypos->lnum == tryposBrace->lnum
				    && trypos->col < tryposBrace->col)))
			trypos = NULL;

		    if (trypos == NULL && terminated == ','
					      && find_last_paren(l, '{', '}'))
			trypos = find_start_brace();

		    if (trypos != NULL)
		    {

			curwin->w_cursor = *trypos;
			l = ml_get_curline();
			if (cin_iscase(l, FALSE) || cin_isscopedecl(l))
			{
			    ++curwin->w_cursor.lnum;
			    curwin->w_cursor.col = 0;
			    continue;
			}
		    }

		    if (terminated == ',')
		    {
			while (curwin->w_cursor.lnum > 1)
			{
			    l = ml_get(curwin->w_cursor.lnum - 1);
			    if (*l == NUL || l[STRLEN(l) - 1] != '\\')
				break;
			    --curwin->w_cursor.lnum;
			    curwin->w_cursor.col = 0;
			}
		    }

		    if (curbuf->b_ind_js)
			cur_amount = get_indent();
		    else
			cur_amount = skip_label(curwin->w_cursor.lnum, &l);

		    if (terminated != ',' && lookfor != LOOKFOR_TERM
							 && theline[0] == '{')
		    {
			amount = cur_amount;

			if (*skipwhite(l) != '{')
			    amount += curbuf->b_ind_open_extra;

			if (curbuf->b_ind_cpp_baseclass && !curbuf->b_ind_js)
			{

			    lookfor = LOOKFOR_CPP_BASECLASS;
			    continue;
			}
			break;
		    }

		    if (cin_is_cinword(l) || cin_iselse(skipwhite(l)))
		    {

			if (lookfor == LOOKFOR_UNTERM
					   || lookfor == LOOKFOR_ENUM_OR_INIT)
			{
			    if (cont_amount > 0)
				amount = cont_amount;
			    else
				amount += ind_continuation;
			    break;
			}

			amount = cur_amount;
			if (theline[0] == '{')
			    amount += curbuf->b_ind_open_extra;
			if (lookfor != LOOKFOR_TERM)
			{
			    amount += curbuf->b_ind_level
						     + curbuf->b_ind_no_brace;
			    break;
			}

			l = skipwhite(ml_get_curline());
			if (cin_isdo(l))
			{
			    if (whilelevel == 0)
				break;
			    --whilelevel;
			}

			if (cin_iselse(l) && whilelevel == 0)
			{

			    if (*l == '}')
				curwin->w_cursor.col =
					  (colnr_T)(l - ml_get_curline()) + 1;

			    if ((trypos = find_start_brace()) == NULL
				       || find_match(LOOKFOR_IF, trypos->lnum)
								      == FAIL)
				break;
			}
		    }

		    else
		    {

			if (lookfor == LOOKFOR_UNTERM)
			{

			    if (terminated == ',')
				amount += ind_continuation;
			    break;
			}

			if (lookfor == LOOKFOR_ENUM_OR_INIT)
			{

			    if (terminated == ',')
			    {
				if (curbuf->b_ind_cpp_baseclass == 0)
				    break;

				lookfor = LOOKFOR_CPP_BASECLASS;
				continue;
			    }

			    if (amount > cur_amount)
				amount = cur_amount;
			}
			else
			{

			    l = ml_get_curline();
			    amount = cur_amount;

			    n = (int)STRLEN(l);
			    if (terminated == ',' && (*skipwhite(l) == ']'
					|| (n >=2 && l[n - 2] == ']')))
				break;

			    if (lookfor == LOOKFOR_INITIAL && terminated == ',')
			    {
				if (curbuf->b_ind_js)
				{

				    if (cin_iscomment(skipwhite(l)))
					break;
				    lookfor = LOOKFOR_COMMA;
				    trypos = find_match_char('[',
						      curbuf->b_ind_maxparen);
				    if (trypos != NULL)
				    {
					if (trypos->lnum
						 == curwin->w_cursor.lnum - 1)
					{

					    break;
					}
					ourscope = trypos->lnum;
				    }
				}
				else
				{
				    lookfor = LOOKFOR_ENUM_OR_INIT;
				    cont_amount = cin_first_id_amount();
				}
			    }
			    else
			    {
				if (lookfor == LOOKFOR_INITIAL
					&& *l != NUL
					&& l[STRLEN(l) - 1] == '\\')

				    cont_amount = cin_get_equal_amount(
						       curwin->w_cursor.lnum);
				if (lookfor != LOOKFOR_TERM
						&& lookfor != LOOKFOR_JS_KEY
						&& lookfor != LOOKFOR_COMMA
						&& raw_string_start != curwin->w_cursor.lnum)
				    lookfor = LOOKFOR_UNTERM;
			    }
			}
		    }
		}

		else if (cin_iswhileofdo_end(terminated))
		{

		    if (lookfor == LOOKFOR_UNTERM
					   || lookfor == LOOKFOR_ENUM_OR_INIT)
		    {
			if (cont_amount > 0)
			    amount = cont_amount;
			else
			    amount += ind_continuation;
			break;
		    }

		    if (whilelevel == 0)
		    {
			lookfor = LOOKFOR_TERM;
			amount = get_indent();
			if (theline[0] == '{')
			    amount += curbuf->b_ind_open_extra;
		    }
		    ++whilelevel;
		}

		else
		{

		    if (lookfor == LOOKFOR_NOBREAK
				  && cin_isbreak(skipwhite(ml_get_curline())))
		    {
			lookfor = LOOKFOR_ANY;
			continue;
		    }

		    if (whilelevel > 0)
		    {
			l = cin_skipcomment(ml_get_curline());
			if (cin_isdo(l))
			{
			    amount = get_indent();
			    --whilelevel;
			    continue;
			}
		    }

		    if (lookfor == LOOKFOR_UNTERM
					   || lookfor == LOOKFOR_ENUM_OR_INIT)
		    {
			if (cont_amount > 0)
			    amount = cont_amount;
			else
			    amount += ind_continuation;
			break;
		    }

		    if (lookfor == LOOKFOR_TERM)
		    {
			if (!lookfor_break && whilelevel == 0)
			    break;
		    }

		    else
		    {

term_again:
			l = ml_get_curline();
			if (find_last_paren(l, '(', ')')
				&& (trypos = find_match_paren(
					   curbuf->b_ind_maxparen)) != NULL)
			{

			    curwin->w_cursor = *trypos;
			    l = ml_get_curline();
			    if (cin_iscase(l, FALSE) || cin_isscopedecl(l))
			    {
				++curwin->w_cursor.lnum;
				curwin->w_cursor.col = 0;
				continue;
			    }
			}

			iscase = (curbuf->b_ind_keep_case_label
						     && cin_iscase(l, FALSE));

			amount = skip_label(curwin->w_cursor.lnum, &l);

			if (theline[0] == '{')
			    amount += curbuf->b_ind_open_extra;

			l = skipwhite(l);
			if (*l == '{')
			    amount -= curbuf->b_ind_open_extra;
			lookfor = iscase ? LOOKFOR_ANY : LOOKFOR_TERM;

			if (lookfor == LOOKFOR_TERM
				&& *l != '}'
				&& cin_iselse(l)
				&& whilelevel == 0)
			{
			    if ((trypos = find_start_brace()) == NULL
				       || find_match(LOOKFOR_IF, trypos->lnum)
								      == FAIL)
				break;
			    continue;
			}

			l = ml_get_curline();
			if (find_last_paren(l, '{', '}')
				     && (trypos = find_start_brace()) != NULL)
			{
			    curwin->w_cursor = *trypos;

			    l = cin_skipcomment(ml_get_curline());
			    if (*l == '}' || !cin_iselse(l))
				goto term_again;
			    ++curwin->w_cursor.lnum;
			    curwin->w_cursor.col = 0;
			}
		    }
		}
	    }
	}
      }

      if (cin_iscomment(theline))
	  amount += curbuf->b_ind_comment;

      if (curbuf->b_ind_jump_label > 0 && original_line_islabel)
	  amount -= curbuf->b_ind_jump_label;

      goto theend;
    }

    if (theline[0] == '{')
    {
	amount = curbuf->b_ind_first_open;
	goto theend;
    }

    if (cur_curpos.lnum < curbuf->b_ml.ml_line_count
	    && !cin_nocode(theline)
	    && vim_strchr(theline, '{') == NULL
	    && vim_strchr(theline, '}') == NULL
	    && !cin_ends_in(theline, (char_u *)":", NULL)
	    && !cin_ends_in(theline, (char_u *)",", NULL)
	    && cin_isfuncdecl(NULL, cur_curpos.lnum + 1,
			      cur_curpos.lnum + 1)
	    && !cin_isterminated(theline, FALSE, TRUE))
    {
	amount = curbuf->b_ind_func_type;
	goto theend;
    }

    amount = 0;
    curwin->w_cursor = cur_curpos;
    while (curwin->w_cursor.lnum > 1)
    {
	curwin->w_cursor.lnum--;
	curwin->w_cursor.col = 0;

	l = ml_get_curline();

	if ((trypos = ind_find_start_CORS(NULL)) != NULL)
	{
	    curwin->w_cursor.lnum = trypos->lnum + 1;
	    curwin->w_cursor.col = 0;
	    continue;
	}

	n = FALSE;
	if (curbuf->b_ind_cpp_baseclass != 0 && theline[0] != '{')
	{
	    n = cin_is_cpp_baseclass(&cache_cpp_baseclass);
	    l = ml_get_curline();
	}
	if (n)
	{

	    amount = get_baseclass_amount(cache_cpp_baseclass.lpos.col);
	    break;
	}

	if (cin_ispreproc_cont(&l, &curwin->w_cursor.lnum, &amount))
	    continue;

	if (cin_nocode(l))
	    continue;

	n = 0;
	if (cin_ends_in(l, (char_u *)",", NULL)
		     || (*l != NUL && (n = l[STRLEN(l) - 1]) == '\\'))
	{

	    if (find_last_paren(l, '(', ')')
		    && (trypos = find_match_paren(
				     curbuf->b_ind_maxparen)) != NULL)
		curwin->w_cursor = *trypos;

	    while (n == 0 && curwin->w_cursor.lnum > 1)
	    {
		l = ml_get(curwin->w_cursor.lnum - 1);
		if (*l == NUL || l[STRLEN(l) - 1] != '\\')
		    break;
		--curwin->w_cursor.lnum;
		curwin->w_cursor.col = 0;
	    }

	    amount = get_indent();

	    if (amount == 0)
		amount = cin_first_id_amount();
	    if (amount == 0)
		amount = ind_continuation;
	    break;
	}

	if (cin_isfuncdecl(NULL, cur_curpos.lnum, 0))
	    break;
	l = ml_get_curline();

	if (*skipwhite(l) == '}')
	    break;

	if (cin_ends_in(l, (char_u *)"};", NULL))
	    break;

	if (cin_ends_in(l, (char_u *)"[", NULL))
	{
	    amount = get_indent() + ind_continuation;
	    break;
	}

	if (*(look = skipwhite(l)) == ';' && cin_nocode(look + 1))
	{
	    pos_T curpos_save = curwin->w_cursor;

	    while (curwin->w_cursor.lnum > 1)
	    {
		look = ml_get(--curwin->w_cursor.lnum);
		if (!(cin_nocode(look) || cin_ispreproc_cont(
				      &look, &curwin->w_cursor.lnum, &amount)))
		    break;
	    }
	    if (curwin->w_cursor.lnum > 0
			    && cin_ends_in(look, (char_u *)"}", NULL))
		break;

	    curwin->w_cursor = curpos_save;
	}

	if (cin_isfuncdecl(&l, curwin->w_cursor.lnum, 0))
	{
	    amount = curbuf->b_ind_param;
	    break;
	}

	if (cin_ends_in(l, (char_u *)";", NULL))
	{
	    l = ml_get(curwin->w_cursor.lnum - 1);
	    if (cin_ends_in(l, (char_u *)",", NULL)
		    || (*l != NUL && l[STRLEN(l) - 1] == '\\'))
		break;
	    l = ml_get_curline();
	}

	find_last_paren(l, '(', ')');

	if ((trypos = find_match_paren(curbuf->b_ind_maxparen)) != NULL)
	    curwin->w_cursor = *trypos;
	amount = get_indent();
	break;
    }

    if (cin_iscomment(theline))
	amount += curbuf->b_ind_comment;

    if (cur_curpos.lnum > 1)
    {
	l = ml_get(cur_curpos.lnum - 1);
	if (*l != NUL && l[STRLEN(l) - 1] == '\\')
	{
	    cur_amount = cin_get_equal_amount(cur_curpos.lnum - 1);
	    if (cur_amount > 0)
		amount = cur_amount;
	    else if (cur_amount == 0)
		amount += ind_continuation;
	}
    }

theend:
    if (amount < 0)
	amount = 0;

laterend:

    curwin->w_cursor = cur_curpos;

    vim_free(linecopy);

    return amount;
}
}
}
}
}
}
}
}
