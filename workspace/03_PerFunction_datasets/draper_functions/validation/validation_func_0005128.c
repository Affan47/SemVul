gotprivate()


{
	chanrec *chan;
	userrec *u = NULL;
	acctrec *a = NULL;
	membrec *m;

	context;

	rmspace(Server->msg);


	strcpy(Server->sbuf,Server->msg);

	context;

	for(chan=Channel->channels; chan!=NULL; chan=chan->next)
	{
		m = Channel_member(chan,Server->from_n);
		if(m != NULL)
		{

			u = m->user;
			a = m->account;
		}
	}

	context;
	if(u == NULL)
	{

		u = User_user(Server->from_n);
		a = User_account(u,Server->from_n,Server->from_uh);
	}

	context;

	User_gotactivity(u,a);

	context;

	User_gotpossiblesignon(u,a);

	context;

	strcpy(cmdinfo.from_n,Server->from_n);
	strcpy(cmdinfo.from_u,Server->from_u);
	strcpy(cmdinfo.from_uh,Server->from_uh);
	strcpy(cmdinfo.from_h,Server->from_h);
	strcpy(cmdinfo.buf,Server->msg);

	context;

	cmdinfo.d = NULL;


	cmdinfo.user = u;
	cmdinfo.account = a;

	if((strlen(Server->sbuf) >= 4) && strncasecmp(Server->sbuf,"pass",4) == 0)
		Log_write(LOG_CMD,"*","%s %s - <sent password>",Server->from_n,Server->from_uh);
	else
		Log_write(LOG_CMD,"*","%s %s - \"%s\"",Server->from_n,Server->from_uh,Server->sbuf);

	context;

	command_do();
}
