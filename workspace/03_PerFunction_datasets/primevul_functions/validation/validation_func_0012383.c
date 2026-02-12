tryShutdownWorkersWithinQueueTimeout(qqueue_t *pThis)
{
	struct timespec tTimeout;
	rsRetVal iRetLocal;
	DEFiRet;

	ISOBJ_TYPE_assert(pThis, qqueue);
	ASSERT(pThis->pqParent == NULL);

	if(pThis->bIsDA) {


		d_pthread_mutex_lock(pThis->mut);


		DBGOPRINT((obj_t*) pThis, "setting EnqOnly mode for DA worker\n");
		pThis->pqDA->bEnqOnly = 1;
		wtpSetState(pThis->pWtpDA, wtpState_SHUTDOWN_IMMEDIATE);
		wtpAdviseMaxWorkers(pThis->pWtpDA, 1);
		DBGOPRINT((obj_t*) pThis, "awoke DA worker, told it to shut down.\n");


		wtpSetState(pThis->pqDA->pWtpReg, wtpState_SHUTDOWN);
		wtpAdviseMaxWorkers(pThis->pqDA->pWtpReg, 1);
		DBGOPRINT((obj_t*) pThis, "awoke DA queue regular worker, told it to shut down when done.\n");

		d_pthread_mutex_unlock(pThis->mut);
	}


	timeoutComp(&tTimeout, pThis->toQShutdown);
	DBGOPRINT((obj_t*) pThis, "trying shutdown of regular workers\n");
	iRetLocal = wtpShutdownAll(pThis->pWtpReg, wtpState_SHUTDOWN, &tTimeout);
	if(iRetLocal == RS_RET_TIMED_OUT) {
		DBGOPRINT((obj_t*) pThis, "regular shutdown timed out on primary queue (this is OK)\n");
	} else {
		DBGOPRINT((obj_t*) pThis, "regular queue workers shut down.\n");
	}


	if(pThis->pqDA != NULL) {
		DBGOPRINT((obj_t*) pThis, "we have a DA queue (0x%lx), requesting its shutdown.\n",
			 qqueueGetID(pThis->pqDA));


		DBGOPRINT((obj_t*) pThis, "trying shutdown of regular worker of DA queue\n");
		iRetLocal = wtpShutdownAll(pThis->pqDA->pWtpReg, wtpState_SHUTDOWN, &tTimeout);
		if(iRetLocal == RS_RET_TIMED_OUT) {
			DBGOPRINT((obj_t*) pThis, "shutdown timed out on DA queue worker (this is OK)\n");
		} else {
			DBGOPRINT((obj_t*) pThis, "DA queue worker shut down.\n");
		}
	}

	RETiRet;
}
