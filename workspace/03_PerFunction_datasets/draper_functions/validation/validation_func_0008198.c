_cl5CompactDBs()
{
#if 1000*DB_VERSION_MAJOR + 100*DB_VERSION_MINOR >= 4400
	int rc;
	Object *fileObj = NULL;
	CL5DBFile *dbFile = NULL;
	DB *db = NULL;
	DB_TXN *txnid = NULL;
	DB_COMPACT c_data = {0};

	PR_Lock (s_cl5Desc.dbTrim.lock);
	rc = TXN_BEGIN(s_cl5Desc.dbEnv, NULL, &txnid, 0);
	if (rc) {
		slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name_cl,
		    "_cl5CompactDBs: failed to begin transaction; db error - %d %s\n",
		    rc, db_strerror(rc));
		goto bail;
	}
	for (fileObj = objset_first_obj(s_cl5Desc.dbFiles);
	     fileObj;
	     fileObj = objset_next_obj(s_cl5Desc.dbFiles, fileObj)) {
		dbFile = (CL5DBFile*)object_get_data(fileObj);
		if (!dbFile) {
			continue;
		}
		db = dbFile->db;
		rc = db->compact(db, txnid, NULL, NULL,
		                 &c_data, DB_FREE_SPACE, NULL);
		if (rc) {
			slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name_cl,
			    "_cl5CompactDBs: failed to compact %s; db error - %d %s\n",
			    dbFile->replName, rc, db_strerror(rc));
			goto bail;
		}
		slapi_log_error(SLAPI_LOG_REPL, repl_plugin_name_cl,
		        "_cl5CompactDBs: %s - %d pages freed\n",
		        dbFile->replName, c_data.compact_pages_free);
	}
bail:
	if (fileObj) {
		object_release(fileObj);
	}
	if (rc) {
		rc = TXN_ABORT (txnid);
		if (rc) {
			slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name_cl,
			    "_cl5CompactDBs: failed to abort transaction; db error - %d %s\n",
			    rc, db_strerror(rc));
		}
	} else {
		rc = TXN_COMMIT (txnid, 0);
		if (rc) {
			slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name_cl,
			    "_cl5CompactDBs: failed to commit transaction; db error - %d %s\n",
			    rc, db_strerror(rc));
		}
	}
	PR_Unlock (s_cl5Desc.dbTrim.lock);

#endif
	return;
}
