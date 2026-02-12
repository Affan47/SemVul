die(int sig)
{
	char buf[256];

	DBGPRINTF("exiting on signal %d\n", sig);


	DBGPRINTF("Terminating input threads...\n");
	thrdTerminateAll();


	if (sig) {
		(void) snprintf(buf, sizeof(buf) / sizeof(char),
		 " [origin software=\"rsyslogd\" " "swVersion=\"" VERSION \
		 "\" x-pid=\"%d\" x-info=\"http://www.rsyslog.com\"]" " exiting on signal %d.",
		 (int) myPid, sig);
		errno = 0;
		logmsgInternal(NO_ERRCODE, LOG_SYSLOG|LOG_INFO, (uchar*)buf, 0);
	}


	DBGPRINTF("Terminating main queue...\n");
	qqueueDestruct(&pMsgQueue);
	pMsgQueue = NULL;


	DBGPRINTF("Terminating outputs...\n");
	destructAllActions();

	DBGPRINTF("all primary multi-thread sources have been terminated - now doing aux cleanup...\n");


	tplDeleteAll();

	remove_pid(PidFile);


	modExitIminternal();


	unregCfSysLineHdlrs();

	legacyOptsFree();


	if(pInternalInputName != NULL)
		prop.Destruct(&pInternalInputName);
	if(pLocalHostIP != NULL)
		prop.Destruct(&pLocalHostIP);


	GlobalClassExit();


	module.UnloadAndDestructAll(eMOD_LINK_ALL);

	DBGPRINTF("Clean shutdown completed, bye\n");

	dbgClassExit();


	freeAllDynMemForTermination();

	exit(0);
}
