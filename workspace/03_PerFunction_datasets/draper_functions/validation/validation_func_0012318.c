__env_backup_alloc(dbenv)
	DB_ENV *dbenv;
{
	ENV *env;

	env = dbenv->env;
	if (env->backup_handle != NULL)
		return (0);
	return (__os_calloc(env, 1,
	     sizeof(*env->backup_handle), &env->backup_handle));
}
