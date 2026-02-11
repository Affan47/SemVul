StartAutoVacLauncher(void)
{
	pid_t		AutoVacPID;

#ifdef EXEC_BACKEND
	switch ((AutoVacPID = avlauncher_forkexec()))
#else
	switch ((AutoVacPID = fork_process()))
#endif
	{
		case -1:
			ereport(LOG,
				 (errmsg("could not fork autovacuum launcher process: %m")));
			return 0;

#ifndef EXEC_BACKEND
		case 0:

			InitPostmasterChild();


			ClosePostmasterPorts(false);

			AutoVacLauncherMain(0, NULL);
			break;
#endif
		default:
			return (int) AutoVacPID;
	}


	return 0;
}
