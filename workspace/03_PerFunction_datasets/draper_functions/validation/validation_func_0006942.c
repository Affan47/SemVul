ss_refresh(struct Luser *lptr, int ac, char **av)

{
	if (!LagDetect)
	{
		notice(n_StatServ, lptr->nick,
		       "Lag Detection is disabled");
		return;
	}

	RecordCommand("%s: %s!%s@%s REFRESH",
	              n_StatServ,
	              lptr->nick,
	              lptr->username,
	              lptr->hostname);

	notice(n_StatServ, lptr->nick,
	       "Updating server lag information");

	DoPings();
}
