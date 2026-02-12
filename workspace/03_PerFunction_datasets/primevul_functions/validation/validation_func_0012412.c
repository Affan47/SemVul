static rsRetVal qDestructFixedArray(qqueue_t *pThis)
{
	DEFiRet;

	ASSERT(pThis != NULL);

	queueDrain(pThis);
	free(pThis->tVars.farray.pBuf);

	RETiRet;
}
