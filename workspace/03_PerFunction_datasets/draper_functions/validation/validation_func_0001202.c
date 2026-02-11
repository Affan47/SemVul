chm_throttle(struct Client *source_p, struct Channel *chptr,
	     int alevel, int parc, int *parn,
	     const char **parv, int *errors, int dir, char c, long mode_type)
{
	int joins = 0, timeslice = 0;

	if(!allow_mode_change(source_p, chptr, alevel, errors, c))
		return;

	if(dir == MODE_QUERY)
		return;

	if(MyClient(source_p) && (++mode_limit_simple > MAXMODES_SIMPLE))
		return;

	if((dir == MODE_ADD) && parc > *parn)
	{
		sscanf(parv[(*parn)], "%d:%d", &joins, &timeslice);

		if(!joins || !timeslice)
			return;

		mode_changes[mode_count].letter = c;
		mode_changes[mode_count].dir = MODE_ADD;
		mode_changes[mode_count].caps = 0;
		mode_changes[mode_count].nocaps = 0;
		mode_changes[mode_count].mems = ALL_MEMBERS;
		mode_changes[mode_count].id = NULL;
		mode_changes[mode_count++].arg = parv[(*parn)];

		(*parn)++;

		chptr->mode.join_num = joins;
		chptr->mode.join_time = timeslice;
	}
	else if(dir == MODE_DEL)
	{
		if(!chptr->mode.join_num)
			return;

		chptr->mode.join_num = 0;
		chptr->mode.join_time = 0;
		chptr->join_count = 0;
		chptr->join_delta = 0;

		mode_changes[mode_count].letter = c;
		mode_changes[mode_count].dir = MODE_DEL;
		mode_changes[mode_count].caps = 0;
		mode_changes[mode_count].nocaps = 0;
		mode_changes[mode_count].mems = ALL_MEMBERS;
		mode_changes[mode_count].id = NULL;
		mode_changes[mode_count++].arg = NULL;
	}
}
