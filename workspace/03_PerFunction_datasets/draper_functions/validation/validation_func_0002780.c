__repmgr_site_config_pp(dbsite, which, value)
	DB_SITE *dbsite;
	u_int32_t which;
	u_int32_t value;
{
	DB_THREAD_INFO *ip;
	ENV *env;
	int ret;

	env = dbsite->env;

	ENV_ENTER(env, ip);
	ret = __repmgr_site_config_int(dbsite, which, value);
	ENV_LEAVE(env, ip);

	return (ret);
}
