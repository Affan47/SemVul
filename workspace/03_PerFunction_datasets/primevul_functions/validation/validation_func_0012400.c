qqueueStart(qqueue_t *pThis)
{
	DEFiRet;
	uchar pszBuf[64];
	size_t lenBuf;

	ASSERT(pThis != NULL);


	if(pThis->pqParent == NULL) {
		pThis->mut = (pthread_mutex_t *) MALLOC (sizeof (pthread_mutex_t));
		pthread_mutex_init(pThis->mut, NULL);
	} else {

		DBGOPRINT((obj_t*) pThis, "I am a child\n");
		pThis->mut = pThis->pqParent->mut;
	}

	pthread_mutex_init(&pThis->mutThrdMgmt, NULL);
	pthread_cond_init (&pThis->condDAReady, NULL);
	pthread_cond_init (&pThis->notFull, NULL);
	pthread_cond_init (&pThis->notEmpty, NULL);
	pthread_cond_init (&pThis->belowFullDlyWtrMrk, NULL);
	pthread_cond_init (&pThis->belowLightDlyWtrMrk, NULL);


	CHKiRet(pThis->qConstruct(pThis));

	DBGOPRINT((obj_t*) pThis, "type %d, enq-only %d, disk assisted %d, maxFileSz %lld, lqsize %d, pqsize %d, child %d, "
				  "full delay %d, light delay %d, deq batch size %d starting\n",
		  pThis->qType, pThis->bEnqOnly, pThis->bIsDA, pThis->iMaxFileSize,
		  getLogicalQueueSize(pThis), getPhysicalQueueSize(pThis),
		  pThis->pqParent == NULL ? 0 : 1, pThis->iFullDlyMrk, pThis->iLightDlyMrk,
		  pThis->iDeqBatchSize);

	if(pThis->qType == QUEUETYPE_DIRECT)
		FINALIZE;


	lenBuf = snprintf((char*)pszBuf, sizeof(pszBuf), "%s:Reg", obj.GetName((obj_t*) pThis));
	CHKiRet(wtpConstruct		(&pThis->pWtpReg));
	CHKiRet(wtpSetDbgHdr		(pThis->pWtpReg, pszBuf, lenBuf));
	CHKiRet(wtpSetpfRateLimiter	(pThis->pWtpReg, (rsRetVal (*)(void *pUsr)) RateLimiter));
	CHKiRet(wtpSetpfChkStopWrkr	(pThis->pWtpReg, (rsRetVal (*)(void *pUsr, int)) ChkStopWrkrReg));
	CHKiRet(wtpSetpfGetDeqBatchSize	(pThis->pWtpReg, (rsRetVal (*)(void *pUsr, int*)) GetDeqBatchSize));
	CHKiRet(wtpSetpfDoWork		(pThis->pWtpReg, (rsRetVal (*)(void *pUsr, void *pWti)) ConsumerReg));
	CHKiRet(wtpSetpfObjProcessed	(pThis->pWtpReg, (rsRetVal (*)(void *pUsr, wti_t *pWti)) batchProcessed));
	CHKiRet(wtpSetpmutUsr		(pThis->pWtpReg, pThis->mut));
	CHKiRet(wtpSetpcondBusy		(pThis->pWtpReg, &pThis->notEmpty));
	CHKiRet(wtpSetiNumWorkerThreads	(pThis->pWtpReg, pThis->iNumWorkerThreads));
	CHKiRet(wtpSettoWrkShutdown	(pThis->pWtpReg, pThis->toWrkShutdown));
	CHKiRet(wtpSetpUsr		(pThis->pWtpReg, pThis));
	CHKiRet(wtpConstructFinalize	(pThis->pWtpReg));


	if(pThis->bIsDA)
		InitDA(pThis, LOCK_MUTEX);

	DBGOPRINT((obj_t*) pThis, "queue finished initialization\n");


	qqueueAdviseMaxWorkers(pThis);
	pThis->bQueueStarted = 1;

finalize_it:
	RETiRet;
}
