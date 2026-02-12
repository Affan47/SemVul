THR_LOCK_DATA **ha_maria::store_lock(THD *thd,
                                     THR_LOCK_DATA **to,
                                     enum thr_lock_type lock_type)
{

  DBUG_ASSERT(lock_type != TL_UNLOCK &&
              (lock_type == TL_IGNORE || file->lock.type == TL_UNLOCK));
  if (lock_type != TL_IGNORE && file->lock.type == TL_UNLOCK)
  {
    const enum enum_sql_command sql_command= thd->lex->sql_command;


    if (lock_type <= TL_READ_HIGH_PRIORITY &&
        !thd->is_current_stmt_binlog_format_row() &&
        (sql_command != SQLCOM_SELECT &&
         sql_command != SQLCOM_LOCK_TABLES) &&
        (thd->variables.option_bits & OPTION_BIN_LOG) &&
        mysql_bin_log.is_open())
      lock_type= TL_READ_NO_INSERT;
    else if (lock_type == TL_WRITE_CONCURRENT_INSERT)
    {
      const enum enum_duplicates duplicates= thd->lex->duplicates;


      if ((file->state->records == 0) ||
          (sql_command == SQLCOM_INSERT_SELECT && duplicates == DUP_UPDATE) ||
          (sql_command == SQLCOM_LOAD && duplicates == DUP_REPLACE))
        lock_type= TL_WRITE;
    }
    file->lock.type= lock_type;
  }
  *to++= &file->lock;
  return to;
}
