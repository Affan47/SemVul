char* get_xtrabackup_info(MYSQL *connection)
{
	const char *uuid = get_backup_uuid(connection);
	char *server_version = read_mysql_one_value(connection, "SELECT VERSION()");

	static const size_t time_buf_size = 100;
	char buf_start_time[time_buf_size];
	char buf_end_time[time_buf_size];

	format_time(history_start_time, buf_start_time, time_buf_size);
	format_time(history_end_time, buf_end_time, time_buf_size);

	ut_a(uuid);
	ut_a(server_version);
	char* result = NULL;
	asprintf(&result,
		"uuid = %s\n"
		"name = %s\n"
		"tool_name = %s\n"
		"tool_command = %s\n"
		"tool_version = %s\n"
		"ibbackup_version = %s\n"
		"server_version = %s\n"
		"start_time = %s\n"
		"end_time = %s\n"
		"lock_time = %ld\n"
		"binlog_pos = %s\n"
		"innodb_from_lsn = " LSN_PF "\n"
		"innodb_to_lsn = " LSN_PF "\n"
		"partial = %s\n"
		"incremental = %s\n"
		"format = %s\n"
		"compact = %s\n"
		"compressed = %s\n"
		"encrypted = %s\n",
		uuid,
		opt_history ? opt_history : "",
		tool_name,
		tool_args,
		XTRABACKUP_VERSION,
		XTRABACKUP_VERSION,
		server_version,
		buf_start_time,
		buf_end_time,
		(long int)history_lock_time,
		mysql_binlog_position ?
			mysql_binlog_position : "",
		incremental_lsn,
		metadata_to_lsn,
		(xtrabackup_tables
		 || xtrabackup_tables_exclude
		 || xtrabackup_tables_file
		 || xtrabackup_databases
		 || xtrabackup_databases_exclude
		 || xtrabackup_databases_file) ? "Y" : "N",
		xtrabackup_incremental ? "Y" : "N",
		xb_stream_format_name[xtrabackup_stream_fmt],
		xtrabackup_compact ? "Y" : "N",
		xtrabackup_compress ? "compressed" : "N",
		xtrabackup_encrypt ? "Y" : "N");

	free(server_version);
	return result;
}
