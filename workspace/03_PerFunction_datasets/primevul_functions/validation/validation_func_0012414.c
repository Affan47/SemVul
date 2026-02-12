DequeueConsumable(qqueue_t *pThis, wti_t *pWti)
{
	DEFiRet;
	int iQueueSize = 0;


	iRet = DequeueConsumableElements(pThis, pWti, &iQueueSize);


	if(iQueueSize < pThis->iFullDlyMrk / 2) {
		pthread_cond_broadcast(&pThis->belowFullDlyWtrMrk);
	}

	if(iQueueSize < pThis->iLightDlyMrk / 2) {
		pthread_cond_broadcast(&pThis->belowLightDlyWtrMrk);
	}


	pthread_cond_signal(&pThis->notFull);


	if(iRet != RS_RET_OK && iRet != RS_RET_DISCARDMSG) {
		DBGOPRINT((obj_t*) pThis, "error %d dequeueing element - ignoring, but strange things "
			  "may happen\n", iRet);
	}

	RETiRet;
}
