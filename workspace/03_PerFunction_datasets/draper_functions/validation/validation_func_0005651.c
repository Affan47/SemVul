CDB___db_ovref_print(notused1, dbtp, lsnp, notused2, notused3)
	DB_ENV *notused1;
	DBT *dbtp;
	DB_LSN *lsnp;
	int notused2;
	void *notused3;
{
	__db_ovref_args *argp;
	u_int32_t i;
	u_int ch;
	int ret;

	i = 0;
	ch = 0;
	notused1 = NULL;
	notused2 = 0;
	notused3 = NULL;

	if ((ret = CDB___db_ovref_read(dbtp->data, &argp)) != 0)
		return (ret);
	printf("[%lu][%lu]db_ovref: rec: %lu txnid %lx prevlsn [%lu][%lu]\n",
	    (u_long)lsnp->file,
	    (u_long)lsnp->offset,
	    (u_long)argp->type,
	    (u_long)argp->txnid->txnid,
	    (u_long)argp->prev_lsn.file,
	    (u_long)argp->prev_lsn.offset);
	printf("\tfileid: %lu\n", (u_long)argp->fileid);
	printf("\tpgno: %lu\n", (u_long)argp->pgno);
	printf("\tadjust: %ld\n", (long)argp->adjust);
	printf("\tlsn: [%lu][%lu]\n",
	    (u_long)argp->lsn.file, (u_long)argp->lsn.offset);
	printf("\n");
	CDB___os_free(argp, 0);
	return (0);
}
