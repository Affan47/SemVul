ajSysExecOutnameC(const char* cmdlinetxt, const char* outfnametxt)
{
#ifndef WIN32
    pid_t pid;
    pid_t retval;
    ajint status;
    char *pgm;
    char **argptr;
    ajint i;

    AjPStr pname = NULL;

    if(!ajSysArglistBuildC(cmdlinetxt, &pgm, &argptr))
	return -1;

    pname = ajStrNew();

    ajStrAssignC(&pname, pgm);

    if(!ajSysFileWhich(&pname))
	ajFatal("cannot find program '%S'", pname);

    fflush(stdout);

    pid=fork();

    if(pid==-1)
	ajFatal("System fork failed");

    if(pid)
    {
	while((retval=waitpid(pid,&status,0))!=pid)
	{
	    if(retval == -1)
		if(errno != EINTR)
		    break;
	}
    }
    else
    {


	if(!freopen(outfnametxt, "wb", stdout))
	    ajErr("Failed to redirect standard output to '%s'", outfnametxt);
	execv(ajStrGetPtr(pname), argptr);
	ajExitAbort();
    }

    ajStrDel(&pname);

    i = 0;
    while(argptr[i])
    {
	AJFREE(argptr[i]);
	++i;
    }
    AJFREE(argptr);

    AJFREE(pgm);

#else

    PROCESS_INFORMATION pinf;
    STARTUPINFO si;
    HANDLE fp;
    SECURITY_ATTRIBUTES sa;
    ajint status = 0;

    ajDebug ("Launching process '%s'\n", cmdlinetxt);

    fflush(stdout);

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags |= STARTF_USESTDHANDLES;


    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;

    fp = CreateFile(TEXT(outfnametxt), GENERIC_WRITE, 0 , &sa,
		    CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if(fp == INVALID_HANDLE_VALUE)
        ajFatal("Cannot open file %s\n",outfnametxt);


    si.hStdOutput = fp;
    si.hStdInput  = GetStdHandle(STD_INPUT_HANDLE);
    si.hStdError  = GetStdHandle(STD_ERROR_HANDLE);


    if(!CreateProcess(NULL, (char *) cmdlinetxt, NULL, NULL, TRUE,
                      CREATE_NO_WINDOW, NULL, NULL, &si, &pinf))
    {
      ajFatal("CreateProcess failed: %s", cmdlinetxt);
    }

    if(!WaitForSingleObject(pinf.hProcess, INFINITE))
        status = 0;
    else
        status = -1;

    CloseHandle(pinf.hProcess);
    CloseHandle(pinf.hThread);
#endif

    return status;
}
