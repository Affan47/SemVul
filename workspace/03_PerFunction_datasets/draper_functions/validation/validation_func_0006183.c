ha_update_row(const uchar *old_data, uchar *new_data)
{
  int error;
  Log_func *log_func= Update_rows_log_event::binlog_row_logging_function;


  DBUG_ASSERT(new_data == table->record[0]);
  DBUG_ASSERT(old_data == table->record[1]);

  MYSQL_UPDATE_ROW_START(table_share->db.str, table_share->table_name.str);
  mark_trx_read_write();

  error= update_row(old_data, new_data);
  MYSQL_UPDATE_ROW_DONE(error);
  if (unlikely(error))
    return error;
  if (unlikely(error= binlog_log_row(table, old_data, new_data, log_func)))
    return error;
  return 0;
}
