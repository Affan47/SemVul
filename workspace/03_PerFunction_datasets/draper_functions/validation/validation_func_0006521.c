__dbc_get_pp(dbc, key, data, flags)
	DBC *dbc;
	DBT *key, *data;
	u_int32_t flags;
{
	DB *dbp;
	DB_THREAD_INFO *ip;
	ENV *env;
	int ignore_lease, ret;

	dbp = dbc->dbp;
	env = dbp->env;

	ignore_lease = LF_ISSET(DB_IGNORE_LEASE) ? 1 : 0;
	LF_CLR(DB_IGNORE_LEASE);
	if ((ret = __dbc_get_arg(dbc, key, data, flags)) != 0) {
		__dbt_userfree(env, key, NULL, data);
		return (ret);
	}

	ENV_ENTER(env, ip);

	DEBUG_LREAD(dbc, dbc->txn, "DBcursor->get",
	    flags == DB_SET || flags == DB_SET_RANGE ? key : NULL, NULL, flags);
	ret = __dbc_get(dbc, key, data, flags);


	if (ret == 0 &&
	    IS_REP_MASTER(env) && IS_USING_LEASES(env) && !ignore_lease)
		ret = __rep_lease_check(env, 1);

	ENV_LEAVE(env, ip);
	__dbt_userfree(env, key, NULL, data);
	return (ret);
}
