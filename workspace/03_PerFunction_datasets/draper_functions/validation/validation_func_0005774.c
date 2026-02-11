syb_db_use(imp_dbh_t *imp_dbh, CS_CONNECTION *connection) {
	CS_COMMAND *cmd = syb_alloc_cmd(imp_dbh, connection);
	CS_RETCODE ret;
	CS_INT restype;
	char statement[255];
	int retval = 0;
	char *db;

	if (!cmd)
		return -1;

	if (DBIc_ACTIVE(imp_dbh) && imp_dbh->curr_db[0])
		db = imp_dbh->curr_db;
	else
		db = imp_dbh->database;

	sprintf(statement, "use %s", db);

	if (DBIc_DBISTATE(imp_dbh)->debug >= 3)
		PerlIO_printf(DBIc_LOGPIO(imp_dbh),
				"    syb_db_use() -> ct_command(%s)\n", statement);
	ret = ct_command(cmd, CS_LANG_CMD, statement, CS_NULLTERM, CS_UNUSED);
	if (ret != CS_SUCCEED) {
		warn("ct_command failed for '%s'", statement);
		return -1;
	}
	ret = ct_send(cmd);
	if (ret != CS_SUCCEED) {
		warn("ct_send failed for '%s'", statement);
		return -1;
	}
	while ((ret = ct_results(cmd, &restype)) == CS_SUCCEED) {
		if (DBIc_DBISTATE(imp_dbh)->debug >= 3)
			PerlIO_printf(DBIc_LOGPIO(imp_dbh),
					"    syb_db_use() -> ct_results(%d)\n", restype);
		if (restype == CS_CMD_FAIL) {
			warn("DBD::Sybase - can't change context to database %s\n",
					imp_dbh->database);
			retval = -1;
		}
	}
	ct_cmd_drop(cmd);

	return retval;
}
