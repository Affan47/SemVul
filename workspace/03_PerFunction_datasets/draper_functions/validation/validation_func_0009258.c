xact_redo_commit(xl_xact_commit *xlrec, TransactionId xid)
{
	TransactionId *sub_xids;
	TransactionId max_xid;
	int			i;

	TransactionIdCommit(xid);


	sub_xids = (TransactionId *) &(xlrec->xnodes[xlrec->nrels]);
	TransactionIdCommitTree(xlrec->nsubxacts, sub_xids);


	max_xid = xid;
	for (i = 0; i < xlrec->nsubxacts; i++)
	{
		if (TransactionIdPrecedes(max_xid, sub_xids[i]))
			max_xid = sub_xids[i];
	}
	if (TransactionIdFollowsOrEquals(max_xid,
									 ShmemVariableCache->nextXid))
	{
		ShmemVariableCache->nextXid = max_xid;
		TransactionIdAdvance(ShmemVariableCache->nextXid);
	}


	for (i = 0; i < xlrec->nrels; i++)
	{
		XLogDropRelation(xlrec->xnodes[i]);
		smgrdounlink(smgropen(xlrec->xnodes[i]), false, true);
	}
}
