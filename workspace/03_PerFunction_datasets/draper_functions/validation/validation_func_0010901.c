dvb_database_sqlite_sqlite_database_throw_last_error_reset (DVBdatabasesqliteSqliteDatabase* self, sqlite3_stmt* stmnt, GError** error) {
	sqlite3_stmt* _tmp0_ = NULL;
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (stmnt != NULL);
	_tmp0_ = stmnt;
	sqlite3_reset (_tmp0_);
	dvb_database_sqlite_sqlite_database_throw_last_error (self, NULL, &_inner_error_);
	if (_inner_error_ != NULL) {
		if (_inner_error_->domain == DVB_DATABASE_SQL_ERROR) {
			g_propagate_error (error, _inner_error_);
			return;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
	}
}
