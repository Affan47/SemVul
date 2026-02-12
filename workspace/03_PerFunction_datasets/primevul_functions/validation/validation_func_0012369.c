ConsumerReg(qqueue_t *pThis, wti_t *pWti)
{
	int iCancelStateSave;
	DEFiRet;

	ISOBJ_TYPE_assert(pThis, qqueue);
	ISOBJ_TYPE_assert(pWti, wti);

	CHKiRet(DequeueForConsumer(pThis, pWti));


	d_pthread_mutex_unlock(pThis->mut);


	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &iCancelStateSave);

	CHKiRet(pThis->pConsumer(pThis->pUsr, &pWti->batch, &pThis->bShutdownImmediate));


	if(pThis->iDeqSlowdown) {
		DBGOPRINT((obj_t*) pThis, "sleeping %d microseconds as requested by config params\n",
			  pThis->iDeqSlowdown);
		srSleep(pThis->iDeqSlowdown / 1000000, pThis->iDeqSlowdown % 1000000);
	}


	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &iCancelStateSave);


	d_pthread_mutex_lock(pThis->mut);

finalize_it:
	dbgprintf("regular consumer finished, iret=%d, szlog %d sz phys %d\n", iRet,
	          getLogicalQueueSize(pThis), getPhysicalQueueSize(pThis));
	RETiRet;
}
