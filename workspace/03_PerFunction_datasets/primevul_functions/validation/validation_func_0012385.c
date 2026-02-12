ConsumerDA(qqueue_t *pThis, wti_t *pWti)
{
	int i;
	int iCancelStateSave;
	DEFiRet;

	ISOBJ_TYPE_assert(pThis, qqueue);
	ISOBJ_TYPE_assert(pWti, wti);

	CHKiRet(DequeueForConsumer(pThis, pWti));


	d_pthread_mutex_unlock(pThis->mut);


	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &iCancelStateSave);


	for(i = 0 ; i < pWti->batch.nElem && !pThis->bShutdownImmediate ; i++) {


		CHKiRet(qqueueEnqObj(pThis->pqDA, eFLOWCTL_NO_DELAY,
			(obj_t*)MsgAddRef((msg_t*)(pWti->batch.pElem[i].pUsrp))));
		pWti->batch.pElem[i].state = BATCH_STATE_COMM;
	}


	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &iCancelStateSave);


	d_pthread_mutex_lock(pThis->mut);

finalize_it:
	DBGOPRINT((obj_t*) pThis, "DAConsumer returns with iRet %d\n", iRet);
	RETiRet;
}
