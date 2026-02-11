RecordTransactionAbortPrepared(TransactionId xid,
							   int nchildren,
							   TransactionId *children,
							   int nrels,
							   RelFileNode *rels)
{
	XLogRecData rdata[3];
	int			lastrdata = 0;
	xl_xact_abort_prepared xlrec;
	XLogRecPtr	recptr;


	if (TransactionIdDidCommit(xid))
		elog(PANIC, "cannot abort transaction %u, it was already committed",
			 xid);

	START_CRIT_SECTION();


	xlrec.xid = xid;
	xlrec.arec.xact_time = GetCurrentTimestamp();
	xlrec.arec.nrels = nrels;
	xlrec.arec.nsubxacts = nchildren;
	rdata[0].data = (char *) (&xlrec);
	rdata[0].len = MinSizeOfXactAbortPrepared;
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

	recptr = XLogInsert(RM_XACT_ID, XLOG_XACT_ABORT_PREPARED, rdata);


	XLogFlush(recptr);


	TransactionIdAbortTree(xid, nchildren, children);

	END_CRIT_SECTION();
}
