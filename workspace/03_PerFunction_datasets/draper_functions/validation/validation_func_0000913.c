__os_umalloc(env, size, storep)
	ENV *env;
	size_t size;
	void *storep;
{
	DB_ENV *dbenv;
	int ret;

	dbenv = env == NULL ? NULL : env->dbenv;


	if (size == 0)
		++size;

	if (dbenv == NULL || dbenv->db_malloc == NULL) {
		if (DB_GLOBAL(j_malloc) != NULL)
			*(void **)storep = DB_GLOBAL(j_malloc)(size);
		else
			*(void **)storep = malloc(size);
		if (*(void **)storep == NULL) {


			if ((ret = __os_get_errno_ret_zero()) == 0) {
				ret = ENOMEM;
				__os_set_errno(ENOMEM);
			}
			__db_err(env, ret, DB_STR_A("0143", "malloc: %lu",
			    "%lu"), (u_long)size);
			return (ret);
		}
		return (0);
	}

	if ((*(void **)storep = dbenv->db_malloc(size)) == NULL) {
		__db_errx(env, DB_STR("0144",
		    "user-specified malloc function returned NULL"));
		return (ENOMEM);
	}

	return (0);
}
