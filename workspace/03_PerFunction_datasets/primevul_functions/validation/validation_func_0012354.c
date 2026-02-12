InitDA(qqueue_t *pThis, int bLockMutex)
{
	DEFiRet;
	DEFVARS_mutexProtection;
	uchar pszBuf[64];
	size_t lenBuf;

	BEGIN_MTX_PROTECTED_OPERATIONS(pThis->mut, bLockMutex);


	lenBuf = snprintf((char*)pszBuf, sizeof(pszBuf), "%s:DAwpool", obj.GetName((obj_t*) pThis));
	CHKiRet(wtpConstruct		(&pThis->pWtpDA));
	CHKiRet(wtpSetDbgHdr		(pThis->pWtpDA, pszBuf, lenBuf));
	CHKiRet(wtpSetpfChkStopWrkr	(pThis->pWtpDA, (rsRetVal (*)(void *pUsr, int)) qqueueChkStopWrkrDA));
	CHKiRet(wtpSetpfGetDeqBatchSize	(pThis->pWtpDA, (rsRetVal (*)(void *pUsr, int*)) GetDeqBatchSize));
	CHKiRet(wtpSetpfDoWork		(pThis->pWtpDA, (rsRetVal (*)(void *pUsr, void *pWti)) ConsumerDA));
	CHKiRet(wtpSetpfObjProcessed	(pThis->pWtpDA, (rsRetVal (*)(void *pUsr, wti_t *pWti)) batchProcessed));
	CHKiRet(wtpSetpmutUsr		(pThis->pWtpDA, pThis->mut));
	CHKiRet(wtpSetpcondBusy		(pThis->pWtpDA, &pThis->notEmpty));
	CHKiRet(wtpSetiNumWorkerThreads	(pThis->pWtpDA, 1));
	CHKiRet(wtpSettoWrkShutdown	(pThis->pWtpDA, pThis->toWrkShutdown));
	CHKiRet(wtpSetpUsr		(pThis->pWtpDA, pThis));
	CHKiRet(wtpConstructFinalize	(pThis->pWtpDA));


	if(pThis->pqDA == NULL) {
		CHKiRet(StartDA(pThis));
	}

finalize_it:
	END_MTX_PROTECTED_OPERATIONS(pThis->mut);
	RETiRet;
}
