msg_channel_flags(int p_or_n, const char *command, struct Client *client_p,
		  struct Client *source_p, struct Channel *chptr, int flags, const char *text)
{
	int type;
	char c;

	if(flags & CHFL_VOICE)
	{
		type = ONLY_CHANOPSVOICED;
		c = '+';
	}
	else
	{
		type = ONLY_CHANOPS;
		c = '@';
	}

	if(MyClient(source_p))
	{

		if(p_or_n != NOTICE)
			source_p->localClient->last = rb_current_time();
	}

	sendto_channel_flags(client_p, type, source_p, chptr, "%s %c%s :%s",
			     command, c, chptr->chname, text);
}
