SubPostmasterMain(int argc, char *argv[])
{
	Port		port;


	IsPostmasterEnvironment = true;
	whereToSendOutput = DestNone;


	InitializeGUCOptions();


	if (argc < 3)
		elog(FATAL, "invalid subpostmaster invocation");


	memset(&port, 0, sizeof(Port));
	read_backend_variables(argv[2], &port);


	ClosePostmasterPorts(strcmp(argv[1], "--forklog") == 0);


	InitPostmasterChild();


	if (strcmp(argv[1], "--forkbackend") == 0 ||
		strcmp(argv[1], "--forkavlauncher") == 0 ||
		strcmp(argv[1], "--forkavworker") == 0 ||
		strcmp(argv[1], "--forkaux") == 0 ||
		strncmp(argv[1], "--forkbgworker=", 15) == 0)
		PGSharedMemoryReAttach();
	else
		PGSharedMemoryNoReAttach();


	if (strcmp(argv[1], "--forkavlauncher") == 0)
		AutovacuumLauncherIAm();
	if (strcmp(argv[1], "--forkavworker") == 0)
		AutovacuumWorkerIAm();


	read_nondefault_variables();


	checkDataDir();


	LocalProcessControlFile(false);


	process_shared_preload_libraries();


	if (strcmp(argv[1], "--forkbackend") == 0)
	{
		Assert(argc == 3);


#ifdef USE_SSL
		if (EnableSSL)
		{
			if (secure_initialize(false) == 0)
				LoadedSSL = true;
			else
				ereport(LOG,
						(errmsg("SSL configuration could not be loaded in child process")));
		}
#endif


		BackendInitialize(&port);


		InitShmemAccess(UsedShmemSegAddr);


		InitProcess();


		CreateSharedMemoryAndSemaphores();


		BackendRun(&port);
	}
	if (strcmp(argv[1], "--forkaux") == 0)
	{
		AuxProcType auxtype;

		Assert(argc == 4);


		InitShmemAccess(UsedShmemSegAddr);


		InitAuxiliaryProcess();


		CreateSharedMemoryAndSemaphores();

		auxtype = atoi(argv[3]);
		AuxiliaryProcessMain(auxtype);
	}
	if (strcmp(argv[1], "--forkavlauncher") == 0)
	{

		InitShmemAccess(UsedShmemSegAddr);


		InitProcess();


		CreateSharedMemoryAndSemaphores();

		AutoVacLauncherMain(argc - 2, argv + 2);
	}
	if (strcmp(argv[1], "--forkavworker") == 0)
	{

		InitShmemAccess(UsedShmemSegAddr);


		InitProcess();


		CreateSharedMemoryAndSemaphores();

		AutoVacWorkerMain(argc - 2, argv + 2);
	}
	if (strncmp(argv[1], "--forkbgworker=", 15) == 0)
	{
		int			shmem_slot;


		IsBackgroundWorker = true;


		InitShmemAccess(UsedShmemSegAddr);


		InitProcess();


		CreateSharedMemoryAndSemaphores();


		shmem_slot = atoi(argv[1] + 15);
		MyBgworkerEntry = BackgroundWorkerEntry(shmem_slot);

		StartBackgroundWorker();
	}
	if (strcmp(argv[1], "--forkcol") == 0)
	{


		PgstatCollectorMain(argc, argv);
	}
	if (strcmp(argv[1], "--forklog") == 0)
	{


		SysLoggerMain(argc, argv);
	}

	abort();
}
