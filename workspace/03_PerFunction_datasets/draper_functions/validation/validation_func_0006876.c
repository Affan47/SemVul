__repmgr_site_list_pp(dbenv, countp, listp)
	DB_ENV *dbenv;
	u_int *countp;
	DB_REPMGR_SITE **listp;
{
	ENV *env;
	DB_THREAD_INFO *ip;
	int ret;

	env = dbenv->env;

	ENV_ENTER(env, ip);
	ret = __repmgr_site_list_int(env, countp, listp);
	ENV_LEAVE(env, ip);

	return (ret);
}
