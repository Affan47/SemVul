__repmgr_try_one(env, eid, refresh)
	ENV *env;
	int eid;
	int refresh;
{
	DB_REP *db_rep;
	REPMGR_SITE *site;
	REPMGR_RUNNABLE *th;
	int ret;

	db_rep = env->rep_handle;
	DB_ASSERT(env, IS_VALID_EID(eid));
	site = SITE_FROM_EID(eid);
	th = site->connector;
	if (th == NULL) {
		if ((ret = __os_malloc(env, sizeof(REPMGR_RUNNABLE), &th)) != 0)
			return (ret);
		site->connector = th;
	} else if (th->finished) {
		if ((ret = __repmgr_thread_join(th)) != 0)
			return (ret);
	} else {
		RPRINT(env, (env, DB_VERB_REPMGR_MISC,
		  "eid %lu previous connector thread still running; will retry",
		    (u_long)eid));
		return (__repmgr_schedule_connection_attempt(env,
			eid, refresh));
	}

	site->state = SITE_CONNECTING;

	th->run = __repmgr_connector_thread;
	th->args.conn_th.eid = eid;


	th->args.conn_th.flags = refresh ? CONNECT_F_REFRESH : 0;
	if ((ret = __repmgr_thread_start(env, th)) != 0) {
		__os_free(env, th);
		site->connector = NULL;
	}
	return (ret);
}
