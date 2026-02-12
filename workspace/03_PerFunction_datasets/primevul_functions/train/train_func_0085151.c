reaper(SIGNAL_ARGS)
{
	int			save_errno = errno;
	int			pid;
	int			exitstatus;


#ifdef WIN32
	PG_SETMASK(&BlockSig);
#endif

	ereport(DEBUG4,
			(errmsg_internal("reaping dead processes")));

	while ((pid = waitpid(-1, &exitstatus, WNOHANG)) > 0)
	{


		if (pid == StartupPID)
		{
			StartupPID = 0;


			if (Shutdown > NoShutdown &&
				(EXIT_STATUS_0(exitstatus) || EXIT_STATUS_1(exitstatus)))
			{
				StartupStatus = STARTUP_NOT_RUNNING;
				pmState = PM_WAIT_BACKENDS;

				continue;
			}

			if (EXIT_STATUS_3(exitstatus))
			{
				ereport(LOG,
						(errmsg("shutdown at recovery target")));
				StartupStatus = STARTUP_NOT_RUNNING;
				Shutdown = Max(Shutdown, SmartShutdown);
				TerminateChildren(SIGTERM);
				pmState = PM_WAIT_BACKENDS;

				continue;
			}


			if (pmState == PM_STARTUP &&
				StartupStatus != STARTUP_SIGNALED &&
				!EXIT_STATUS_0(exitstatus))
			{
				LogChildExit(LOG, _("startup process"),
							 pid, exitstatus);
				ereport(LOG,
						(errmsg("aborting startup due to startup process failure")));
				ExitPostmaster(1);
			}


			if (!EXIT_STATUS_0(exitstatus))
			{
				if (StartupStatus == STARTUP_SIGNALED)
				{
					StartupStatus = STARTUP_NOT_RUNNING;
					if (pmState == PM_STARTUP)
						pmState = PM_WAIT_BACKENDS;
				}
				else
					StartupStatus = STARTUP_CRASHED;
				HandleChildCrash(pid, exitstatus,
								 _("startup process"));
				continue;
			}


			StartupStatus = STARTUP_NOT_RUNNING;
			FatalError = false;
			AbortStartTime = 0;
			ReachedNormalRunning = true;
			pmState = PM_RUN;
			connsAllowed = ALLOW_ALL_CONNS;


			if (CheckpointerPID == 0)
				CheckpointerPID = StartCheckpointer();
			if (BgWriterPID == 0)
				BgWriterPID = StartBackgroundWriter();
			if (WalWriterPID == 0)
				WalWriterPID = StartWalWriter();


			if (!IsBinaryUpgrade && AutoVacuumingActive() && AutoVacPID == 0)
				AutoVacPID = StartAutoVacLauncher();
			if (PgArchStartupAllowed() && PgArchPID == 0)
				PgArchPID = StartArchiver();
			if (PgStatPID == 0)
				PgStatPID = pgstat_start();


			maybe_start_bgworkers();


			ereport(LOG,
					(errmsg("database system is ready to accept connections")));


			AddToDataDirLockFile(LOCK_FILE_LINE_PM_STATUS, PM_STATUS_READY);
#ifdef USE_SYSTEMD
			sd_notify(0, "READY=1");
#endif

			continue;
		}


		if (pid == BgWriterPID)
		{
			BgWriterPID = 0;
			if (!EXIT_STATUS_0(exitstatus))
				HandleChildCrash(pid, exitstatus,
								 _("background writer process"));
			continue;
		}


		if (pid == CheckpointerPID)
		{
			CheckpointerPID = 0;
			if (EXIT_STATUS_0(exitstatus) && pmState == PM_SHUTDOWN)
			{


				Assert(Shutdown > NoShutdown);


				if (PgArchPID != 0)
					signal_child(PgArchPID, SIGUSR2);


				SignalChildren(SIGUSR2);

				pmState = PM_SHUTDOWN_2;


				if (PgStatPID != 0)
					signal_child(PgStatPID, SIGQUIT);
			}
			else
			{


				HandleChildCrash(pid, exitstatus,
								 _("checkpointer process"));
			}

			continue;
		}


		if (pid == WalWriterPID)
		{
			WalWriterPID = 0;
			if (!EXIT_STATUS_0(exitstatus))
				HandleChildCrash(pid, exitstatus,
								 _("WAL writer process"));
			continue;
		}


		if (pid == WalReceiverPID)
		{
			WalReceiverPID = 0;
			if (!EXIT_STATUS_0(exitstatus) && !EXIT_STATUS_1(exitstatus))
				HandleChildCrash(pid, exitstatus,
								 _("WAL receiver process"));
			continue;
		}


		if (pid == AutoVacPID)
		{
			AutoVacPID = 0;
			if (!EXIT_STATUS_0(exitstatus))
				HandleChildCrash(pid, exitstatus,
								 _("autovacuum launcher process"));
			continue;
		}


		if (pid == PgArchPID)
		{
			PgArchPID = 0;
			if (!EXIT_STATUS_0(exitstatus) && !EXIT_STATUS_1(exitstatus))
				HandleChildCrash(pid, exitstatus,
								 _("archiver process"));
			if (PgArchStartupAllowed())
				PgArchPID = StartArchiver();
			continue;
		}


		if (pid == PgStatPID)
		{
			PgStatPID = 0;
			if (!EXIT_STATUS_0(exitstatus))
				LogChildExit(LOG, _("statistics collector process"),
							 pid, exitstatus);
			if (pmState == PM_RUN || pmState == PM_HOT_STANDBY)
				PgStatPID = pgstat_start();
			continue;
		}


		if (pid == SysLoggerPID)
		{
			SysLoggerPID = 0;

			SysLoggerPID = SysLogger_Start();
			if (!EXIT_STATUS_0(exitstatus))
				LogChildExit(LOG, _("system logger process"),
							 pid, exitstatus);
			continue;
		}


		if (CleanupBackgroundWorker(pid, exitstatus))
		{

			HaveCrashedWorker = true;
			continue;
		}


		CleanupBackend(pid, exitstatus);
	}


	PostmasterStateMachine();


#ifdef WIN32
	PG_SETMASK(&UnBlockSig);
#endif

	errno = save_errno;
}
