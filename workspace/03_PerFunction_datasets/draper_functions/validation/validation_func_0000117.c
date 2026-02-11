__db_msg(const ENV *env, const char *fmt, ...)
#else
__db_msg(env, fmt, va_alist)
	const ENV *env;
	const char *fmt;
	va_dcl
#endif
{
	DB_ENV *dbenv;

	dbenv = env == NULL ? NULL : env->dbenv;

	DB_REAL_MSG(dbenv, fmt);
}
