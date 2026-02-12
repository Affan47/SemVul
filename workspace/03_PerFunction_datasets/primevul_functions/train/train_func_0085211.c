ServerLoop(void)
{
	fd_set		readmask;
	int			nSockets;
	time_t		last_lockfile_recheck_time,
				last_touch_time;

	last_lockfile_recheck_time = last_touch_time = time(NULL);

	nSockets = initMasks(&readmask);

	for (;;)
	{
		fd_set		rmask;
		int			selres;
		time_t		now;


		memcpy((char *) &rmask, (char *) &readmask, sizeof(fd_set));

		if (pmState == PM_WAIT_DEAD_END)
		{
			PG_SETMASK(&UnBlockSig);

			pg_usleep(100000L);
			selres = 0;

			PG_SETMASK(&BlockSig);
		}
		else
		{

			struct timeval timeout;


			DetermineSleepTime(&timeout);

			PG_SETMASK(&UnBlockSig);

			selres = select(nSockets, &rmask, NULL, NULL, &timeout);

			PG_SETMASK(&BlockSig);
		}


		if (selres < 0)
		{
			if (errno != EINTR && errno != EWOULDBLOCK)
			{
				ereport(LOG,
						(errcode_for_socket_access(),
						 errmsg("select() failed in postmaster: %m")));
				return STATUS_ERROR;
			}
		}


		if (selres > 0)
		{
			int			i;

			for (i = 0; i < MAXLISTEN; i++)
			{
				if (ListenSocket[i] == PGINVALID_SOCKET)
					break;
				if (FD_ISSET(ListenSocket[i], &rmask))
				{
					Port	   *port;

					port = ConnCreate(ListenSocket[i]);
					if (port)
					{
						BackendStartup(port);


						StreamClose(port->sock);
						ConnFree(port);
					}
				}
			}
		}


		if (SysLoggerPID == 0 && Logging_collector)
			SysLoggerPID = SysLogger_Start();


		if (pmState == PM_RUN || pmState == PM_RECOVERY ||
			pmState == PM_HOT_STANDBY || pmState == PM_STARTUP)
		{
			if (CheckpointerPID == 0)
				CheckpointerPID = StartCheckpointer();
			if (BgWriterPID == 0)
				BgWriterPID = StartBackgroundWriter();
		}


		if (WalWriterPID == 0 && pmState == PM_RUN)
			WalWriterPID = StartWalWriter();


		if (!IsBinaryUpgrade && AutoVacPID == 0 &&
			(AutoVacuumingActive() || start_autovac_launcher) &&
			pmState == PM_RUN)
		{
			AutoVacPID = StartAutoVacLauncher();
			if (AutoVacPID != 0)
				start_autovac_launcher = false;
		}


		if (PgStatPID == 0 &&
			(pmState == PM_RUN || pmState == PM_HOT_STANDBY))
			PgStatPID = pgstat_start();


		if (PgArchPID == 0 && PgArchStartupAllowed())
			PgArchPID = StartArchiver();


		if (avlauncher_needs_signal)
		{
			avlauncher_needs_signal = false;
			if (AutoVacPID != 0)
				kill(AutoVacPID, SIGUSR2);
		}


		if (WalReceiverRequested)
			MaybeStartWalReceiver();


		if (StartWorkerNeeded || HaveCrashedWorker)
			maybe_start_bgworkers();

#ifdef HAVE_PTHREAD_IS_THREADED_NP


		Assert(pthread_is_threaded_np() == 0);
#endif


		now = time(NULL);


		if ((Shutdown >= ImmediateShutdown || (FatalError && !SendStop)) &&
			AbortStartTime != 0 &&
			(now - AbortStartTime) >= SIGKILL_CHILDREN_AFTER_SECS)
		{

			ereport(LOG,
					(errmsg("issuing SIGKILL to recalcitrant children")));
			TerminateChildren(SIGKILL);

			AbortStartTime = 0;
		}


		if (now - last_lockfile_recheck_time >= 1 * SECS_PER_MINUTE)
		{
			if (!RecheckDataDirLockFile())
			{
				ereport(LOG,
						(errmsg("performing immediate shutdown because data directory lock file is invalid")));
				kill(MyProcPid, SIGQUIT);
			}
			last_lockfile_recheck_time = now;
		}


		if (now - last_touch_time >= 58 * SECS_PER_MINUTE)
		{
			TouchSocketFiles();
			TouchSocketLockFiles();
			last_touch_time = now;
		}
	}
}
