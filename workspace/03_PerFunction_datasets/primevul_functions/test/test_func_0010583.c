suggest_try_soundalike_prep(void)
{
    langp_T	*lp;
    int		lpi;
    slang_T	*slang;


    for (lpi = 0; lpi < curwin->w_s->b_langp.ga_len; ++lpi)
    {
	lp = LANGP_ENTRY(curwin->w_s->b_langp, lpi);
	slang = lp->lp_slang;
	if (slang->sl_sal.ga_len > 0 && slang->sl_sbyts != NULL)

	    hash_init(&slang->sl_sounddone);
    }
}
