GetDeqBatchSize(qqueue_t *pThis, int *pVal)
{
	DEFiRet;
	assert(pVal != NULL);
	*pVal = pThis->iDeqBatchSize;
if(pThis->pqParent != NULL)
	*pVal = 16;
	RETiRet;
}
