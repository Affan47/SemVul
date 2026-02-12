spell_reload(void)
{
    win_T	*wp;


    init_spell_chartab();


    spell_free_all();


    FOR_ALL_WINDOWS(wp)
    {


	if (*wp->w_s->b_p_spl != NUL)
	{
		if (wp->w_p_spell)
		{
		    (void)did_set_spelllang(wp);
		    break;
		}
	}
    }
}
