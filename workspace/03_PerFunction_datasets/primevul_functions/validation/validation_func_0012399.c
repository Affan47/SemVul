qqueueDeq(qqueue_t *pThis, void **ppUsr)
{
	DEFiRet;

	ASSERT(pThis != NULL);


	iRet = pThis->qDeq(pThis, ppUsr);
	ATOMIC_INC(&pThis->nLogDeq, &pThis->mutLogDeq);


	RETiRet;
}
