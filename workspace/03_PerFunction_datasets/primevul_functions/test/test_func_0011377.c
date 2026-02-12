vgr_init_regmatch(regmmatch_T *regmatch, char_u *s)
{

    regmatch->regprog = NULL;

    if (s == NULL || *s == NUL)
    {

	if (last_search_pat() == NULL)
	{
	    emsg(_(e_no_previous_regular_expression));
	    return;
	}
	regmatch->regprog = vim_regcomp(last_search_pat(), RE_MAGIC);
    }
    else
	regmatch->regprog = vim_regcomp(s, RE_MAGIC);

    regmatch->rmm_ic = p_ic;
    regmatch->rmm_maxcol = 0;
}
