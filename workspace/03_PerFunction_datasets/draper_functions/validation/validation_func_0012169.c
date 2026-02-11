__blob_del_all(dbp, txn, istruncate)
	DB *dbp;
	DB_TXN *txn;
	int istruncate;
{
#ifdef HAVE_64BIT_TYPES
	ENV *env;
	char *path;
	int close, isdir, ret;

	env = dbp->env;
	path = NULL;
	ret = 0;
	close = 0;

	if (dbp->blob_sub_dir == NULL) {
		if ((ret = __blob_make_sub_dir(env, &dbp->blob_sub_dir,
		    dbp->blob_file_id, dbp->blob_sdb_id)) != 0)
			goto err;
	}


	if (dbp->blob_sub_dir == NULL || dbp->blob_threshold == 0)
		goto err;

	if ((ret = __blob_get_dir(dbp, &path)) != 0)
		goto err;


	if (!istruncate) {
		if (dbp->blob_seq != NULL) {
			__seq_close(dbp->blob_seq, 0);
			dbp->blob_seq = NULL;
		}
		if (dbp->blob_meta_db != NULL) {
			__db_close(dbp->blob_meta_db, NULL, 0);
			dbp->blob_meta_db = NULL;
		}
	}


	if (__os_exists(env, path, &isdir) != 0)
		goto err;

	if ((ret = __blob_clean_dir(dbp, txn, path, istruncate)) != 0)
		goto err;

err:	if (path != NULL)
		__os_free(env, path);
	return (ret);

#else
        __db_errx(dbp->env, DB_STR("0220",
            "library build did not include support for blobs"));
        return (DB_OPNOTSUP);
#endif

}
