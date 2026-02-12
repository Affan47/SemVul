pmdie(SIGNAL_ARGS)
{
	int			save_errno = errno;


#ifdef WIN32
	PG_SETMASK(&BlockSig);
#endif

	ereport(DEBUG2,
			(errmsg_internal("postmaster received signal %d",
							 postgres_signal_arg)));

	switch (postgres_signal_arg)
	{
		case SIGTERM:


			if (Shutdown >= SmartShutdown)
				break;
			Shutdown = SmartShutdown;
			ereport(LOG,
					(errmsg("received smart shutdown request")));


			AddToDataDirLockFile(LOCK_FILE_LINE_PM_STATUS, PM_STATUS_STOPPING);
#ifdef USE_SYSTEMD
			sd_notify(0, "STOPPING=1");
#endif


			if (pmState == PM_RUN)
				connsAllowed = ALLOW_SUPERUSER_CONNS;
			else if (pmState == PM_HOT_STANDBY)
				connsAllowed = ALLOW_NO_CONNS;
			else if (pmState == PM_STARTUP || pmState == PM_RECOVERY)
			{

				pmState = PM_STOP_BACKENDS;
			}


			PostmasterStateMachine();
			break;

		case SIGINT:


			if (Shutdown >= FastShutdown)
				break;
			Shutdown = FastShutdown;
			ereport(LOG,
					(errmsg("received fast shutdown request")));


			AddToDataDirLockFile(LOCK_FILE_LINE_PM_STATUS, PM_STATUS_STOPPING);
#ifdef USE_SYSTEMD
			sd_notify(0, "STOPPING=1");
#endif

			if (pmState == PM_STARTUP || pmState == PM_RECOVERY)
			{

				pmState = PM_STOP_BACKENDS;
			}
			else if (pmState == PM_RUN ||
					 pmState == PM_HOT_STANDBY)
			{

				ereport(LOG,
						(errmsg("aborting any active transactions")));
				pmState = PM_STOP_BACKENDS;
			}


			PostmasterStateMachine();
			break;

		case SIGQUIT:


			if (Shutdown >= ImmediateShutdown)
				break;
			Shutdown = ImmediateShutdown;
			ereport(LOG,
					(errmsg("received immediate shutdown request")));


			AddToDataDirLockFile(LOCK_FILE_LINE_PM_STATUS, PM_STATUS_STOPPING);
#ifdef USE_SYSTEMD
			sd_notify(0, "STOPPING=1");
#endif


			SetQuitSignalReason(PMQUIT_FOR_STOP);
			TerminateChildren(SIGQUIT);
			pmState = PM_WAIT_BACKENDS;


			AbortStartTime = time(NULL);


			PostmasterStateMachine();
			break;
	}

#ifdef WIN32
	PG_SETMASK(&UnBlockSig);
#endif

	errno = save_errno;
}
