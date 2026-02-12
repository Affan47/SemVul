spell_check(
    win_T	*wp,
    char_u	*ptr,
    hlf_T	*attrp,
    int		*capcol,
    int		docount)
{
    matchinf_T	mi;

    int		nrlen = 0;
    int		c;
    int		wrongcaplen = 0;
    int		lpi;
    int		count_word = docount;
    int		use_camel_case = *wp->w_s->b_p_spo != NUL;
    int		camel_case = 0;


    if (*ptr <= ' ')
	return 1;


    if (wp->w_s->b_langp.ga_len == 0)
	return 1;

    CLEAR_FIELD(mi);


    if (*ptr >= '0' && *ptr <= '9')
    {
	if (*ptr == '0' && (ptr[1] == 'b' || ptr[1] == 'B'))
	    mi.mi_end = skipbin(ptr + 2);
	else if (*ptr == '0' && (ptr[1] == 'x' || ptr[1] == 'X'))
	    mi.mi_end = skiphex(ptr + 2);
	else
	    mi.mi_end = skipdigits(ptr);
	nrlen = (int)(mi.mi_end - ptr);
    }


    mi.mi_word = ptr;
    mi.mi_fend = ptr;
    if (spell_iswordp(mi.mi_fend, wp))
    {
	int prev_upper;
	int this_upper = FALSE;

	if (use_camel_case)
	{
	    c = PTR2CHAR(mi.mi_fend);
	    this_upper = SPELL_ISUPPER(c);
	}

	do
	{
	    MB_PTR_ADV(mi.mi_fend);
	    if (use_camel_case)
	    {
		prev_upper = this_upper;
		c = PTR2CHAR(mi.mi_fend);
		this_upper = SPELL_ISUPPER(c);
		camel_case = !prev_upper && this_upper;
	    }
	} while (*mi.mi_fend != NUL && spell_iswordp(mi.mi_fend, wp)
							       && !camel_case);

	if (capcol != NULL && *capcol == 0 && wp->w_s->b_cap_prog != NULL)
	{

	    c = PTR2CHAR(ptr);
	    if (!SPELL_ISUPPER(c))
		wrongcaplen = (int)(mi.mi_fend - ptr);
	}
    }
    if (capcol != NULL)
	*capcol = -1;


    mi.mi_end = mi.mi_fend;


    mi.mi_capflags = 0;
    mi.mi_cend = NULL;
    mi.mi_win = wp;


    if (*mi.mi_fend != NUL)
	MB_PTR_ADV(mi.mi_fend);

    (void)spell_casefold(wp, ptr, (int)(mi.mi_fend - ptr), mi.mi_fword,
							     MAXWLEN + 1);
    mi.mi_fwordlen = (int)STRLEN(mi.mi_fword);

    if (camel_case && mi.mi_fwordlen > 0)

	mi.mi_fword[mi.mi_fwordlen - 1] = ' ';


    mi.mi_result = SP_BAD;
    mi.mi_result2 = SP_BAD;


    for (lpi = 0; lpi < wp->w_s->b_langp.ga_len; ++lpi)
    {
	mi.mi_lp = LANGP_ENTRY(wp->w_s->b_langp, lpi);


	if (mi.mi_lp->lp_slang->sl_fidxs == NULL)
	    continue;


	find_word(&mi, FIND_FOLDWORD);


	find_word(&mi, FIND_KEEPWORD);


	find_prefix(&mi, FIND_FOLDWORD);


	if (mi.mi_lp->lp_slang->sl_nobreak && mi.mi_result == SP_BAD
						   && mi.mi_result2 != SP_BAD)
	{
	    mi.mi_result = mi.mi_result2;
	    mi.mi_end = mi.mi_end2;
	}


	if (count_word && mi.mi_result == SP_OK)
	{
	    count_common_word(mi.mi_lp->lp_slang, ptr,
						   (int)(mi.mi_end - ptr), 1);
	    count_word = FALSE;
	}
    }

    if (mi.mi_result != SP_OK)
    {


	if (nrlen > 0)
	{
	    if (mi.mi_result == SP_BAD || mi.mi_result == SP_BANNED)
		return nrlen;
	}


	else if (!spell_iswordp_nmw(ptr, wp))
	{
	    if (capcol != NULL && wp->w_s->b_cap_prog != NULL)
	    {
		regmatch_T	regmatch;
		int		r;


		regmatch.regprog = wp->w_s->b_cap_prog;
		regmatch.rm_ic = FALSE;
		r = vim_regexec(&regmatch, ptr, 0);
		wp->w_s->b_cap_prog = regmatch.regprog;
		if (r)
		    *capcol = (int)(regmatch.endp[0] - ptr);
	    }

	    if (has_mbyte)
		return (*mb_ptr2len)(ptr);
	    return 1;
	}
	else if (mi.mi_end == ptr)


	    MB_PTR_ADV(mi.mi_end);
	else if (mi.mi_result == SP_BAD
		&& LANGP_ENTRY(wp->w_s->b_langp, 0)->lp_slang->sl_nobreak)
	{
	    char_u	*p, *fp;
	    int		save_result = mi.mi_result;


	    mi.mi_lp = LANGP_ENTRY(wp->w_s->b_langp, 0);
	    if (mi.mi_lp->lp_slang->sl_fidxs != NULL)
	    {
		p = mi.mi_word;
		fp = mi.mi_fword;
		for (;;)
		{
		    MB_PTR_ADV(p);
		    MB_PTR_ADV(fp);
		    if (p >= mi.mi_end)
			break;
		    mi.mi_compoff = (int)(fp - mi.mi_fword);
		    find_word(&mi, FIND_COMPOUND);
		    if (mi.mi_result != SP_BAD)
		    {
			mi.mi_end = p;
			break;
		    }
		}
		mi.mi_result = save_result;
	    }
	}

	if (mi.mi_result == SP_BAD || mi.mi_result == SP_BANNED)
	    *attrp = HLF_SPB;
	else if (mi.mi_result == SP_RARE)
	    *attrp = HLF_SPR;
	else
	    *attrp = HLF_SPL;
    }

    if (wrongcaplen > 0 && (mi.mi_result == SP_OK || mi.mi_result == SP_RARE))
    {

	*attrp = HLF_SPC;
	return wrongcaplen;
    }

    return (int)(mi.mi_end - ptr);
}
