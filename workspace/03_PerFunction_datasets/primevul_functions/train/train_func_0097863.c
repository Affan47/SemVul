static int _pgsql_exec(void *conn, const char *cmd, char *value, size_t size,
		       size_t *value_len, const sasl_utils_t *utils)
{
    PGresult *result;
    int row_count;
    ExecStatusType status;


    result = PQexec(conn, cmd);


    status = PQresultStatus(result);
    if (status == PGRES_COMMAND_OK) {

	PQclear(result);
	return 0;
    }
    else if (status != PGRES_TUPLES_OK) {

	utils->log(utils->conn, SASL_LOG_DEBUG, "sql plugin: %s ",
		   PQresStatus(status));
	PQclear(result);
	return -1;
    }


    row_count = PQntuples(result);
    if (!row_count) {

	utils->log(utils->conn, SASL_LOG_NOTE, "sql plugin: no result found");
	PQclear(result);
	return -1;
    }
    if (row_count > 1) {
	utils->log(utils->conn, SASL_LOG_WARN,
		   "sql plugin: found duplicate row for query %s", cmd);
    }


    if (value) {
	strncpy(value, PQgetvalue(result,0,0), size-2);
	value[size-1] = '\0';
	if (value_len) *value_len = strlen(value);
    }


    PQclear(result);
    return 0;
}
