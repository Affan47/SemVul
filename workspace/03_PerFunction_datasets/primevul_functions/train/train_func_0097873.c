static int _mysql_exec(void *conn, const char *cmd, char *value, size_t size,
		       size_t *value_len, const sasl_utils_t *utils)
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    int row_count, len;

    len = strlen(cmd);

    if (cmd[len-1] == ';') len--;


    (void)mysql_real_query(conn, cmd, len);

    if(mysql_errno(conn)) {
        utils->log(utils->conn, SASL_LOG_ERR, "sql query failed: %s",
		   mysql_error(conn));
	return -1;
    }


    if (!mysql_field_count(conn)) {

	return 0;
    }


    result = mysql_store_result(conn);
    if (!result) {

	utils->log(utils->conn, SASL_LOG_NOTE, "sql plugin: no result found");
	return -1;
    }


    row_count = mysql_num_rows(result);
    if (!row_count) {

	mysql_free_result(result);
	utils->log(utils->conn, SASL_LOG_NOTE, "sql plugin: no result found");
	return -1;
    }
    if (row_count > 1) {
	utils->log(utils->conn, SASL_LOG_WARN,
		   "sql plugin: found duplicate row for query %s", cmd);
    }


    row = mysql_fetch_row(result);
    if (!row || !row[0]) {

	utils->log(utils->conn, SASL_LOG_NOTE, "sql plugin: no result found");
	mysql_free_result(result);
	return -1;
    }
    if (value) {
	strncpy(value, row[0], size-2);
	value[size-1] = '\0';
	if (value_len) *value_len = strlen(value);
    }


    mysql_free_result(result);
    mysql_next_result(conn);

    return 0;
}
