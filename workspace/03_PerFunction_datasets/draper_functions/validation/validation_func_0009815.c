CDB___txn_regop_read(recbuf, argpp)
	void *recbuf;
	__txn_regop_args **argpp;
{
	__txn_regop_args *argp;
	u_int8_t *bp;
	int ret;

	ret = CDB___os_malloc(sizeof(__txn_regop_args) +
	    sizeof(DB_TXN), NULL, &argp);
	if (ret != 0)
		return (ret);
	argp->txnid = (DB_TXN *)&argp[1];
	bp = recbuf;
	memcpy(&argp->type, bp, sizeof(argp->type));
	bp += sizeof(argp->type);
	memcpy(&argp->txnid->txnid,  bp, sizeof(argp->txnid->txnid));
	bp += sizeof(argp->txnid->txnid);
	memcpy(&argp->prev_lsn, bp, sizeof(DB_LSN));
	bp += sizeof(DB_LSN);
	memcpy(&argp->opcode, bp, sizeof(argp->opcode));
	bp += sizeof(argp->opcode);
	*argpp = argp;
	return (0);
}
