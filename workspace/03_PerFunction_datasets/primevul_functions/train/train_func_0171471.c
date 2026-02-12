static int binlog_log_row_internal(TABLE* table,
                                   const uchar *before_record,
                                   const uchar *after_record,
                                   Log_func *log_func)
{
  bool error= 0;
  THD *const thd= table->in_use;


  if (likely(!(error= ((thd->get_binlog_table_maps() == 0 &&
                        write_locked_table_maps(thd))))))
  {


    bool const has_trans= thd->lex->sql_command == SQLCOM_CREATE_TABLE ||
      table->file->has_transactions();
    error= (*log_func)(thd, table, has_trans, before_record, after_record);
  }
  return error ? HA_ERR_RBR_LOGGING_FAILED : 0;
}
