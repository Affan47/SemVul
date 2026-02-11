get_or_create_channel(struct Client *client_p, const char *chname, int *isnew)
{
	struct Channel *chptr;
	rb_dlink_node *ptr;
	unsigned int hashv;
	int len;
	const char *s = chname;

	if(EmptyString(s))
		return NULL;

	len = strlen(s);
	if(len > CHANNELLEN)
	{
		if(IsServer(client_p))
		{
			sendto_realops_flags(UMODE_DEBUG, L_ALL,
					     "*** Long channel name from %s (%d > %d): %s",
					     client_p->name, len, CHANNELLEN, s);
		}
		len = CHANNELLEN;
		s = LOCAL_COPY_N(s, CHANNELLEN);
	}

	hashv = hash_channel(s);

	RB_DLINK_FOREACH(ptr, channelTable[hashv].head)
	{
		chptr = ptr->data;

		if(irccmp(s, chptr->chname) == 0)
		{
			if(isnew != NULL)
				*isnew = 0;
			return chptr;
		}
	}

	if(isnew != NULL)
		*isnew = 1;

	chptr = allocate_channel(s);

	rb_dlinkAdd(chptr, &chptr->node, &global_channel_list);

	chptr->channelts = rb_current_time();

	rb_dlinkAddAlloc(chptr, &channelTable[hashv]);

	return chptr;
}
