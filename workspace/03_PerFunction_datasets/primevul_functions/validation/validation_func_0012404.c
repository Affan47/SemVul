doEnqSingleObj(qqueue_t *pThis, flowControl_t flowCtlType, void *pUsr)
{
	DEFiRet;
	struct timespec t;


	CHKiRet(qqueueChkDiscardMsg(pThis, pThis->iQueueSize, pUsr));


	if(flowCtlType == eFLOWCTL_FULL_DELAY) {
		while(pThis->iQueueSize >= pThis->iFullDlyMrk) {
			DBGOPRINT((obj_t*) pThis, "enqueueMsg: FullDelay mark reached for full delayable message - blocking.\n");
			pthread_cond_wait(&pThis->belowFullDlyWtrMrk, pThis->mut);
		}
	} else if(flowCtlType == eFLOWCTL_LIGHT_DELAY) {
		if(pThis->iQueueSize >= pThis->iLightDlyMrk) {
			DBGOPRINT((obj_t*) pThis, "enqueueMsg: LightDelay mark reached for light delayable message - blocking a bit.\n");
			timeoutComp(&t, 1000);
			pthread_cond_timedwait(&pThis->belowLightDlyWtrMrk, pThis->mut, &t);
		}
	}


	while(   (pThis->iMaxQueueSize > 0 && pThis->iQueueSize >= pThis->iMaxQueueSize)
	      || (pThis->qType == QUEUETYPE_DISK && pThis->sizeOnDiskMax != 0
	      	  && pThis->tVars.disk.sizeOnDisk > pThis->sizeOnDiskMax)) {
		DBGOPRINT((obj_t*) pThis, "enqueueMsg: queue FULL - waiting to drain.\n");
		timeoutComp(&t, pThis->toEnq);

		if(pthread_cond_timedwait(&pThis->notFull, pThis->mut, &t) != 0) {
			DBGOPRINT((obj_t*) pThis, "enqueueMsg: cond timeout, dropping message!\n");
			objDestruct(pUsr);
			ABORT_FINALIZE(RS_RET_QUEUE_FULL);
		}
	}


	CHKiRet(qqueueAdd(pThis, pUsr));

finalize_it:
	RETiRet;
}
