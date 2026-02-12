eval_soundfold(char_u *word)
{
    langp_T	*lp;
    char_u	sound[MAXWLEN];
    int		lpi;

    if (curwin->w_p_spell && *curwin->w_s->b_p_spl != NUL)

	for (lpi = 0; lpi < curwin->w_s->b_langp.ga_len; ++lpi)
	{
	    lp = LANGP_ENTRY(curwin->w_s->b_langp, lpi);
	    if (lp->lp_slang->sl_sal.ga_len > 0)
	    {

		spell_soundfold(lp->lp_slang, word, FALSE, sound);
		return vim_strsave(sound);
	    }
	}


    return vim_strsave(word);
}
