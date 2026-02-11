_tdb_transaction_prepare_commit(struct tdb_context *tdb)
{
	const struct tdb_methods *methods;
	enum TDB_ERROR ecode;

	if (tdb->tdb2.transaction == NULL) {
		return tdb_logerr(tdb, TDB_ERR_EINVAL, TDB_LOG_USE_ERROR,
				  "tdb_transaction_prepare_commit:"
				  " no transaction");
	}

	if (tdb->tdb2.transaction->prepared) {
		_tdb_transaction_cancel(tdb);
		return tdb_logerr(tdb, TDB_ERR_EINVAL, TDB_LOG_USE_ERROR,
				  "tdb_transaction_prepare_commit:"
				  " transaction already prepared");
	}

	if (tdb->tdb2.transaction->transaction_error) {
		_tdb_transaction_cancel(tdb);
		return tdb_logerr(tdb, TDB_ERR_EINVAL, TDB_LOG_ERROR,
				  "tdb_transaction_prepare_commit:"
				  " transaction error pending");
	}


	if (tdb->tdb2.transaction->nesting != 0) {
		return TDB_SUCCESS;
	}


	if (tdb->tdb2.transaction->blocks == NULL) {
		return TDB_SUCCESS;
	}

	methods = tdb->tdb2.transaction->io_methods;


	ecode = tdb_allrecord_upgrade(tdb, TDB_HASH_LOCK_START);
	if (ecode != TDB_SUCCESS) {
		return ecode;
	}


	ecode = tdb_lock_open(tdb, F_WRLCK, TDB_LOCK_WAIT|TDB_LOCK_NOCHECK);
	if (ecode != TDB_SUCCESS) {
		return ecode;
	}


	if (!(tdb->flags & TDB_NOSYNC)) {


		ecode = transaction_setup_recovery(tdb);
		if (ecode != TDB_SUCCESS) {
			return ecode;
		}
	}

	tdb->tdb2.transaction->prepared = true;


	if (tdb->file->map_size != tdb->tdb2.transaction->old_map_size) {
		tdb_len_t add;

		add = tdb->file->map_size - tdb->tdb2.transaction->old_map_size;

		tdb->file->map_size = tdb->tdb2.transaction->old_map_size;
		ecode = methods->expand_file(tdb, add);
		if (ecode != TDB_SUCCESS) {
			return ecode;
		}
	}


	return TDB_SUCCESS;
}
