init()
{
	rsRetVal localRet;
	int iNbrActions;
	int bHadConfigErr = 0;
	ruleset_t *pRuleset;
	char cbuf[BUFSIZ];
	char bufStartUpMsg[512];
	struct sigaction sigAct;
	DEFiRet;

	thrdTerminateAll();


	pDfltHostnameCmp = NULL;
	pDfltProgNameCmp = NULL;
	eDfltHostnameCmpMode = HN_NO_COMP;

	DBGPRINTF("rsyslog %s - called init()\n", VERSION);


	if(pMsgQueue != NULL) {
		DBGPRINTF("deleting main message queue\n");
		qqueueDestruct(&pMsgQueue);
		pMsgQueue = NULL;
	}


	destructAllActions();


	DBGPRINTF("Unloading non-static modules.\n");
	module.UnloadAndDestructAll(eMOD_LINK_DYNAMIC_LOADED);

	DBGPRINTF("Clearing templates.\n");
	tplDeleteNew();


	conf.cfsysline((uchar*)"ResetConfigVariables");

	conf.ReInitConf();


	ruleset.Construct(&pRuleset);
	ruleset.SetName(pRuleset, UCHAR_CONSTANT("RSYSLOG_DefaultRuleset"));
	ruleset.ConstructFinalize(pRuleset);


	localRet = conf.processConfFile(ConfFile);
	CHKiRet(conf.GetNbrActActions(&iNbrActions));

	if(localRet != RS_RET_OK) {
		errmsg.LogError(0, localRet, "CONFIG ERROR: could not interpret master config file '%s'.", ConfFile);
		bHadConfigErr = 1;
	} else if(iNbrActions == 0) {
		errmsg.LogError(0, RS_RET_NO_ACTIONS, "CONFIG ERROR: there are no active actions configured. Inputs will "
			 "run, but no output whatsoever is created.");
		bHadConfigErr = 1;
	}

	if((localRet != RS_RET_OK && localRet != RS_RET_NONFATAL_CONFIG_ERR) || iNbrActions == 0) {


		errmsg.LogError(0, NO_ERRCODE, "EMERGENCY CONFIGURATION ACTIVATED - fix rsyslog config file!");


		char szTTYNameBuf[128];
		rule_t *pRule = NULL;
		conf.cfline(UCHAR_CONSTANT("*.ERR\t" _PATH_CONSOLE), &pRule);
		conf.cfline(UCHAR_CONSTANT("syslog.*\t" _PATH_CONSOLE), &pRule);
		conf.cfline(UCHAR_CONSTANT("*.PANIC\t*"), &pRule);
		conf.cfline(UCHAR_CONSTANT("syslog.*\troot"), &pRule);
		if(ttyname_r(0, szTTYNameBuf, sizeof(szTTYNameBuf)) == 0) {
			snprintf(cbuf,sizeof(cbuf), "*.*\t%s", szTTYNameBuf);
			conf.cfline((uchar*)cbuf, &pRule);
		} else {
			DBGPRINTF("error %d obtaining controlling terminal, not using that emergency rule\n", errno);
		}
		ruleset.AddRule(ruleset.GetCurrent(), &pRule);
	}

	legacyOptsHook();


	if(pDfltHostnameCmp != NULL) {
		rsCStrDestruct(&pDfltHostnameCmp);
	}

	if(pDfltProgNameCmp != NULL) {
		rsCStrDestruct(&pDfltProgNameCmp);
	}


	if(iMainMsgQueueNumWorkers < 1) {
		errmsg.LogError(0, NO_ERRCODE, "$MainMsgQueueNumWorkers must be at least 1! Set to 1.\n");
		iMainMsgQueueNumWorkers = 1;
	}

	if(MainMsgQueType == QUEUETYPE_DISK) {
		errno = 0;
		if(glbl.GetWorkDir() == NULL) {
			errmsg.LogError(0, NO_ERRCODE, "No $WorkDirectory specified - can not run main message queue in 'disk' mode. "
				 "Using 'FixedArray' instead.\n");
			MainMsgQueType = QUEUETYPE_FIXED_ARRAY;
		}
		if(pszMainMsgQFName == NULL) {
			errmsg.LogError(0, NO_ERRCODE, "No $MainMsgQueueFileName specified - can not run main message queue in "
				 "'disk' mode. Using 'FixedArray' instead.\n");
			MainMsgQueType = QUEUETYPE_FIXED_ARRAY;
		}
	}


	if(pszConfDAGFile != NULL)
		generateConfigDAG(pszConfDAGFile);


	if(iConfigVerify) {
		if(bHadConfigErr) {

			exit(1);
		}
		ABORT_FINALIZE(RS_RET_VALIDATION_RUN);
	}


	if(MainMsgQueType == QUEUETYPE_DIRECT || iMainMsgQueueNumWorkers > 1) {
		MsgEnableThreadSafety();
	}


	CHKiRet_Hdlr(qqueueConstruct(&pMsgQueue, MainMsgQueType, iMainMsgQueueNumWorkers, iMainMsgQueueSize, msgConsumer)) {

		fprintf(stderr, "fatal error %d: could not create message queue - rsyslogd can not run!\n", iRet);
		exit(1);
	}

	obj.SetName((obj_t*) pMsgQueue, (uchar*) "main Q");


#	define setQPROP(func, directive, data) \
	CHKiRet_Hdlr(func(pMsgQueue, data)) { \
		errmsg.LogError(0, NO_ERRCODE, "Invalid " #directive ", error %d. Ignored, running with default setting", iRet); \
	}
#	define setQPROPstr(func, directive, data) \
	CHKiRet_Hdlr(func(pMsgQueue, data, (data == NULL)? 0 : strlen((char*) data))) { \
		errmsg.LogError(0, NO_ERRCODE, "Invalid " #directive ", error %d. Ignored, running with default setting", iRet); \
	}

	setQPROP(qqueueSetMaxFileSize, "$MainMsgQueueFileSize", iMainMsgQueMaxFileSize);
	setQPROP(qqueueSetsizeOnDiskMax, "$MainMsgQueueMaxDiskSpace", iMainMsgQueMaxDiskSpace);
	setQPROPstr(qqueueSetFilePrefix, "$MainMsgQueueFileName", pszMainMsgQFName);
	setQPROP(qqueueSetiPersistUpdCnt, "$MainMsgQueueCheckpointInterval", iMainMsgQPersistUpdCnt);
	setQPROP(qqueueSetbSyncQueueFiles, "$MainMsgQueueSyncQueueFiles", bMainMsgQSyncQeueFiles);
	setQPROP(qqueueSettoQShutdown, "$MainMsgQueueTimeoutShutdown", iMainMsgQtoQShutdown );
	setQPROP(qqueueSettoActShutdown, "$MainMsgQueueTimeoutActionCompletion", iMainMsgQtoActShutdown);
	setQPROP(qqueueSettoWrkShutdown, "$MainMsgQueueWorkerTimeoutThreadShutdown", iMainMsgQtoWrkShutdown);
	setQPROP(qqueueSettoEnq, "$MainMsgQueueTimeoutEnqueue", iMainMsgQtoEnq);
	setQPROP(qqueueSetiHighWtrMrk, "$MainMsgQueueHighWaterMark", iMainMsgQHighWtrMark);
	setQPROP(qqueueSetiLowWtrMrk, "$MainMsgQueueLowWaterMark", iMainMsgQLowWtrMark);
	setQPROP(qqueueSetiDiscardMrk, "$MainMsgQueueDiscardMark", iMainMsgQDiscardMark);
	setQPROP(qqueueSetiDiscardSeverity, "$MainMsgQueueDiscardSeverity", iMainMsgQDiscardSeverity);
	setQPROP(qqueueSetiMinMsgsPerWrkr, "$MainMsgQueueWorkerThreadMinimumMessages", iMainMsgQWrkMinMsgs);
	setQPROP(qqueueSetbSaveOnShutdown, "$MainMsgQueueSaveOnShutdown", bMainMsgQSaveOnShutdown);
	setQPROP(qqueueSetiDeqSlowdown, "$MainMsgQueueDequeueSlowdown", iMainMsgQDeqSlowdown);
	setQPROP(qqueueSetiDeqtWinFromHr,  "$MainMsgQueueDequeueTimeBegin", iMainMsgQueueDeqtWinFromHr);
	setQPROP(qqueueSetiDeqtWinToHr,    "$MainMsgQueueDequeueTimeEnd", iMainMsgQueueDeqtWinToHr);

#	undef setQPROP
#	undef setQPROPstr


	CHKiRet_Hdlr(qqueueStart(pMsgQueue)) {

		fprintf(stderr, "fatal error %d: could not start message queue - rsyslogd can not run!\n", iRet);
		exit(1);
	}

	bHaveMainQueue = (MainMsgQueType == QUEUETYPE_DIRECT) ? 0 : 1;
	DBGPRINTF("Main processing queue is initialized and running\n");


	startInputModules();

	if(Debug) {
		dbgPrintInitInfo();
	}


	snprintf(bufStartUpMsg, sizeof(bufStartUpMsg)/sizeof(char),
		 " [origin software=\"rsyslogd\" " "swVersion=\"" VERSION \
		 "\" x-pid=\"%d\" x-info=\"http://www.rsyslog.com\"] (re)start",
		 (int) myPid);
	logmsgInternal(NO_ERRCODE, LOG_SYSLOG|LOG_INFO, (uchar*)bufStartUpMsg, 0);

	memset(&sigAct, 0, sizeof (sigAct));
	sigemptyset(&sigAct.sa_mask);
	sigAct.sa_handler = sighup_handler;
	sigaction(SIGHUP, &sigAct, NULL);

	DBGPRINTF(" (re)started.\n");

finalize_it:
	RETiRet;
}
