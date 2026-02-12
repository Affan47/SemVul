DequeueConsumableElements(qqueue_t *pThis, wti_t *pWti, int *piRemainingQueueSize)
{
	int nDequeued;
	int nDiscarded;
	int nDeleted;
	int iQueueSize;
	void *pUsr;
	rsRetVal localRet;
	DEFiRet;

	nDeleted = pWti->batch.nElemDeq;
	DeleteProcessedBatch(pThis, &pWti->batch);

	nDequeued = nDiscarded = 0;
	while((iQueueSize = getLogicalQueueSize(pThis)) > 0 && nDequeued < pThis->iDeqBatchSize) {
		CHKiRet(qqueueDeq(pThis, &pUsr));


		localRet = qqueueChkDiscardMsg(pThis, pThis->iQueueSize, pUsr);
		if(localRet == RS_RET_QUEUE_FULL) {
			++nDiscarded;
			continue;
		} else if(localRet != RS_RET_OK) {
			ABORT_FINALIZE(localRet);
		}


		pWti->batch.pElem[nDequeued].pUsrp = pUsr;
		pWti->batch.pElem[nDequeued].state = BATCH_STATE_RDY;
		pWti->batch.pElem[nDequeued].bFilterOK = 1;
		++nDequeued;
	}


	qqueueChkPersist(pThis, nDequeued+nDiscarded+nDeleted);

	pWti->batch.nElem = nDequeued;
	pWti->batch.nElemDeq = nDequeued + nDiscarded;
	pWti->batch.deqID = getNextDeqID(pThis);
	*piRemainingQueueSize = iQueueSize;

finalize_it:
	RETiRet;
}
