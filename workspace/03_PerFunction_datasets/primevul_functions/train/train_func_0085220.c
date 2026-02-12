StartChildProcess(AuxProcType type)
{
	pid_t		pid;

#ifdef EXEC_BACKEND
	{
		char	   *av[10];
		int			ac = 0;
		char		typebuf[32];


		av[ac++] = "postgres";
		av[ac++] = "--forkaux";
		av[ac++] = NULL;

		snprintf(typebuf, sizeof(typebuf), "%d", type);
		av[ac++] = typebuf;

		av[ac] = NULL;
		Assert(ac < lengthof(av));

		pid = postmaster_forkexec(ac, av);
	}
#else
	pid = fork_process();

	if (pid == 0)
	{
		InitPostmasterChild();


		ClosePostmasterPorts(false);


		MemoryContextSwitchTo(TopMemoryContext);
		MemoryContextDelete(PostmasterContext);
		PostmasterContext = NULL;

		AuxiliaryProcessMain(type);
	}
#endif

	if (pid < 0)
	{

		int			save_errno = errno;

		errno = save_errno;
		switch (type)
		{
			case StartupProcess:
				ereport(LOG,
						(errmsg("could not fork startup process: %m")));
				break;
			case ArchiverProcess:
				ereport(LOG,
						(errmsg("could not fork archiver process: %m")));
				break;
			case BgWriterProcess:
				ereport(LOG,
						(errmsg("could not fork background writer process: %m")));
				break;
			case CheckpointerProcess:
				ereport(LOG,
						(errmsg("could not fork checkpointer process: %m")));
				break;
			case WalWriterProcess:
				ereport(LOG,
						(errmsg("could not fork WAL writer process: %m")));
				break;
			case WalReceiverProcess:
				ereport(LOG,
						(errmsg("could not fork WAL receiver process: %m")));
				break;
			default:
				ereport(LOG,
						(errmsg("could not fork process: %m")));
				break;
		}


		if (type == StartupProcess)
			ExitPostmaster(1);
		return 0;
	}


	return pid;
}
