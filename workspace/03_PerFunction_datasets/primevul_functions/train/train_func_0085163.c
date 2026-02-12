PostmasterStateMachine(void)
{

	if (pmState == PM_RUN || pmState == PM_HOT_STANDBY)
	{
		if (connsAllowed == ALLOW_SUPERUSER_CONNS)
		{


			if (!BackupInProgress())
				connsAllowed = ALLOW_NO_CONNS;
		}

		if (connsAllowed == ALLOW_NO_CONNS)
		{


			if (CountChildren(BACKEND_TYPE_NORMAL) == 0)
				pmState = PM_STOP_BACKENDS;
		}
	}


	if (pmState == PM_STOP_BACKENDS)
	{


		ForgetUnstartedBackgroundWorkers();


		SignalSomeChildren(SIGTERM,
						   BACKEND_TYPE_ALL - BACKEND_TYPE_WALSND);

		if (AutoVacPID != 0)
			signal_child(AutoVacPID, SIGTERM);

		if (BgWriterPID != 0)
			signal_child(BgWriterPID, SIGTERM);

		if (WalWriterPID != 0)
			signal_child(WalWriterPID, SIGTERM);

		if (StartupPID != 0)
			signal_child(StartupPID, SIGTERM);
		if (WalReceiverPID != 0)
			signal_child(WalReceiverPID, SIGTERM);


		pmState = PM_WAIT_BACKENDS;
	}


	if (pmState == PM_WAIT_BACKENDS)
	{


		if (CountChildren(BACKEND_TYPE_ALL - BACKEND_TYPE_WALSND) == 0 &&
			StartupPID == 0 &&
			WalReceiverPID == 0 &&
			BgWriterPID == 0 &&
			(CheckpointerPID == 0 ||
			 (!FatalError && Shutdown < ImmediateShutdown)) &&
			WalWriterPID == 0 &&
			AutoVacPID == 0)
		{
			if (Shutdown >= ImmediateShutdown || FatalError)
			{


				pmState = PM_WAIT_DEAD_END;


			}
			else
			{


				Assert(Shutdown > NoShutdown);

				if (CheckpointerPID == 0)
					CheckpointerPID = StartCheckpointer();

				if (CheckpointerPID != 0)
				{
					signal_child(CheckpointerPID, SIGUSR2);
					pmState = PM_SHUTDOWN;
				}
				else
				{


					FatalError = true;
					pmState = PM_WAIT_DEAD_END;


					SignalChildren(SIGQUIT);
					if (PgArchPID != 0)
						signal_child(PgArchPID, SIGQUIT);
					if (PgStatPID != 0)
						signal_child(PgStatPID, SIGQUIT);
				}
			}
		}
	}

	if (pmState == PM_SHUTDOWN_2)
	{


		if (PgArchPID == 0 && CountChildren(BACKEND_TYPE_ALL) == 0)
		{
			pmState = PM_WAIT_DEAD_END;
		}
	}

	if (pmState == PM_WAIT_DEAD_END)
	{


		if (dlist_is_empty(&BackendList) &&
			PgArchPID == 0 && PgStatPID == 0)
		{

			Assert(StartupPID == 0);
			Assert(WalReceiverPID == 0);
			Assert(BgWriterPID == 0);
			Assert(CheckpointerPID == 0);
			Assert(WalWriterPID == 0);
			Assert(AutoVacPID == 0);

			pmState = PM_NO_CHILDREN;
		}
	}


	if (Shutdown > NoShutdown && pmState == PM_NO_CHILDREN)
	{
		if (FatalError)
		{
			ereport(LOG, (errmsg("abnormal database system shutdown")));
			ExitPostmaster(1);
		}
		else
		{


			if (ReachedNormalRunning)
				CancelBackup();


			ExitPostmaster(0);
		}
	}


	if (pmState == PM_NO_CHILDREN)
	{
		if (StartupStatus == STARTUP_CRASHED)
		{
			ereport(LOG,
					(errmsg("shutting down due to startup process failure")));
			ExitPostmaster(1);
		}
		if (!restart_after_crash)
		{
			ereport(LOG,
					(errmsg("shutting down because restart_after_crash is off")));
			ExitPostmaster(1);
		}
	}


	if (FatalError && pmState == PM_NO_CHILDREN)
	{
		ereport(LOG,
				(errmsg("all server processes terminated; reinitializing")));


		if (remove_temp_files_after_crash)
			RemovePgTempFiles();


		ResetBackgroundWorkerCrashTimes();

		shmem_exit(1);


		LocalProcessControlFile(true);

		reset_shared();

		StartupPID = StartupDataBase();
		Assert(StartupPID != 0);
		StartupStatus = STARTUP_RUNNING;
		pmState = PM_STARTUP;

		AbortStartTime = 0;
	}
}
