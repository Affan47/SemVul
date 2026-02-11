__db_noop_verify(env, dbtp, lsnp, notused2, lvhp)
	ENV *env;
	DBT *dbtp;
	DB_LSN *lsnp;
	db_recops notused2;
	void *lvhp;
{
	__db_noop_args *argp;
	DB_LOG_VRFY_INFO *lvh;
	int ret;

	COMPQUIET(notused2, DB_TXN_LOG_VERIFY);
	lvh = (DB_LOG_VRFY_INFO *)lvhp;

	if ((ret =
	    __db_noop_read(env, NULL, NULL, dbtp->data, &argp)) != 0)
		return (ret);

	LOG_VRFY_PROC(lvh, *lsnp, argp, argp->fileid);

out:

err:

	__os_free(env, argp);

	return (ret);
}
