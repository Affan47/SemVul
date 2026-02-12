find_decl(
    char_u	*ptr,
    int		len,
    int		locally,
    int		thisblock,
    int		flags_arg)
{
    char_u	*pat;
    pos_T	old_pos;
    pos_T	par_pos;
    pos_T	found_pos;
    int		t;
    int		save_p_ws;
    int		save_p_scs;
    int		retval = OK;
    int		incll;
    int		searchflags = flags_arg;
    int		valid;

    if ((pat = alloc(len + 7)) == NULL)
	return FAIL;


    sprintf((char *)pat, vim_iswordp(ptr) ? "\\V\\<%.*s\\>" : "\\V%.*s",
								    len, ptr);
    old_pos = curwin->w_cursor;
    save_p_ws = p_ws;
    save_p_scs = p_scs;
    p_ws = FALSE;
    p_scs = FALSE;


    if (!locally || !findpar(&incll, BACKWARD, 1L, '{', FALSE))
    {
	setpcmark();
	curwin->w_cursor.lnum = 1;
	par_pos = curwin->w_cursor;
    }
    else
    {
	par_pos = curwin->w_cursor;
	while (curwin->w_cursor.lnum > 1 && *skipwhite(ml_get_curline()) != NUL)
	    --curwin->w_cursor.lnum;
    }
    curwin->w_cursor.col = 0;


    CLEAR_POS(&found_pos);
    for (;;)
    {
	t = searchit(curwin, curbuf, &curwin->w_cursor, NULL, FORWARD,
					  pat, 1L, searchflags, RE_LAST, NULL);
	if (curwin->w_cursor.lnum >= old_pos.lnum)
	    t = FAIL;

	if (thisblock && t != FAIL)
	{
	    pos_T	*pos;


	    if ((pos = findmatchlimit(NULL, '}', FM_FORWARD,
		     (int)(old_pos.lnum - curwin->w_cursor.lnum + 1))) != NULL
		    && pos->lnum < old_pos.lnum)
	    {


		curwin->w_cursor = *pos;
		continue;
	    }
	}

	if (t == FAIL)
	{

	    if (found_pos.lnum != 0)
	    {
		curwin->w_cursor = found_pos;
		t = OK;
	    }
	    break;
	}
	if (get_leader_len(ml_get_curline(), NULL, FALSE, TRUE) > 0)
	{

	    ++curwin->w_cursor.lnum;
	    curwin->w_cursor.col = 0;
	    continue;
	}
	valid = is_ident(ml_get_curline(), curwin->w_cursor.col);


	if (!valid && found_pos.lnum != 0)
	{
	    curwin->w_cursor = found_pos;
	    break;
	}


	if (valid && !locally)
	    break;
	if (valid && curwin->w_cursor.lnum >= par_pos.lnum)
	{

	    if (found_pos.lnum != 0)
		curwin->w_cursor = found_pos;
	    break;
	}


	if (!valid)
	    CLEAR_POS(&found_pos);
	else
	    found_pos = curwin->w_cursor;


	searchflags &= ~SEARCH_START;
    }

    if (t == FAIL)
    {
	retval = FAIL;
	curwin->w_cursor = old_pos;
    }
    else
    {
	curwin->w_set_curswant = TRUE;

	reset_search_dir();
    }

    vim_free(pat);
    p_ws = save_p_ws;
    p_scs = save_p_scs;

    return retval;
}
