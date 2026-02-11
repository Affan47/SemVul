do_cmd_disarm_chest(int y, int x, s16b o_idx)
{
	int i, j;

	bool more = FALSE;

	object_type *o_ptr = object_byid(o_idx);


	i = p_ptr->state.skills[SKILL_DISARM];


	if (p_ptr->timed[TMD_BLIND] || no_light()) i = i / 10;
	if (p_ptr->timed[TMD_CONFUSED] || p_ptr->timed[TMD_IMAGE]) i = i / 10;


	j = i - o_ptr->pval[DEFAULT_PVAL];


	if (j < 2) j = 2;


	if (!object_is_known(o_ptr))
	{
		msg("I don't see any traps.");
	}


	else if (o_ptr->pval[DEFAULT_PVAL] <= 0)
	{
		msg("The chest is not trapped.");
	}


	else if (!chest_traps[o_ptr->pval[DEFAULT_PVAL]])
	{
		msg("The chest is not trapped.");
	}


	else if (randint0(100) < j)
	{
		msgt(MSG_DISARM, "You have disarmed the chest.");
		player_exp_gain(p_ptr, o_ptr->pval[DEFAULT_PVAL]);
		o_ptr->pval[DEFAULT_PVAL] = (0 - o_ptr->pval[DEFAULT_PVAL]);
	}


	else if ((i > 5) && (randint1(i) > 5))
	{

		more = TRUE;
		flush();
		msg("You failed to disarm the chest.");
	}


	else
	{
		msg("You set off a trap!");
		chest_trap(y, x, o_idx);
	}


	return (more);
}
