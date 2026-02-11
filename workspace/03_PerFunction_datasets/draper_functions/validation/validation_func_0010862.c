pgstat_read_current_status(void)
{
	volatile PgBackendStatus *beentry;
	LocalPgBackendStatus *localtable;
	LocalPgBackendStatus *localentry;
	char	   *localappname,
			   *localactivity;
#ifdef USE_SSL
	PgBackendSSLStatus *localsslstatus;
#endif
	int			i;

	Assert(!pgStatRunningInCollector);
	if (localBackendStatusTable)
		return;

	pgstat_setup_memcxt();

	localtable = (LocalPgBackendStatus *)
		MemoryContextAlloc(pgStatLocalContext,
						   sizeof(LocalPgBackendStatus) * MaxBackends);
	localappname = (char *)
		MemoryContextAlloc(pgStatLocalContext,
						   NAMEDATALEN * MaxBackends);
	localactivity = (char *)
		MemoryContextAlloc(pgStatLocalContext,
						   pgstat_track_activity_query_size * MaxBackends);
#ifdef USE_SSL
	localsslstatus = (PgBackendSSLStatus *)
		MemoryContextAlloc(pgStatLocalContext,
						   sizeof(PgBackendSSLStatus) * MaxBackends);
#endif

	localNumBackends = 0;

	beentry = BackendStatusArray;
	localentry = localtable;
	for (i = 1; i <= MaxBackends; i++)
	{


		for (;;)
		{
			int			before_changecount;
			int			after_changecount;

			pgstat_save_changecount_before(beentry, before_changecount);

			localentry->backendStatus.st_procpid = beentry->st_procpid;
			if (localentry->backendStatus.st_procpid > 0)
			{
				memcpy(&localentry->backendStatus, (char *) beentry, sizeof(PgBackendStatus));


				strcpy(localappname, (char *) beentry->st_appname);
				localentry->backendStatus.st_appname = localappname;
				strcpy(localactivity, (char *) beentry->st_activity);
				localentry->backendStatus.st_activity = localactivity;
				localentry->backendStatus.st_ssl = beentry->st_ssl;
#ifdef USE_SSL
				if (beentry->st_ssl)
				{
					memcpy(localsslstatus, beentry->st_sslstatus, sizeof(PgBackendSSLStatus));
					localentry->backendStatus.st_sslstatus = localsslstatus;
				}
#endif
			}

			pgstat_save_changecount_after(beentry, after_changecount);
			if (before_changecount == after_changecount &&
				(before_changecount & 1) == 0)
				break;


			CHECK_FOR_INTERRUPTS();
		}

		beentry++;

		if (localentry->backendStatus.st_procpid > 0)
		{
			BackendIdGetTransactionIds(i,
									   &localentry->backend_xid,
									   &localentry->backend_xmin);

			localentry++;
			localappname += NAMEDATALEN;
			localactivity += pgstat_track_activity_query_size;
#ifdef USE_SSL
			localsslstatus++;
#endif
			localNumBackends++;
		}
	}


	localBackendStatusTable = localtable;
}
