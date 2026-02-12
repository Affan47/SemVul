ex_sort(exarg_T *eap)
{
    regmatch_T	regmatch;
    int		len;
    linenr_T	lnum;
    long	maxlen = 0;
    sorti_T	*nrs;
    size_t	count = (size_t)(eap->line2 - eap->line1 + 1);
    size_t	i;
    char_u	*p;
    char_u	*s;
    char_u	*s2;
    char_u	c;
    int		unique = FALSE;
    long	deleted;
    colnr_T	start_col;
    colnr_T	end_col;
    int		sort_what = 0;
    int		format_found = 0;
    int		change_occurred = FALSE;


    if (count <= 1)
	return;

    if (u_save((linenr_T)(eap->line1 - 1), (linenr_T)(eap->line2 + 1)) == FAIL)
	return;
    sortbuf1 = NULL;
    sortbuf2 = NULL;
    regmatch.regprog = NULL;
    nrs = ALLOC_MULT(sorti_T, count);
    if (nrs == NULL)
	goto sortend;

    sort_abort = sort_ic = sort_lc = sort_rx = sort_nr = 0;
#ifdef FEAT_FLOAT
    sort_flt = 0;
#endif

    for (p = eap->arg; *p != NUL; ++p)
    {
	if (VIM_ISWHITE(*p))
	    ;
	else if (*p == 'i')
	    sort_ic = TRUE;
	else if (*p == 'l')
	    sort_lc = TRUE;
	else if (*p == 'r')
	    sort_rx = TRUE;
	else if (*p == 'n')
	{
	    sort_nr = 1;
	    ++format_found;
	}
#ifdef FEAT_FLOAT
	else if (*p == 'f')
	{
	    sort_flt = 1;
	    ++format_found;
	}
#endif
	else if (*p == 'b')
	{
	    sort_what = STR2NR_BIN + STR2NR_FORCE;
	    ++format_found;
	}
	else if (*p == 'o')
	{
	    sort_what = STR2NR_OCT + STR2NR_FORCE;
	    ++format_found;
	}
	else if (*p == 'x')
	{
	    sort_what = STR2NR_HEX + STR2NR_FORCE;
	    ++format_found;
	}
	else if (*p == 'u')
	    unique = TRUE;
	else if (*p == '"')
	    break;
	else if (eap->nextcmd == NULL && check_nextcmd(p) != NULL)
	{
	    eap->nextcmd = check_nextcmd(p);
	    break;
	}
	else if (!ASCII_ISALPHA(*p) && regmatch.regprog == NULL)
	{
	    s = skip_regexp_err(p + 1, *p, TRUE);
	    if (s == NULL)
		goto sortend;
	    *s = NUL;

	    if (s == p + 1)
	    {
		if (last_search_pat() == NULL)
		{
		    emsg(_(e_no_previous_regular_expression));
		    goto sortend;
		}
		regmatch.regprog = vim_regcomp(last_search_pat(), RE_MAGIC);
	    }
	    else
		regmatch.regprog = vim_regcomp(p + 1, RE_MAGIC);
	    if (regmatch.regprog == NULL)
		goto sortend;
	    p = s;
	    regmatch.rm_ic = p_ic;
	}
	else
	{
	    semsg(_(e_invalid_argument_str), p);
	    goto sortend;
	}
    }


    if (format_found > 1)
    {
	emsg(_(e_invalid_argument));
	goto sortend;
    }


    sort_nr += sort_what;


    for (lnum = eap->line1; lnum <= eap->line2; ++lnum)
    {
	s = ml_get(lnum);
	len = (int)STRLEN(s);
	if (maxlen < len)
	    maxlen = len;

	start_col = 0;
	end_col = len;
	if (regmatch.regprog != NULL && vim_regexec(&regmatch, s, 0))
	{
	    if (sort_rx)
	    {
		start_col = (colnr_T)(regmatch.startp[0] - s);
		end_col = (colnr_T)(regmatch.endp[0] - s);
	    }
	    else
		start_col = (colnr_T)(regmatch.endp[0] - s);
	}
	else
	    if (regmatch.regprog != NULL)
		end_col = 0;

	if (sort_nr
#ifdef FEAT_FLOAT
		|| sort_flt
#endif
		)
	{


	    s2 = s + end_col;
	    c = *s2;
	    *s2 = NUL;

	    p = s + start_col;
	    if (sort_nr)
	    {
		if (sort_what & STR2NR_HEX)
		    s = skiptohex(p);
		else if (sort_what & STR2NR_BIN)
		    s = skiptobin(p);
		else
		    s = skiptodigit(p);
		if (s > p && s[-1] == '-')
		    --s;
		if (*s == NUL)
		{

		    nrs[lnum - eap->line1].st_u.num.is_number = FALSE;
		    nrs[lnum - eap->line1].st_u.num.value = 0;
		}
		else
		{
		    nrs[lnum - eap->line1].st_u.num.is_number = TRUE;
		    vim_str2nr(s, NULL, NULL, sort_what,
			&nrs[lnum - eap->line1].st_u.num.value,
			NULL, 0, FALSE);
		}
	    }
#ifdef FEAT_FLOAT
	    else
	    {
		s = skipwhite(p);
		if (*s == '+')
		    s = skipwhite(s + 1);

		if (*s == NUL)

		    nrs[lnum - eap->line1].st_u.value_flt = -DBL_MAX;
		else
		    nrs[lnum - eap->line1].st_u.value_flt =
						      strtod((char *)s, NULL);
	    }
#endif
	    *s2 = c;
	}
	else
	{

	    nrs[lnum - eap->line1].st_u.line.start_col_nr = start_col;
	    nrs[lnum - eap->line1].st_u.line.end_col_nr = end_col;
	}

	nrs[lnum - eap->line1].lnum = lnum;

	if (regmatch.regprog != NULL)
	    fast_breakcheck();
	if (got_int)
	    goto sortend;
    }


    sortbuf1 = alloc(maxlen + 1);
    if (sortbuf1 == NULL)
	goto sortend;
    sortbuf2 = alloc(maxlen + 1);
    if (sortbuf2 == NULL)
	goto sortend;


    qsort((void *)nrs, count, sizeof(sorti_T), sort_compare);

    if (sort_abort)
	goto sortend;


    lnum = eap->line2;
    for (i = 0; i < count; ++i)
    {
	linenr_T get_lnum = nrs[eap->forceit ? count - i - 1 : i].lnum;


	if (get_lnum + ((linenr_T)count - 1) != lnum)
	    change_occurred = TRUE;

	s = ml_get(get_lnum);
	if (!unique || i == 0 || string_compare(s, sortbuf1) != 0)
	{


	    STRCPY(sortbuf1, s);
	    if (ml_append(lnum++, sortbuf1, (colnr_T)0, FALSE) == FAIL)
		break;
	}
	fast_breakcheck();
	if (got_int)
	    goto sortend;
    }


    if (i == count)
	for (i = 0; i < count; ++i)
	    ml_delete(eap->line1);
    else
	count = 0;


    deleted = (long)(count - (lnum - eap->line2));
    if (deleted > 0)
    {
	mark_adjust(eap->line2 - deleted, eap->line2, (long)MAXLNUM, -deleted);
	msgmore(-deleted);
    }
    else if (deleted < 0)
	mark_adjust(eap->line2, MAXLNUM, -deleted, 0L);

    if (change_occurred || deleted != 0)
	changed_lines(eap->line1, 0, eap->line2 + 1, -deleted);

    curwin->w_cursor.lnum = eap->line1;
    beginline(BL_WHITE | BL_FIX);

sortend:
    vim_free(nrs);
    vim_free(sortbuf1);
    vim_free(sortbuf2);
    vim_regfree(regmatch.regprog);
    if (got_int)
	emsg(_(e_interrupted));
}
