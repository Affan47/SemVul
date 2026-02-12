rsRetVal qqueueEnqObjDirectBatch(qqueue_t *pThis, batch_t *pBatch)
{
	DEFiRet;

	ASSERT(pThis != NULL);


	iRet = pThis->pConsumer(pThis->pUsr, pBatch, &pThis->bShutdownImmediate);

	RETiRet;
}
