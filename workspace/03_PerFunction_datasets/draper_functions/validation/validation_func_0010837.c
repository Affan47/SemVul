dvb_database_sqlite_sqlite_database_get_version (DVBdatabasesqliteSqliteDatabase* self) {
	gint result = 0;
	gint version = 0;
	GError * _inner_error_ = NULL;
	g_return_val_if_fail (self != NULL, 0);
	version = 0;
	{
		gint _tmp0_ = 0;
		gint _tmp1_ = 0;
		_tmp1_ = dvb_database_sqlite_sqlite_database_simple_query_int (self, "PRAGMA user_version", &_inner_error_);
		_tmp0_ = _tmp1_;
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == DVB_DATABASE_SQL_ERROR) {
				goto __catch3_dvb_database_sql_error;
			}
			g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return 0;
		}
		version = _tmp0_;
	}
	goto __finally3;
	__catch3_dvb_database_sql_error:
	{
		GError* e = NULL;
		DVBLoggingLogger* _tmp2_ = NULL;
		GError* _tmp3_ = NULL;
		const gchar* _tmp4_ = NULL;
		e = _inner_error_;
		_inner_error_ = NULL;
		_tmp2_ = dvb_database_sqlite_sqlite_database_log;
		_tmp3_ = e;
		_tmp4_ = _tmp3_->message;
		dvb_logging_logger_error (_tmp2_, "SqliteDatabase.vala:105: %s", _tmp4_);
		_g_error_free0 (e);
	}
	__finally3:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return 0;
	}
	result = version;
	return result;
}
