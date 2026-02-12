do_search(
    oparg_T	    *oap,
    int		    dirc,
    int		    search_delim,

    char_u	    *pat,
    long	    count,
    int		    options,
    searchit_arg_T  *sia)
{
    pos_T	    pos;
    char_u	    *searchstr;
    soffset_T	    old_off;
    int		    retval;
    char_u	    *p;
    long	    c;
    char_u	    *dircp;
    char_u	    *strcopy = NULL;
    char_u	    *ps;
    char_u	    *msgbuf = NULL;
    size_t	    len;
    int		    has_offset = FALSE;


    if (spats[0].off.line && vim_strchr(p_cpo, CPO_LINEOFF) != NULL)
    {
	spats[0].off.line = FALSE;
	spats[0].off.off = 0;
    }


    old_off = spats[0].off;

    pos = curwin->w_cursor;


    if (dirc == 0)
	dirc = spats[0].off.dir;
    else
    {
	spats[0].off.dir = dirc;
#if defined(FEAT_EVAL)
	set_vv_searchforward();
#endif
    }
    if (options & SEARCH_REV)
    {
#ifdef MSWIN


	dirc = (dirc == '/')  ?  '?'  :  '/';
#else
	if (dirc == '/')
	    dirc = '?';
	else
	    dirc = '/';
#endif
    }

#ifdef FEAT_FOLDING


    if (dirc == '/')
    {
	if (hasFolding(pos.lnum, NULL, &pos.lnum))
	    pos.col = MAXCOL - 2;
    }
    else
    {
	if (hasFolding(pos.lnum, &pos.lnum, NULL))
	    pos.col = 0;
    }
#endif

#ifdef FEAT_SEARCH_EXTRA


    if (no_hlsearch && !(options & SEARCH_KEEP))
    {
	redraw_all_later(SOME_VALID);
	set_no_hlsearch(FALSE);
    }
#endif


    for (;;)
    {
	int		show_top_bot_msg = FALSE;

	searchstr = pat;
	dircp = NULL;

	if (pat == NULL || *pat == NUL || *pat == search_delim)
	{
	    if (spats[RE_SEARCH].pat == NULL)
	    {
		searchstr = spats[RE_SUBST].pat;
		if (searchstr == NULL)
		{
		    emsg(_(e_no_previous_regular_expression));
		    retval = 0;
		    goto end_do_search;
		}
	    }
	    else
	    {

		searchstr = (char_u *)"";
	    }
	}

	if (pat != NULL && *pat != NUL)
	{


	    ps = strcopy;
	    p = skip_regexp_ex(pat, search_delim, magic_isset(),
							&strcopy, NULL, NULL);
	    if (strcopy != ps)
	    {

		searchcmdlen += (int)(STRLEN(pat) - STRLEN(strcopy));
		pat = strcopy;
		searchstr = strcopy;
	    }
	    if (*p == search_delim)
	    {
		dircp = p;
		*p++ = NUL;
	    }
	    spats[0].off.line = FALSE;
	    spats[0].off.end = FALSE;
	    spats[0].off.off = 0;


	    if (*p == '+' || *p == '-' || VIM_ISDIGIT(*p))
		spats[0].off.line = TRUE;
	    else if ((options & SEARCH_OPT)
				      && (*p == 'e' || *p == 's' || *p == 'b'))
	    {
		if (*p == 'e')
		    spats[0].off.end = SEARCH_END;
		++p;
	    }
	    if (VIM_ISDIGIT(*p) || *p == '+' || *p == '-')
	    {

		if (VIM_ISDIGIT(*p) || VIM_ISDIGIT(*(p + 1)))
		    spats[0].off.off = atol((char *)p);
		else if (*p == '-')
		    spats[0].off.off = -1;
		else
		    spats[0].off.off = 1;
		++p;
		while (VIM_ISDIGIT(*p))
		    ++p;
	    }


	    searchcmdlen += (int)(p - pat);

	    pat = p;
	}

	if ((options & SEARCH_ECHO) && messaging()
		&& !msg_silent
		&& (!cmd_silent || !shortmess(SHM_SEARCHCOUNT)))
	{
	    char_u	*trunc;
	    char_u	off_buf[40];
	    size_t	off_len = 0;


	    msg_start();


	    if (!cmd_silent &&
		    (spats[0].off.line || spats[0].off.end || spats[0].off.off))
	    {
		p = off_buf;
		*p++ = dirc;
		if (spats[0].off.end)
		    *p++ = 'e';
		else if (!spats[0].off.line)
		    *p++ = 's';
		if (spats[0].off.off > 0 || spats[0].off.line)
		    *p++ = '+';
		*p = NUL;
		if (spats[0].off.off != 0 || spats[0].off.line)
		    sprintf((char *)p, "%ld", spats[0].off.off);
		off_len = STRLEN(off_buf);
	    }

	    if (*searchstr == NUL)
		p = spats[0].pat;
	    else
		p = searchstr;

	    if (!shortmess(SHM_SEARCHCOUNT) || cmd_silent)
	    {


		if (msg_scrolled != 0 && !cmd_silent)

		    len = (int)(Rows - msg_row) * Columns - 1;
		else

		    len = (int)(Rows - msg_row - 1) * Columns + sc_col - 1;
		if (len < STRLEN(p) + off_len + SEARCH_STAT_BUF_LEN + 3)
		    len = STRLEN(p) + off_len + SEARCH_STAT_BUF_LEN + 3;
	    }
	    else

		len = STRLEN(p) + off_len + 3;

	    vim_free(msgbuf);
	    msgbuf = alloc(len);
	    if (msgbuf != NULL)
	    {
		vim_memset(msgbuf, ' ', len);
		msgbuf[len - 1] = NUL;


		if (!cmd_silent)
		{
		    msgbuf[0] = dirc;

		    if (enc_utf8 && utf_iscomposing(utf_ptr2char(p)))
		    {

			msgbuf[1] = ' ';
			mch_memmove(msgbuf + 2, p, STRLEN(p));
		    }
		    else
			mch_memmove(msgbuf + 1, p, STRLEN(p));
		    if (off_len > 0)
			mch_memmove(msgbuf + STRLEN(p) + 1, off_buf, off_len);

		    trunc = msg_strtrunc(msgbuf, TRUE);
		    if (trunc != NULL)
		    {
			vim_free(msgbuf);
			msgbuf = trunc;
		    }

#ifdef FEAT_RIGHTLEFT


		    if (curwin->w_p_rl && *curwin->w_p_rlc == 's')
		    {
			char_u *r;
			size_t pat_len;

			r = reverse_text(msgbuf);
			if (r != NULL)
			{
			    vim_free(msgbuf);
			    msgbuf = r;

			    while (*r != NUL && *r == ' ')
				r++;
			    pat_len = msgbuf + STRLEN(msgbuf) - r;
			    mch_memmove(msgbuf, r, pat_len);

			    if ((size_t)(r - msgbuf) >= pat_len)
				vim_memset(r, ' ', pat_len);
			    else
				vim_memset(msgbuf + pat_len, ' ', r - msgbuf);
			}
		    }
#endif
		    msg_outtrans(msgbuf);
		    msg_clr_eos();
		    msg_check();

		    gotocmdline(FALSE);
		    out_flush();
		    msg_nowait = TRUE;
		}
	    }
	}


	if (!spats[0].off.line && spats[0].off.off && pos.col < MAXCOL - 2)
	{
	    if (spats[0].off.off > 0)
	    {
		for (c = spats[0].off.off; c; --c)
		    if (decl(&pos) == -1)
			break;
		if (c)
		{
		    pos.lnum = 0;
		    pos.col = MAXCOL;
		}
	    }
	    else
	    {
		for (c = spats[0].off.off; c; ++c)
		    if (incl(&pos) == -1)
			break;
		if (c)
		{
		    pos.lnum = curbuf->b_ml.ml_line_count + 1;
		    pos.col = 0;
		}
	    }
	}


	c = searchit(curwin, curbuf, &pos, NULL,
					      dirc == '/' ? FORWARD : BACKWARD,
		searchstr, count, spats[0].off.end + (options &
		       (SEARCH_KEEP + SEARCH_PEEK + SEARCH_HIS
			+ SEARCH_MSG + SEARCH_START
			+ ((pat != NULL && *pat == ';') ? 0 : SEARCH_NOOF))),
		RE_LAST, sia);

	if (dircp != NULL)
	    *dircp = search_delim;

	if (!shortmess(SHM_SEARCH)
		&& ((dirc == '/' && LT_POS(pos, curwin->w_cursor))
			    || (dirc == '?' && LT_POS(curwin->w_cursor, pos))))
	    show_top_bot_msg = TRUE;

	if (c == FAIL)
	{
	    retval = 0;
	    goto end_do_search;
	}
	if (spats[0].off.end && oap != NULL)
	    oap->inclusive = TRUE;

	retval = 1;


	if (!(options & SEARCH_NOOF) || (pat != NULL && *pat == ';'))
	{
	    pos_T org_pos = pos;

	    if (spats[0].off.line)
	    {
		c = pos.lnum + spats[0].off.off;
		if (c < 1)
		    pos.lnum = 1;
		else if (c > curbuf->b_ml.ml_line_count)
		    pos.lnum = curbuf->b_ml.ml_line_count;
		else
		    pos.lnum = c;
		pos.col = 0;

		retval = 2;
	    }
	    else if (pos.col < MAXCOL - 2)
	    {

		c = spats[0].off.off;
		if (c > 0)
		{
		    while (c-- > 0)
			if (incl(&pos) == -1)
			    break;
		}

		else
		{
		    while (c++ < 0)
			if (decl(&pos) == -1)
			    break;
		}
	    }
	    if (!EQUAL_POS(pos, org_pos))
		has_offset = TRUE;
	}


	if ((options & SEARCH_ECHO)
		&& messaging()
		&& !msg_silent
		&& c != FAIL
		&& !shortmess(SHM_SEARCHCOUNT)
		&& msgbuf != NULL)
	     cmdline_search_stat(dirc, &pos, &curwin->w_cursor,
				show_top_bot_msg, msgbuf,
				(count != 1 || has_offset
#ifdef FEAT_FOLDING
				 || (!(fdo_flags & FDO_SEARCH)
				     && hasFolding(curwin->w_cursor.lnum,
								   NULL, NULL))
#endif
				),
				SEARCH_STAT_DEF_MAX_COUNT,
				SEARCH_STAT_DEF_TIMEOUT);


	if (!(options & SEARCH_OPT) || pat == NULL || *pat != ';')
	    break;

	dirc = *++pat;
	search_delim = dirc;
	if (dirc != '?' && dirc != '/')
	{
	    retval = 0;
	    emsg(_(e_expected_question_or_slash_after_semicolon));
	    goto end_do_search;
	}
	++pat;
    }

    if (options & SEARCH_MARK)
	setpcmark();
    curwin->w_cursor = pos;
    curwin->w_set_curswant = TRUE;

end_do_search:
    if ((options & SEARCH_KEEP) || (cmdmod.cmod_flags & CMOD_KEEPPATTERNS))
	spats[0].off = old_off;
    vim_free(strcopy);
    vim_free(msgbuf);

    return retval;
}
