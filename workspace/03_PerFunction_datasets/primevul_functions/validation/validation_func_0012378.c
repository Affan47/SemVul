rsRetVal qqueueConstruct(qqueue_t **ppThis, queueType_t qType, int iWorkerThreads,
		        int iMaxQueueSize, rsRetVal (*pConsumer)(void*, batch_t*,int*))
{
	DEFiRet;
	qqueue_t *pThis;

	ASSERT(ppThis != NULL);
	ASSERT(pConsumer != NULL);
	ASSERT(iWorkerThreads >= 0);

	CHKmalloc(pThis = (qqueue_t *)calloc(1, sizeof(qqueue_t)));


	objConstructSetObjInfo(pThis);
	if((pThis->pszSpoolDir = (uchar*) strdup((char*)glbl.GetWorkDir())) == NULL)
		ABORT_FINALIZE(RS_RET_OUT_OF_MEMORY);


	pThis->iFullDlyMrk  = iMaxQueueSize - (iMaxQueueSize / 100) *  3;
	pThis->iLightDlyMrk = iMaxQueueSize - (iMaxQueueSize / 100) * 30;

	pThis->lenSpoolDir = ustrlen(pThis->pszSpoolDir);
	pThis->iMaxFileSize = 1024 * 1024;
	pThis->iQueueSize = 0;
	pThis->nLogDeq = 0;
	pThis->iMaxQueueSize = iMaxQueueSize;
	pThis->pConsumer = pConsumer;
	pThis->iNumWorkerThreads = iWorkerThreads;
	pThis->iDeqtWinToHr = 25;
	pThis->iDeqBatchSize = 8;

	pThis->pszFilePrefix = NULL;
	pThis->qType = qType;


	switch(qType) {
		case QUEUETYPE_FIXED_ARRAY:
			pThis->qConstruct = qConstructFixedArray;
			pThis->qDestruct = qDestructFixedArray;
			pThis->qAdd = qAddFixedArray;
			pThis->qDeq = qDeqFixedArray;
			pThis->qDel = qDelFixedArray;
			pThis->MultiEnq = qqueueMultiEnqObjNonDirect;
			break;
		case QUEUETYPE_LINKEDLIST:
			pThis->qConstruct = qConstructLinkedList;
			pThis->qDestruct = qDestructLinkedList;
			pThis->qAdd = qAddLinkedList;
			pThis->qDeq = (rsRetVal (*)(qqueue_t*,void**)) qDeqLinkedList;
			pThis->qDel = (rsRetVal (*)(qqueue_t*)) qDelLinkedList;
			pThis->MultiEnq = qqueueMultiEnqObjNonDirect;
			break;
		case QUEUETYPE_DISK:
			pThis->qConstruct = qConstructDisk;
			pThis->qDestruct = qDestructDisk;
			pThis->qAdd = qAddDisk;
			pThis->qDeq = qDeqDisk;
			pThis->qDel = qDelDisk;
			pThis->MultiEnq = qqueueMultiEnqObjNonDirect;

			pThis->iNumWorkerThreads = 1;
			break;
		case QUEUETYPE_DIRECT:
			pThis->qConstruct = qConstructDirect;
			pThis->qDestruct = qDestructDirect;
			pThis->qAdd = qAddDirect;
			pThis->qDel = qDelDirect;
			pThis->MultiEnq = qqueueMultiEnqObjDirect;
			break;
	}

	INIT_ATOMIC_HELPER_MUT(pThis->mutQueueSize);
	INIT_ATOMIC_HELPER_MUT(pThis->mutLogDeq);

finalize_it:
	OBJCONSTRUCT_CHECK_SUCCESS_AND_CLEANUP
	RETiRet;
}
