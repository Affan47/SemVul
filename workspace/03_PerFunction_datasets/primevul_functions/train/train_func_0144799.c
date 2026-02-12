vim_regexec_multi(
    regmmatch_T *rmp,
    win_T       *win,
    buf_T       *buf,
    linenr_T	lnum,
    colnr_T	col,
    int		*timed_out)
{
    int		result;
    regexec_T	rex_save;
    int		rex_in_use_save = rex_in_use;


    if (rmp->regprog->re_in_use)
    {
	emsg(_(e_cannot_use_pattern_recursively));
	return FALSE;
    }
    rmp->regprog->re_in_use = TRUE;

    if (rex_in_use)

	rex_save = rex;
    rex_in_use = TRUE;

    result = rmp->regprog->engine->regexec_multi(
				      rmp, win, buf, lnum, col, timed_out);
    rmp->regprog->re_in_use = FALSE;


    if (rmp->regprog->re_engine == AUTOMATIC_ENGINE
					       && result == NFA_TOO_EXPENSIVE)
    {
	int    save_p_re = p_re;
	int    re_flags = rmp->regprog->re_flags;
	char_u *pat = vim_strsave(((nfa_regprog_T *)rmp->regprog)->pattern);

	p_re = BACKTRACKING_ENGINE;
	if (pat != NULL)
	{
	    regprog_T *prev_prog = rmp->regprog;

#ifdef FEAT_EVAL
	    report_re_switch(pat);
#endif
#ifdef FEAT_SYN_HL


	    reg_do_extmatch = REX_ALL;
#endif
	    rmp->regprog = vim_regcomp(pat, re_flags);
#ifdef FEAT_SYN_HL
	    reg_do_extmatch = 0;
#endif
	    if (rmp->regprog == NULL)
	    {


		rmp->regprog = prev_prog;
	    }
	    else
	    {
		vim_regfree(prev_prog);

		rmp->regprog->re_in_use = TRUE;
		result = rmp->regprog->engine->regexec_multi(
				      rmp, win, buf, lnum, col, timed_out);
		rmp->regprog->re_in_use = FALSE;
	    }
	    vim_free(pat);
	}
	p_re = save_p_re;
    }

    rex_in_use = rex_in_use_save;
    if (rex_in_use)
	rex = rex_save;

    return result <= 0 ? 0 : result;
}
