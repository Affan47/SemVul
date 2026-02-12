get_address(
    exarg_T	*eap UNUSED,
    char_u	**ptr,
    cmd_addr_T	addr_type,
    int		skip,
    int		silent,
    int		to_other_file,
    int		address_count UNUSED)
{
    int		c;
    int		i;
    long	n;
    char_u	*cmd;
    pos_T	pos;
    pos_T	*fp;
    linenr_T	lnum;
    buf_T	*buf;

    cmd = skipwhite(*ptr);
    lnum = MAXLNUM;
    do
    {
	switch (*cmd)
	{
	    case '.':
		++cmd;
		switch (addr_type)
		{
		    case ADDR_LINES:
		    case ADDR_OTHER:
			lnum = curwin->w_cursor.lnum;
			break;
		    case ADDR_WINDOWS:
			lnum = CURRENT_WIN_NR;
			break;
		    case ADDR_ARGUMENTS:
			lnum = curwin->w_arg_idx + 1;
			break;
		    case ADDR_LOADED_BUFFERS:
		    case ADDR_BUFFERS:
			lnum = curbuf->b_fnum;
			break;
		    case ADDR_TABS:
			lnum = CURRENT_TAB_NR;
			break;
		    case ADDR_NONE:
		    case ADDR_TABS_RELATIVE:
		    case ADDR_UNSIGNED:
			addr_error(addr_type);
			cmd = NULL;
			goto error;
			break;
		    case ADDR_QUICKFIX:
#ifdef FEAT_QUICKFIX
			lnum = qf_get_cur_idx(eap);
#endif
			break;
		    case ADDR_QUICKFIX_VALID:
#ifdef FEAT_QUICKFIX
			lnum = qf_get_cur_valid_idx(eap);
#endif
			break;
		}
		break;

	    case '$':
		++cmd;
		switch (addr_type)
		{
		    case ADDR_LINES:
		    case ADDR_OTHER:
			lnum = curbuf->b_ml.ml_line_count;
			break;
		    case ADDR_WINDOWS:
			lnum = LAST_WIN_NR;
			break;
		    case ADDR_ARGUMENTS:
			lnum = ARGCOUNT;
			break;
		    case ADDR_LOADED_BUFFERS:
			buf = lastbuf;
			while (buf->b_ml.ml_mfp == NULL)
			{
			    if (buf->b_prev == NULL)
				break;
			    buf = buf->b_prev;
			}
			lnum = buf->b_fnum;
			break;
		    case ADDR_BUFFERS:
			lnum = lastbuf->b_fnum;
			break;
		    case ADDR_TABS:
			lnum = LAST_TAB_NR;
			break;
		    case ADDR_NONE:
		    case ADDR_TABS_RELATIVE:
		    case ADDR_UNSIGNED:
			addr_error(addr_type);
			cmd = NULL;
			goto error;
			break;
		    case ADDR_QUICKFIX:
#ifdef FEAT_QUICKFIX
			lnum = qf_get_size(eap);
			if (lnum == 0)
			    lnum = 1;
#endif
			break;
		    case ADDR_QUICKFIX_VALID:
#ifdef FEAT_QUICKFIX
			lnum = qf_get_valid_size(eap);
			if (lnum == 0)
			    lnum = 1;
#endif
			break;
		}
		break;

	    case '\'':
		if (*++cmd == NUL)
		{
		    cmd = NULL;
		    goto error;
		}
		if (addr_type != ADDR_LINES)
		{
		    addr_error(addr_type);
		    cmd = NULL;
		    goto error;
		}
		if (skip)
		    ++cmd;
		else
		{


		    fp = getmark(*cmd, to_other_file && cmd[1] == NUL);
		    ++cmd;
		    if (fp == (pos_T *)-1)

			lnum = curwin->w_cursor.lnum;
		    else
		    {
			if (check_mark(fp) == FAIL)
			{
			    cmd = NULL;
			    goto error;
			}
			lnum = fp->lnum;
		    }
		}
		break;

	    case '/':
	    case '?':
		c = *cmd++;
		if (addr_type != ADDR_LINES)
		{
		    addr_error(addr_type);
		    cmd = NULL;
		    goto error;
		}
		if (skip)
		{
		    cmd = skip_regexp(cmd, c, magic_isset());
		    if (*cmd == c)
			++cmd;
		}
		else
		{
		    int flags;

		    pos = curwin->w_cursor;


		    if (lnum > 0 && lnum != MAXLNUM)
			curwin->w_cursor.lnum =
				lnum > curbuf->b_ml.ml_line_count
					   ? curbuf->b_ml.ml_line_count : lnum;


		    if (c == '/' && curwin->w_cursor.lnum > 0)
			curwin->w_cursor.col = MAXCOL;
		    else
			curwin->w_cursor.col = 0;
		    searchcmdlen = 0;
		    flags = silent ? 0 : SEARCH_HIS | SEARCH_MSG;
		    if (!do_search(NULL, c, c, cmd, 1L, flags, NULL))
		    {
			curwin->w_cursor = pos;
			cmd = NULL;
			goto error;
		    }
		    lnum = curwin->w_cursor.lnum;
		    curwin->w_cursor = pos;

		    cmd += searchcmdlen;
		}
		break;

	    case '\\':
		++cmd;
		if (addr_type != ADDR_LINES)
		{
		    addr_error(addr_type);
		    cmd = NULL;
		    goto error;
		}
		if (*cmd == '&')
		    i = RE_SUBST;
		else if (*cmd == '?' || *cmd == '/')
		    i = RE_SEARCH;
		else
		{
		    emsg(_(e_backslash_should_be_followed_by));
		    cmd = NULL;
		    goto error;
		}

		if (!skip)
		{


		    if (lnum != MAXLNUM)
			pos.lnum = lnum;
		    else
			pos.lnum = curwin->w_cursor.lnum;


		    if (*cmd != '?')
			pos.col = MAXCOL;
		    else
			pos.col = 0;
		    pos.coladd = 0;
		    if (searchit(curwin, curbuf, &pos, NULL,
				*cmd == '?' ? BACKWARD : FORWARD,
				(char_u *)"", 1L, SEARCH_MSG, i, NULL) != FAIL)
			lnum = pos.lnum;
		    else
		    {
			cmd = NULL;
			goto error;
		    }
		}
		++cmd;
		break;

	    default:
		if (VIM_ISDIGIT(*cmd))
		    lnum = getdigits(&cmd);
	}

	for (;;)
	{
	    cmd = skipwhite(cmd);
	    if (*cmd != '-' && *cmd != '+' && !VIM_ISDIGIT(*cmd))
		break;

	    if (lnum == MAXLNUM)
	    {
		switch (addr_type)
		{
		    case ADDR_LINES:
		    case ADDR_OTHER:

			lnum = curwin->w_cursor.lnum;
			break;
		    case ADDR_WINDOWS:
			lnum = CURRENT_WIN_NR;
			break;
		    case ADDR_ARGUMENTS:
			lnum = curwin->w_arg_idx + 1;
			break;
		    case ADDR_LOADED_BUFFERS:
		    case ADDR_BUFFERS:
			lnum = curbuf->b_fnum;
			break;
		    case ADDR_TABS:
			lnum = CURRENT_TAB_NR;
			break;
		    case ADDR_TABS_RELATIVE:
			lnum = 1;
			break;
		    case ADDR_QUICKFIX:
#ifdef FEAT_QUICKFIX
			lnum = qf_get_cur_idx(eap);
#endif
			break;
		    case ADDR_QUICKFIX_VALID:
#ifdef FEAT_QUICKFIX
			lnum = qf_get_cur_valid_idx(eap);
#endif
			break;
		    case ADDR_NONE:
		    case ADDR_UNSIGNED:
			lnum = 0;
			break;
		}
	    }

	    if (VIM_ISDIGIT(*cmd))
		i = '+';
	    else
		i = *cmd++;
	    if (!VIM_ISDIGIT(*cmd))
		n = 1;
	    else
		n = getdigits(&cmd);

	    if (addr_type == ADDR_TABS_RELATIVE)
	    {
		emsg(_(e_invalid_range));
		cmd = NULL;
		goto error;
	    }
	    else if (addr_type == ADDR_LOADED_BUFFERS
		    || addr_type == ADDR_BUFFERS)
		lnum = compute_buffer_local_count(
				    addr_type, lnum, (i == '-') ? -1 * n : n);
	    else
	    {
#ifdef FEAT_FOLDING


		if (addr_type == ADDR_LINES && (i == '-' || i == '+')
			&& address_count >= 2)
		    (void)hasFolding(lnum, NULL, &lnum);
#endif
		if (i == '-')
		    lnum -= n;
		else
		    lnum += n;
	    }
	}
    } while (*cmd == '/' || *cmd == '?');

error:
    *ptr = cmd;
    return lnum;
}
