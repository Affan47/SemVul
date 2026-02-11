Banlist_writebans()


{
	FILE	*f;
	banlrec	*b;
	int	x;
	char	banlist[256], tmpfile[256];


	if(!(Banlist->flags & BANLIST_ACTIVE))
	{
		Log_write(LOG_MAIN,"*","Banlist list is not active.  Ignoring write request.");
		return;
	}


	sprintf(banlist,"%s/%s",Grufti->botdir,Grufti->banlist);
	sprintf(tmpfile,"%s.tmp",banlist);
	f = fopen(tmpfile,"w");
	if(f == NULL)
	{
		Log_write(LOG_MAIN|LOG_ERROR,"*","Couldn't write banlist.");
		return;
	}


	writeheader(f,"Banlist->banlist - The shitlist",banlist);


	for(b=Banlist->banlist; b!=NULL; b=b->next)
	{

		if(fprintf(f,"n %s\n",b->nick) == EOF)
			return;


		if(fprintf(f,"b %s\n",b->ban) == EOF)
			return;


		if(fprintf(f,"t %lu\n",(u_long)b->time_set) == EOF)
			return;


		if(fprintf(f,"e %lu\n",(u_long)b->expires) == EOF)
			return;


		if(fprintf(f,"u %d\n",b->used) == EOF)
			return;
	}

	fclose(f);


	if(Grufti->keep_tmpfiles)
		x = copyfile(tmpfile,banlist);
	else
		x = movefile(tmpfile,banlist);

	verify_write(x,tmpfile,banlist);
	if(x == 0)
	{
		Log_write(LOG_MAIN,"*","Wrote banlist.");
		Banlist->flags &= ~BANLIST_NEEDS_WRITE;
	}
}
