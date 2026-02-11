do_cmd_open_chest(int y, int x, s16b o_idx)
{
	int i, j;

	bool flag = TRUE;

	bool more = FALSE;

	object_type *o_ptr = object_byid(o_idx);


	if (o_ptr->pval[DEFAULT_PVAL] > 0)
	{

		flag = FALSE;


		i = p_ptr->state.skills[SKILL_DISARM];


		if (p_ptr->timed[TMD_BLIND] || no_light()) i = i / 10;
		if (p_ptr->timed[TMD_CONFUSED] || p_ptr->timed[TMD_IMAGE]) i = i / 10;


		j = i - o_ptr->pval[DEFAULT_PVAL];


		if (j < 2) j = 2;


		if (randint0(100) < j)
		{
			msgt(MSG_LOCKPICK, "You have picked the lock.");
			player_exp_gain(p_ptr, 1);
			flag = TRUE;
		}


		else
		{

			more = TRUE;
			flush();
			msgt(MSG_LOCKPICK_FAIL, "You failed to pick the lock.");
		}
	}


	if (flag)
	{

		chest_trap(y, x, o_idx);


		chest_death(y, x, o_idx);


		p_ptr->notice |= PN_SQUELCH;


		cave_light_spot(cave, y, x);
	}


	return (more);
}
