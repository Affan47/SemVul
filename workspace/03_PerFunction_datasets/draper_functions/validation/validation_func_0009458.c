abort_result_set() {

  DBUG_ENTER("select_insert::abort_result_set");


  if (table)
  {
    bool changed, transactional_table;


    if (thd->locked_tables_mode <= LTM_LOCK_TABLES)
      table->file->ha_end_bulk_insert();


    changed= (info.copied || info.deleted || info.updated);
    transactional_table= table->file->has_transactions();
    if (thd->transaction.stmt.modified_non_trans_table)
    {
        if (!can_rollback_data())
          thd->transaction.all.modified_non_trans_table= TRUE;

        if (mysql_bin_log.is_open())
        {
          int errcode= query_error_code(thd, thd->killed == THD::NOT_KILLED);

          (void) thd->binlog_query(THD::ROW_QUERY_TYPE, thd->query(),
                                   thd->query_length(),
                                   transactional_table, FALSE, FALSE, errcode);
        }
	if (changed)
	  query_cache_invalidate3(thd, table, 1);
    }
    DBUG_ASSERT(transactional_table || !changed ||
		thd->transaction.stmt.modified_non_trans_table);
    table->file->ha_release_auto_increment();
  }

  DBUG_VOID_RETURN;
}
