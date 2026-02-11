TransactionIdDidCommit(TransactionId transactionId)
{
	XidStatus	xidstatus;

	xidstatus = TransactionLogFetch(transactionId);


	if (xidstatus == TRANSACTION_STATUS_COMMITTED)
		return true;


	if (xidstatus == TRANSACTION_STATUS_SUB_COMMITTED)
	{
		TransactionId parentXid;

		if (TransactionIdPrecedes(transactionId, TransactionXmin))
			return false;
		parentXid = SubTransGetParent(transactionId);
		if (!TransactionIdIsValid(parentXid))
		{
			elog(WARNING, "no pg_subtrans entry for subcommitted XID %u",
				 transactionId);
			return false;
		}
		return TransactionIdDidCommit(parentXid);
	}


	return false;
}
