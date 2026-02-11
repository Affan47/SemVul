spell_cast(int spell, int dir)
{
	int chance;


	const magic_type *s_ptr = &p_ptr->class->spells.info[spell];


	chance = spell_chance(spell);


	if (randint0(100) < chance)
	{
		flush();
		msg("You failed to concentrate hard enough!");
	}


	else
	{

		if (!cast_spell(p_ptr->class->spell_book, spell, dir)) return FALSE;


		sound(MSG_SPELL);

		if (!(p_ptr->spell_flags[spell] & PY_SPELL_WORKED))
		{
			int e = s_ptr->sexp;


			p_ptr->spell_flags[spell] |= PY_SPELL_WORKED;


			player_exp_gain(p_ptr, e * s_ptr->slevel);


			p_ptr->redraw |= (PR_OBJECT);
		}
	}


	if (s_ptr->smana <= p_ptr->csp)
	{

		p_ptr->csp -= s_ptr->smana;
	}


	else
	{
		int oops = s_ptr->smana - p_ptr->csp;


		p_ptr->csp = 0;
		p_ptr->csp_frac = 0;


		msg("You faint from the effort!");


		(void)player_inc_timed(p_ptr, TMD_PARALYZED, randint1(5 * oops + 1), TRUE, FALSE);


		if (randint0(100) < 50)
		{
			bool perm = (randint0(100) < 25);


			msg("You have damaged your health!");


			player_stat_dec(p_ptr, A_CON, perm);
		}
	}


	p_ptr->redraw |= (PR_MANA);

	return TRUE;
}
