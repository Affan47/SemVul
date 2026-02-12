ShutdownWorkers(qqueue_t *pThis)
{
	DEFiRet;

	ISOBJ_TYPE_assert(pThis, qqueue);
	ASSERT(pThis->pqParent == NULL);

	DBGOPRINT((obj_t*) pThis, "initiating worker thread shutdown sequence\n");

	CHKiRet(tryShutdownWorkersWithinQueueTimeout(pThis));

	if(getPhysicalQueueSize(pThis) > 0) {
		CHKiRet(tryShutdownWorkersWithinActionTimeout(pThis));
	}

	CHKiRet(cancelWorkers(pThis));


	DBGOPRINT((obj_t*) pThis, "worker threads terminated, remaining queue size log %d, phys %d.\n",
		  getLogicalQueueSize(pThis), getPhysicalQueueSize(pThis));

finalize_it:
	RETiRet;
}
