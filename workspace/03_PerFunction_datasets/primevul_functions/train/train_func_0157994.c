static void executeCommand( const OFString &cmd )


{
#ifdef HAVE_FORK
  pid_t pid = fork();
  if( pid < 0 )
    OFLOG_ERROR(storescpLogger, "cannot execute command '" << cmd << "' (fork failed)");
  else if (pid > 0)
  {


    cleanChildren(pid, opt_execSync);
  }
  else
  {


    if (execl( "/bin/sh", "/bin/sh", "-c", cmd.c_str(), NULL ) < 0)
      OFLOG_ERROR(storescpLogger, "cannot execute /bin/sh");


    abort();
  }
#else
  PROCESS_INFORMATION procinfo;
  STARTUPINFO sinfo;
  OFBitmanipTemplate<char>::zeroMem((char *)&sinfo, sizeof(sinfo));
  sinfo.cb = sizeof(sinfo);


  if( !CreateProcess(NULL, OFconst_cast(char *, cmd.c_str()), NULL, NULL, 0, 0, NULL, NULL, &sinfo, &procinfo) )
    OFLOG_ERROR(storescpLogger, "cannot execute command '" << cmd << "'");

  if (opt_execSync)
  {

    WaitForSingleObject(procinfo.hProcess, INFINITE);
  }


  CloseHandle(procinfo.hProcess);
  CloseHandle(procinfo.hThread);
#endif
}
