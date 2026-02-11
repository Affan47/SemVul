__env_failchk_pp(dbenv, flags)
	DB_ENV *dbenv;
	u_int32_t flags;
{
	DB_THREAD_INFO *ip;
	ENV *env;
	int ret;

	env = dbenv->env;

	ENV_ILLEGAL_BEFORE_OPEN(env, "DB_ENV->failchk");


	if (!ALIVE_ON(env)) {
		__db_errx(env, DB_STR("1503",
	"DB_ENV->failchk requires DB_ENV->is_alive be configured"));
		return (EINVAL);
	}

	if (flags != 0)
		return (__db_ferr(env, "DB_ENV->failchk", 0));

	ENV_ENTER(env, ip);
	FAILCHK_THREAD(env, ip);
	ret = __env_failchk_int(dbenv);
	ENV_LEAVE(env, ip);
	return (ret);
}
