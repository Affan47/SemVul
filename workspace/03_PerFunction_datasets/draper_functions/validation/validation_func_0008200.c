SysLogger_Start(void)
{
	pid_t		sysloggerPid;
	char	   *filename;

	if (!Logging_collector)
		return 0;


#ifndef WIN32
	if (syslogPipe[0] < 0)
	{
		if (pgpipe(syslogPipe) < 0)
			ereport(FATAL,
					(errcode_for_socket_access(),
					 (errmsg("could not create pipe for syslog: %m"))));
	}
#else
	if (!syslogPipe[0])
	{
		SECURITY_ATTRIBUTES sa;

		memset(&sa, 0, sizeof(SECURITY_ATTRIBUTES));
		sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		sa.bInheritHandle = TRUE;

		if (!CreatePipe(&syslogPipe[0], &syslogPipe[1], &sa, 32768))
			ereport(FATAL,
					(errcode_for_file_access(),
					 (errmsg("could not create pipe for syslog: %m"))));
	}
#endif


	mkdir(Log_directory, S_IRWXU);


	filename = logfile_getname(time(NULL), NULL);

	syslogFile = logfile_open(filename, "a", false);

	pfree(filename);

#ifdef EXEC_BACKEND
	switch ((sysloggerPid = syslogger_forkexec()))
#else
	switch ((sysloggerPid = fork_process()))
#endif
	{
		case -1:
			ereport(LOG,
					(errmsg("could not fork system logger: %m")));
			return 0;

#ifndef EXEC_BACKEND
		case 0:


			ClosePostmasterPorts(true);


			on_exit_reset();


			PGSharedMemoryDetach();


			SysLoggerMain(0, NULL);
			break;
#endif

		default:


			if (!redirection_done)
			{
#ifndef WIN32
				fflush(stdout);
				if (dup2(syslogPipe[1], fileno(stdout)) < 0)
					ereport(FATAL,
							(errcode_for_file_access(),
							 errmsg("could not redirect stdout: %m")));
				fflush(stderr);
				if (dup2(syslogPipe[1], fileno(stderr)) < 0)
					ereport(FATAL,
							(errcode_for_file_access(),
							 errmsg("could not redirect stderr: %m")));

				close(syslogPipe[1]);
				syslogPipe[1] = -1;
#else
				int			fd;


				fflush(stderr);
				fd = _open_osfhandle((intptr_t) syslogPipe[1],
									 _O_APPEND | _O_BINARY);
				if (dup2(fd, _fileno(stderr)) < 0)
					ereport(FATAL,
							(errcode_for_file_access(),
							 errmsg("could not redirect stderr: %m")));
				close(fd);
				_setmode(_fileno(stderr), _O_BINARY);

				CloseHandle(syslogPipe[1]);
				syslogPipe[1] = 0;
#endif
				redirection_done = true;
			}


			fclose(syslogFile);
			syslogFile = NULL;
			return (int) sysloggerPid;
	}


	return 0;
}
