static rsRetVal mainThread()
{
	DEFiRet;
	uchar *pTmp;


	pTmp = template_DebugFormat;
	tplAddLine("RSYSLOG_DebugFormat", &pTmp);
	pTmp = template_SyslogProtocol23Format;
	tplAddLine("RSYSLOG_SyslogProtocol23Format", &pTmp);
	pTmp = template_FileFormat;
	tplAddLine("RSYSLOG_FileFormat", &pTmp);
	pTmp = template_TraditionalFileFormat;
	tplAddLine("RSYSLOG_TraditionalFileFormat", &pTmp);
	pTmp = template_WallFmt;
	tplAddLine(" WallFmt", &pTmp);
	pTmp = template_ForwardFormat;
	tplAddLine("RSYSLOG_ForwardFormat", &pTmp);
	pTmp = template_TraditionalForwardFormat;
	tplAddLine("RSYSLOG_TraditionalForwardFormat", &pTmp);
	pTmp = template_StdUsrMsgFmt;
	tplAddLine(" StdUsrMsgFmt", &pTmp);
	pTmp = template_StdDBFmt;
	tplAddLine(" StdDBFmt", &pTmp);
        pTmp = template_StdPgSQLFmt;
        tplLastStaticInit(tplAddLine(" StdPgSQLFmt", &pTmp));

	CHKiRet(init());

	if(Debug && debugging_on) {
		DBGPRINTF("Debugging enabled, SIGUSR1 to turn off debugging.\n");
	}


	if(myPid != ppid)
		kill(ppid, SIGTERM);


	if(gidDropPriv != 0) {
		doDropPrivGid(gidDropPriv);
		glbl.SetHUPisRestart(0);
	}

	if(uidDropPriv != 0) {
		doDropPrivUid(uidDropPriv);
		glbl.SetHUPisRestart(0);
	}


	runInputModules();


	DBGPRINTF("initialization completed, transitioning to regular run mode\n");


	if(!(Debug || NoFork)) {
		close(1);
		close(2);
		bErrMsgToStderr = 0;
	}

	mainloop();

finalize_it:
	RETiRet;
}
