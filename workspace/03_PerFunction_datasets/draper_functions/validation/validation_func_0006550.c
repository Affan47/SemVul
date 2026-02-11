RecordTransactionAbort(bool isSubXact)
{
	TransactionId xid = GetCurrentTransactionIdIfAny();
	TransactionId latestXid;
	int			nrels;
	RelFileNode *rels;
	int			nchildren;
	TransactionId *children;
	XLogRecData rdata[3];
	int			lastrdata = 0;
	xl_xact_abort xlrec;


	if (!TransactionIdIsValid(xid))
	{

		if (!isSubXact)
			XactLastRecEnd.xrecoff = 0;
		return InvalidTransactionId;
	}


	if (TransactionIdDidCommit(xid))
		elog(PANIC, "cannot abort transaction %u, it was already committed",
			 xid);


	nrels = smgrGetPendingDeletes(false, &rels, NULL);
	nchildren = xactGetCommittedChildren(&children);


	START_CRIT_SECTION();


	if (isSubXact)
		xlrec.xact_time = GetCurrentTimestamp();
	else
	{
		SetCurrentTransactionStopTimestamp();
		xlrec.xact_time = xactStopTimestamp;
	}
	xlrec.nrels = nrels;
	xlrec.nsubxacts = nchildren;
	rdata[0].data = (char *) (&xlrec);
	rdata[0].len = MinSizeOfXactAbort;
	rdata[0].buffer = InvalidBuffer;

	if (nrels > 0)
	{
		rdata[0].next = &(rdata[1]);
		rdata[1].data = (char *) rels;
		rdata[1].len = nrels * sizeof(RelFileNode);
		rdata[1].buffer = InvalidBuffer;
		lastrdata = 1;
	}

	if (nchildren > 0)
	{
		rdata[lastrdata].next = &(rdata[2]);
		rdata[2].data = (char *) children;
		rdata[2].len = nchildren * sizeof(TransactionId);
		rdata[2].buffer = InvalidBuffer;
		lastrdata = 2;
	}
	rdata[lastrdata].next = NULL;

	(void) XLogInsert(RM_XACT_ID, XLOG_XACT_ABORT, rdata);


	TransactionIdAbort(xid);
	TransactionIdAbortTree(nchildren, children);

	END_CRIT_SECTION();


	latestXid = TransactionIdLatest(xid, nchildren, children);


	if (isSubXact)
		XidCacheRemoveRunningXids(xid, nchildren, children, latestXid);


	if (!isSubXact)
		XactLastRecEnd.xrecoff = 0;


	if (rels)
		pfree(rels);

	return latestXid;
}
