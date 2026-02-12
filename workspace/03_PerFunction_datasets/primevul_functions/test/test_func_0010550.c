suggest_try_change(suginfo_T *su)
{
    char_u	fword[MAXWLEN];
    int		n;
    char_u	*p;
    int		lpi;
    langp_T	*lp;


    STRCPY(fword, su->su_fbadword);
    n = (int)STRLEN(fword);
    p = su->su_badptr + su->su_badlen;
    (void)spell_casefold(curwin, p, (int)STRLEN(p), fword + n, MAXWLEN - n);


    n = (int)STRLEN(su->su_badptr);
    if (n < MAXWLEN)
	fword[n] = NUL;

    for (lpi = 0; lpi < curwin->w_s->b_langp.ga_len; ++lpi)
    {
	lp = LANGP_ENTRY(curwin->w_s->b_langp, lpi);


	if (lp->lp_slang->sl_fbyts == NULL)
	    continue;


#ifdef SUGGEST_PROFILE
	prof_init();
#endif
	suggest_trie_walk(su, lp, fword, FALSE);
#ifdef SUGGEST_PROFILE
	prof_report("try_change");
#endif
    }
}
