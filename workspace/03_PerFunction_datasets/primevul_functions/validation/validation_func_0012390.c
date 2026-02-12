DoDeleteBatchFromQStore(qqueue_t *pThis, int nElem)
{
	int i;
	DEFiRet;

	ISOBJ_TYPE_assert(pThis, qqueue);


	for(i = 0 ; i < nElem ; ++i) {
		pThis->qDel(pThis);
	}


	ATOMIC_SUB(&pThis->iQueueSize, nElem, &pThis->mutQueueSize);
	ATOMIC_SUB(&pThis->nLogDeq, nElem, &pThis->mutLogDeq);
dbgprintf("delete batch from store, new sizes: log %d, phys %d\n", getLogicalQueueSize(pThis), getPhysicalQueueSize(pThis));
	++pThis->deqIDDel;

	RETiRet;
}
