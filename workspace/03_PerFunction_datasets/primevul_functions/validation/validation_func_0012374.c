cancelWorkers(qqueue_t *pThis)
{
	rsRetVal iRetLocal;
	DEFiRet;


	DBGOPRINT((obj_t*) pThis, "checking to see if we need to cancel any worker threads of the primary queue\n");
	iRetLocal = wtpCancelAll(pThis->pWtpReg);
	if(iRetLocal != RS_RET_OK) {
		DBGOPRINT((obj_t*) pThis, "unexpected iRet state %d trying to cancel primary queue worker "
			  "threads, continuing, but results are unpredictable\n", iRetLocal);
	}


	if(pThis->pqDA != NULL) {
		DBGOPRINT((obj_t*) pThis, "checking to see if we need to cancel any worker threads of the DA queue\n");
		iRetLocal = wtpCancelAll(pThis->pqDA->pWtpReg);
		if(iRetLocal != RS_RET_OK) {
			DBGOPRINT((obj_t*) pThis, "unexpected iRet state %d trying to cancel DA queue worker "
				  "threads, continuing, but results are unpredictable\n", iRetLocal);
		}


		DBGOPRINT((obj_t*) pThis, "checking to see if main queue DA worker pool needs to be cancelled\n");
		wtpCancelAll(pThis->pWtpDA);
	}

	RETiRet;
}
