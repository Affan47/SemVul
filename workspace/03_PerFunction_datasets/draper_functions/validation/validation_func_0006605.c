chm_voice(struct Client *source_p, struct Channel *chptr,
	  int alevel, int parc, int *parn,
	  const char **parv, int *errors, int dir, char c, long mode_type)
{
	struct membership *mstptr;
	const char *opnick;
	struct Client *targ_p;

	if(alevel != CHFL_CHANOP)
	{
		if(!(*errors & SM_ERR_NOOPS))
			sendto_one(source_p, form_str(ERR_CHANOPRIVSNEEDED),
				   me.name, source_p->name, chptr->chname);
		*errors |= SM_ERR_NOOPS;
		return;
	}

	if((dir == MODE_QUERY) || parc <= *parn)
		return;

	opnick = parv[(*parn)];
	(*parn)++;


	if(EmptyString(opnick))
	{
		sendto_one_numeric(source_p, ERR_NOSUCHNICK, form_str(ERR_NOSUCHNICK), "*");
		return;
	}

	if((targ_p = find_chasing(source_p, opnick, NULL)) == NULL)
	{
		return;
	}

	mstptr = find_channel_membership(chptr, targ_p);

	if(mstptr == NULL)
	{
		if(!(*errors & SM_ERR_NOTONCHANNEL) && MyClient(source_p))
			sendto_one_numeric(source_p, ERR_USERNOTINCHANNEL,
					   form_str(ERR_USERNOTINCHANNEL), opnick, chptr->chname);
		*errors |= SM_ERR_NOTONCHANNEL;
		return;
	}

	if(MyClient(source_p) && (++mode_limit > MAXMODEPARAMS))
		return;

	if(dir == MODE_ADD)
	{
		mode_changes[mode_count].letter = c;
		mode_changes[mode_count].dir = MODE_ADD;
		mode_changes[mode_count].caps = 0;
		mode_changes[mode_count].nocaps = 0;
		mode_changes[mode_count].mems = ALL_MEMBERS;
		mode_changes[mode_count].id = targ_p->id;
		mode_changes[mode_count].arg = targ_p->name;
		mode_changes[mode_count++].client = targ_p;

		mstptr->flags |= CHFL_VOICE;
	}
	else
	{
		mode_changes[mode_count].letter = 'v';
		mode_changes[mode_count].dir = MODE_DEL;
		mode_changes[mode_count].caps = 0;
		mode_changes[mode_count].nocaps = 0;
		mode_changes[mode_count].mems = ALL_MEMBERS;
		mode_changes[mode_count].id = targ_p->id;
		mode_changes[mode_count].arg = targ_p->name;
		mode_changes[mode_count++].client = targ_p;

		mstptr->flags &= ~CHFL_VOICE;
	}
}
