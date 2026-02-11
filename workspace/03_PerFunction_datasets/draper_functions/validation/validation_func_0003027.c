GetSnapshotData(Snapshot snapshot, bool serializable)
{
	ProcArrayStruct *arrayP = procArray;
	TransactionId xmin;
	TransactionId xmax;
	TransactionId globalxmin;
	int			index;
	int			count = 0;
	int			subcount = 0;

	Assert(snapshot != NULL);


	Assert(serializable ?
		   !TransactionIdIsValid(MyProc->xmin) :
		   TransactionIdIsValid(MyProc->xmin));


	if (snapshot->xip == NULL)
	{


		snapshot->xip = (TransactionId *)
			malloc(arrayP->maxProcs * sizeof(TransactionId));
		if (snapshot->xip == NULL)
			ereport(ERROR,
					(errcode(ERRCODE_OUT_OF_MEMORY),
					 errmsg("out of memory")));
		Assert(snapshot->subxip == NULL);
		snapshot->subxip = (TransactionId *)
			malloc(arrayP->maxProcs * PGPROC_MAX_CACHED_SUBXIDS * sizeof(TransactionId));
		if (snapshot->subxip == NULL)
			ereport(ERROR,
					(errcode(ERRCODE_OUT_OF_MEMORY),
					 errmsg("out of memory")));
	}

	globalxmin = xmin = GetTopTransactionId();


	LWLockAcquire(ProcArrayLock, LW_SHARED);


	xmax = ReadNewTransactionId();

	for (index = 0; index < arrayP->numProcs; index++)
	{
		PGPROC	   *proc = arrayP->procs[index];


		TransactionId xid = proc->xid;


		if (proc == MyProc ||
			!TransactionIdIsNormal(xid) ||
			TransactionIdFollowsOrEquals(xid, xmax) ||
			proc->inVacuum)
			continue;

		if (TransactionIdPrecedes(xid, xmin))
			xmin = xid;
		snapshot->xip[count] = xid;
		count++;


		xid = proc->xmin;
		if (TransactionIdIsNormal(xid))
			if (TransactionIdPrecedes(xid, globalxmin))
				globalxmin = xid;


		if (subcount >= 0)
		{
			if (proc->subxids.overflowed)
				subcount = -1;
			else
			{
				int			nxids = proc->subxids.nxids;

				if (nxids > 0)
				{
					memcpy(snapshot->subxip + subcount,
						   proc->subxids.xids,
						   nxids * sizeof(TransactionId));
					subcount += nxids;
				}
			}
		}
	}

	if (serializable)
		MyProc->xmin = TransactionXmin = xmin;

	LWLockRelease(ProcArrayLock);


	if (TransactionIdPrecedes(xmin, globalxmin))
		globalxmin = xmin;


	RecentGlobalXmin = globalxmin;
	RecentXmin = xmin;

	snapshot->xmin = xmin;
	snapshot->xmax = xmax;
	snapshot->xcnt = count;
	snapshot->subxcnt = subcount;

	snapshot->curcid = GetCurrentCommandId();

	return snapshot;
}
