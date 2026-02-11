__blob_make_sub_dir(env, blob_sub_dir, file_id, db_id)
	ENV *env;
	char **blob_sub_dir;
	uintmax_t file_id;
	uintmax_t db_id;
{
	char fname[MAX_BLOB_PATH_SZ], dname[MAX_BLOB_PATH_SZ];
	int ret;
	size_t len;

	*blob_sub_dir = NULL;
	memset(fname, 0, MAX_BLOB_PATH_SZ);
	memset(dname, 0, MAX_BLOB_PATH_SZ);

	if (db_id == 0 && file_id == 0)
		return (0);


	if (db_id != 0)
		sprintf(dname,
		    "%s%llu", BLOB_DIR_PREFIX, (unsigned long long)db_id);
	sprintf(fname, "%s%llu", BLOB_DIR_PREFIX,
	    (unsigned long long)file_id);

	len = strlen(fname) + (db_id ? strlen(dname) : 0) + 3;
	if ((ret = __os_malloc(env, len, blob_sub_dir)) != 0)
		goto err;
	if (db_id != 0)
		sprintf(*blob_sub_dir, "%s%c%s%c", fname,
		    PATH_SEPARATOR[0], dname, PATH_SEPARATOR[0]);
	else
		sprintf(*blob_sub_dir, "%s%c", fname, PATH_SEPARATOR[0]);

	return (0);

err:	if (*blob_sub_dir != NULL)
		__os_free(env, *blob_sub_dir);

	return (ret);
}
