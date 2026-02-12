bool multi_update::send_eof()
{
  char buff[STRING_BUFFER_USUAL_SIZE];
  ulonglong id;
  killed_state killed_status= NOT_KILLED;
  DBUG_ENTER("multi_update::send_eof");
  THD_STAGE_INFO(thd, stage_updating_reference_tables);


  int local_error= thd->is_error();
  if (likely(!local_error))
    local_error = (table_count) ? do_updates() : 0;


  killed_status= (local_error == 0) ? NOT_KILLED : thd->killed;
  THD_STAGE_INFO(thd, stage_end);


  if (updated)
  {
    query_cache_invalidate3(thd, update_tables, 1);
  }


  if (thd->transaction.stmt.modified_non_trans_table)
    thd->transaction.all.modified_non_trans_table= TRUE;
  thd->transaction.all.m_unsafe_rollback_flags|=
    (thd->transaction.stmt.m_unsafe_rollback_flags & THD_TRANS::DID_WAIT);

  if (likely(local_error == 0 ||
             thd->transaction.stmt.modified_non_trans_table))
  {
    if (WSREP_EMULATE_BINLOG(thd) || mysql_bin_log.is_open())
    {
      int errcode= 0;
      if (likely(local_error == 0))
        thd->clear_error();
      else
        errcode= query_error_code(thd, killed_status == NOT_KILLED);

      bool force_stmt= false;
      for (TABLE *table= all_tables->table; table; table= table->next)
      {
        if (table->versioned(VERS_TRX_ID))
        {
          force_stmt= true;
          break;
        }
      }
      enum_binlog_format save_binlog_format;
      save_binlog_format= thd->get_current_stmt_binlog_format();
      if (force_stmt)
        thd->set_current_stmt_binlog_format_stmt();

      if (thd->binlog_query(THD::ROW_QUERY_TYPE, thd->query(),
                            thd->query_length(), transactional_tables, FALSE,
                            FALSE, errcode) > 0)
	local_error= 1;
      thd->set_current_stmt_binlog_format(save_binlog_format);
    }
  }
  DBUG_ASSERT(trans_safe || !updated ||
              thd->transaction.stmt.modified_non_trans_table);

  if (likely(local_error != 0))
    error_handled= TRUE;

  if (unlikely(local_error > 0))
  {

    my_message(ER_UNKNOWN_ERROR, "An error occurred in multi-table update",
	       MYF(0));
    DBUG_RETURN(TRUE);
  }

  if (!thd->lex->analyze_stmt)
  {
    id= thd->arg_of_last_insert_id_function ?
    thd->first_successful_insert_id_in_prev_stmt : 0;
    my_snprintf(buff, sizeof(buff), ER_THD(thd, ER_UPDATE_INFO),
                (ulong) found, (ulong) updated, (ulong) thd->cuted_fields);
    ::my_ok(thd, (thd->client_capabilities & CLIENT_FOUND_ROWS) ? found : updated,
            id, buff);
  }
  DBUG_RETURN(FALSE);
}
