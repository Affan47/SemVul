__env_print_stats(env, flags)
	ENV *env;
	u_int32_t flags;
{
	REGENV *renv;
	REGINFO *infop;
	char time_buf[CTIME_BUFLEN];

	infop = env->reginfo;
	renv = infop->primary;

	if (LF_ISSET(DB_STAT_ALL)) {
		__db_msg(env, "%s", DB_GLOBAL(db_line));
		__db_msg(env, "Default database environment information:");
	}
	STAT_HEX("Magic number", renv->magic);
	STAT_LONG("Panic value", renv->panic);
	__db_msg(env, "%d.%d.%d\tEnvironment version",
	    renv->majver, renv->minver, renv->patchver);
	STAT_LONG("Btree version", DB_BTREEVERSION);
	STAT_LONG("Hash version", DB_HASHVERSION);
	STAT_LONG("Lock version", DB_LOCKVERSION);
	STAT_LONG("Log version", DB_LOGVERSION);
	STAT_LONG("Queue version", DB_QAMVERSION);
	STAT_LONG("Sequence version", DB_SEQUENCE_VERSION);
	STAT_LONG("Txn version", DB_TXNVERSION);
	__db_msg(env,
	    "%.24s\tCreation time", __os_ctime(&renv->timestamp, time_buf));
	STAT_HEX("Environment ID", renv->envid);
	__mutex_print_debug_single(env,
	    "Primary region allocation and reference count mutex",
	    renv->mtx_regenv, flags);
	STAT_LONG("References", renv->refcnt);
	__db_dlbytes(env, "Current region size",
	    (u_long)0, (u_long)0, (u_long)infop->rp->size);
	__db_dlbytes(env, "Maximum region size",
	    (u_long)0, (u_long)0, (u_long)infop->rp->max);

	return (0);
}
