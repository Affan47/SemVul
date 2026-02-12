searchit(
    win_T	*win,

    buf_T	*buf,
    pos_T	*pos,
    pos_T	*end_pos,
    int		dir,
    char_u	*pat,
    long	count,
    int		options,
    int		pat_use,
    searchit_arg_T *extra_arg)
{
    int		found;
    linenr_T	lnum;
    colnr_T	col;
    regmmatch_T	regmatch;
    char_u	*ptr;
    colnr_T	matchcol;
    lpos_T	endpos;
    lpos_T	matchpos;
    int		loop;
    pos_T	start_pos;
    int		at_first_line;
    int		extra_col;
    int		start_char_len;
    int		match_ok;
    long	nmatched;
    int		submatch = 0;
    int		first_match = TRUE;
    int		called_emsg_before = called_emsg;
#ifdef FEAT_SEARCH_EXTRA
    int		break_loop = FALSE;
#endif
    linenr_T	stop_lnum = 0;
#ifdef FEAT_RELTIME
    proftime_T	*tm = NULL;
    int		*timed_out = NULL;
#endif

    if (extra_arg != NULL)
    {
	stop_lnum = extra_arg->sa_stop_lnum;
#ifdef FEAT_RELTIME
	tm = extra_arg->sa_tm;
	timed_out = &extra_arg->sa_timed_out;
#endif
    }

    if (search_regcomp(pat, RE_SEARCH, pat_use,
		   (options & (SEARCH_HIS + SEARCH_KEEP)), &regmatch) == FAIL)
    {
	if ((options & SEARCH_MSG) && !rc_did_emsg)
	    semsg(_(e_invalid_search_string_str), mr_pattern);
	return FAIL;
    }


    do
    {


	if (pos->col == MAXCOL)
	    start_char_len = 0;

	else if (has_mbyte
		    && pos->lnum >= 1 && pos->lnum <= buf->b_ml.ml_line_count
						    && pos->col < MAXCOL - 2)
	{
	    ptr = ml_get_buf(buf, pos->lnum, FALSE);
	    if ((int)STRLEN(ptr) <= pos->col)
		start_char_len = 1;
	    else
		start_char_len = (*mb_ptr2len)(ptr + pos->col);
	}
	else
	    start_char_len = 1;
	if (dir == FORWARD)
	{
	    if (options & SEARCH_START)
		extra_col = 0;
	    else
		extra_col = start_char_len;
	}
	else
	{
	    if (options & SEARCH_START)
		extra_col = start_char_len;
	    else
		extra_col = 0;
	}

	start_pos = *pos;
	found = 0;
	at_first_line = TRUE;
	if (pos->lnum == 0)
	{
	    pos->lnum = 1;
	    pos->col = 0;
	    at_first_line = FALSE;
	}


	if (dir == BACKWARD && start_pos.col == 0
					     && (options & SEARCH_START) == 0)
	{
	    lnum = pos->lnum - 1;
	    at_first_line = FALSE;
	}
	else
	    lnum = pos->lnum;

	for (loop = 0; loop <= 1; ++loop)
	{
	    for ( ; lnum > 0 && lnum <= buf->b_ml.ml_line_count;
					   lnum += dir, at_first_line = FALSE)
	    {

		if (stop_lnum != 0 && (dir == FORWARD
				       ? lnum > stop_lnum : lnum < stop_lnum))
		    break;
#ifdef FEAT_RELTIME

		if (tm != NULL && profile_passed_limit(tm))
		    break;
#endif


		col = at_first_line && (options & SEARCH_COL) ? pos->col
								 : (colnr_T)0;
		nmatched = vim_regexec_multi(&regmatch, win, buf,
					     lnum, col,
#ifdef FEAT_RELTIME
					     tm, timed_out
#else
					     NULL, NULL
#endif
						      );

		if (regmatch.regprog == NULL)
		    break;

		if (called_emsg > called_emsg_before
#ifdef FEAT_RELTIME
			|| (timed_out != NULL && *timed_out)
#endif
			)
		    break;
		if (nmatched > 0)
		{

		    matchpos = regmatch.startpos[0];
		    endpos = regmatch.endpos[0];
#ifdef FEAT_EVAL
		    submatch = first_submatch(&regmatch);
#endif

		    if (lnum + matchpos.lnum > buf->b_ml.ml_line_count)
			ptr = (char_u *)"";
		    else
			ptr = ml_get_buf(buf, lnum + matchpos.lnum, FALSE);


		    if (dir == FORWARD && at_first_line)
		    {
			match_ok = TRUE;


			while (matchpos.lnum == 0
				&& ((options & SEARCH_END) && first_match
				    ?  (nmatched == 1
					&& (int)endpos.col - 1
					     < (int)start_pos.col + extra_col)
				    : ((int)matchpos.col
						  - (ptr[matchpos.col] == NUL)
					    < (int)start_pos.col + extra_col)))
			{


			    if (vim_strchr(p_cpo, CPO_SEARCH) != NULL)
			    {
				if (nmatched > 1)
				{


				    match_ok = FALSE;
				    break;
				}
				matchcol = endpos.col;

				if (matchcol == matchpos.col
						      && ptr[matchcol] != NUL)
				{
				    if (has_mbyte)
					matchcol +=
					  (*mb_ptr2len)(ptr + matchcol);
				    else
					++matchcol;
				}
			    }
			    else
			    {
				matchcol = matchpos.col;
				if (ptr[matchcol] != NUL)
				{
				    if (has_mbyte)
					matchcol += (*mb_ptr2len)(ptr
								  + matchcol);
				    else
					++matchcol;
				}
			    }
			    if (matchcol == 0 && (options & SEARCH_START))
				break;
			    if (ptr[matchcol] == NUL
				    || (nmatched = vim_regexec_multi(&regmatch,
					      win, buf, lnum + matchpos.lnum,
					      matchcol,
#ifdef FEAT_RELTIME
					      tm, timed_out
#else
					      NULL, NULL
#endif
					      )) == 0)
			    {
				match_ok = FALSE;
				break;
			    }

			    if (regmatch.regprog == NULL)
				break;
			    matchpos = regmatch.startpos[0];
			    endpos = regmatch.endpos[0];
# ifdef FEAT_EVAL
			    submatch = first_submatch(&regmatch);
# endif


			    ptr = ml_get_buf(buf, lnum + matchpos.lnum, FALSE);
			}
			if (!match_ok)
			    continue;
		    }
		    if (dir == BACKWARD)
		    {


			match_ok = FALSE;
			for (;;)
			{


			    if (loop
				|| ((options & SEARCH_END)
				    ? (lnum + regmatch.endpos[0].lnum
							      < start_pos.lnum
					|| (lnum + regmatch.endpos[0].lnum
							     == start_pos.lnum
					     && (int)regmatch.endpos[0].col - 1
							< (int)start_pos.col
								+ extra_col))
				    : (lnum + regmatch.startpos[0].lnum
							      < start_pos.lnum
					|| (lnum + regmatch.startpos[0].lnum
							     == start_pos.lnum
					     && (int)regmatch.startpos[0].col
						      < (int)start_pos.col
							      + extra_col))))
			    {
				match_ok = TRUE;
				matchpos = regmatch.startpos[0];
				endpos = regmatch.endpos[0];
# ifdef FEAT_EVAL
				submatch = first_submatch(&regmatch);
# endif
			    }
			    else
				break;


			    if (vim_strchr(p_cpo, CPO_SEARCH) != NULL)
			    {
				if (nmatched > 1)
				    break;
				matchcol = endpos.col;

				if (matchcol == matchpos.col
						      && ptr[matchcol] != NUL)
				{
				    if (has_mbyte)
					matchcol +=
					  (*mb_ptr2len)(ptr + matchcol);
				    else
					++matchcol;
				}
			    }
			    else
			    {

				if (matchpos.lnum > 0)
				    break;
				matchcol = matchpos.col;
				if (ptr[matchcol] != NUL)
				{
				    if (has_mbyte)
					matchcol +=
					  (*mb_ptr2len)(ptr + matchcol);
				    else
					++matchcol;
				}
			    }
			    if (ptr[matchcol] == NUL
				    || (nmatched = vim_regexec_multi(&regmatch,
					      win, buf, lnum + matchpos.lnum,
					      matchcol,
#ifdef FEAT_RELTIME
					      tm, timed_out
#else
					      NULL, NULL
#endif
					    )) == 0)
			    {
#ifdef FEAT_RELTIME


				if (timed_out != NULL && *timed_out)
				    match_ok = FALSE;
#endif
				break;
			    }

			    if (regmatch.regprog == NULL)
				break;


			    ptr = ml_get_buf(buf, lnum + matchpos.lnum, FALSE);
			}


			if (!match_ok)
			    continue;
		    }


		    if ((options & SEARCH_END) && !(options & SEARCH_NOOF)
			    && !(matchpos.lnum == endpos.lnum
				&& matchpos.col == endpos.col))
		    {


			pos->lnum = lnum + endpos.lnum;
			pos->col = endpos.col;
			if (endpos.col == 0)
			{
			    if (pos->lnum > 1)
			    {
				--pos->lnum;
				pos->col = (colnr_T)STRLEN(ml_get_buf(buf,
							   pos->lnum, FALSE));
			    }
			}
			else
			{
			    --pos->col;
			    if (has_mbyte
				    && pos->lnum <= buf->b_ml.ml_line_count)
			    {
				ptr = ml_get_buf(buf, pos->lnum, FALSE);
				pos->col -= (*mb_head_off)(ptr, ptr + pos->col);
			    }
			}
			if (end_pos != NULL)
			{
			    end_pos->lnum = lnum + matchpos.lnum;
			    end_pos->col = matchpos.col;
			}
		    }
		    else
		    {
			pos->lnum = lnum + matchpos.lnum;
			pos->col = matchpos.col;
			if (end_pos != NULL)
			{
			    end_pos->lnum = lnum + endpos.lnum;
			    end_pos->col = endpos.col;
			}
		    }
		    pos->coladd = 0;
		    if (end_pos != NULL)
			end_pos->coladd = 0;
		    found = 1;
		    first_match = FALSE;


		    search_match_lines = endpos.lnum - matchpos.lnum;
		    search_match_endcol = endpos.col;
		    break;
		}
		line_breakcheck();
		if (got_int)
		    break;

#ifdef FEAT_SEARCH_EXTRA


		if ((options & SEARCH_PEEK)
			&& ((lnum - pos->lnum) & 0x3f) == 0
			&& char_avail())
		{
		    break_loop = TRUE;
		    break;
		}
#endif

		if (loop && lnum == start_pos.lnum)
		    break;
	    }
	    at_first_line = FALSE;


	    if (regmatch.regprog == NULL)
		break;


	    if (!p_ws || stop_lnum != 0 || got_int
					    || called_emsg > called_emsg_before
#ifdef FEAT_RELTIME
				|| (timed_out != NULL && *timed_out)
#endif
#ifdef FEAT_SEARCH_EXTRA
				|| break_loop
#endif
				|| found || loop)
		break;


	    if (dir == BACKWARD)
		lnum = buf->b_ml.ml_line_count;
	    else
		lnum = 1;
	    if (!shortmess(SHM_SEARCH) && (options & SEARCH_MSG))
		give_warning((char_u *)_(dir == BACKWARD
					  ? top_bot_msg : bot_top_msg), TRUE);
	    if (extra_arg != NULL)
		extra_arg->sa_wrapped = TRUE;
	}
	if (got_int || called_emsg > called_emsg_before
#ifdef FEAT_RELTIME
		|| (timed_out != NULL && *timed_out)
#endif
#ifdef FEAT_SEARCH_EXTRA
		|| break_loop
#endif
		)
	    break;
    }
    while (--count > 0 && found);

    vim_regfree(regmatch.regprog);

    if (!found)
    {
	if (got_int)
	    emsg(_(e_interrupted));
	else if ((options & SEARCH_MSG) == SEARCH_MSG)
	{
	    if (p_ws)
		semsg(_(e_pattern_not_found_str), mr_pattern);
	    else if (lnum == 0)
		semsg(_(e_search_hit_top_without_match_for_str), mr_pattern);
	    else
		semsg(_(e_search_hit_bottom_without_match_for_str), mr_pattern);
	}
	return FAIL;
    }


    if (pos->lnum > buf->b_ml.ml_line_count)
    {
	pos->lnum = buf->b_ml.ml_line_count;
	pos->col = (int)STRLEN(ml_get_buf(buf, pos->lnum, FALSE));
	if (pos->col > 0)
	    --pos->col;
    }

    return submatch + 1;
}
