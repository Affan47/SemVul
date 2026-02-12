void multi_update::abort_result_set()
{

  if (unlikely(error_handled ||
               (!thd->transaction.stmt.modified_non_trans_table && !updated)))
    return;


  if (updated)
    query_cache_invalidate3(thd, update_tables, 1);


  if (! trans_safe)
  {
    DBUG_ASSERT(thd->transaction.stmt.modified_non_trans_table);
    if (do_update && table_count > 1)
    {

      (void) do_updates();
    }
  }
  if (thd->transaction.stmt.modified_non_trans_table)
  {


    if (WSREP_EMULATE_BINLOG(thd) || mysql_bin_log.is_open())
    {


      int errcode= query_error_code(thd, thd->killed == NOT_KILLED);

      (void)thd->binlog_query(THD::ROW_QUERY_TYPE,
                        thd->query(), thd->query_length(),
                        transactional_tables, FALSE, FALSE, errcode);
    }
    thd->transaction.all.modified_non_trans_table= TRUE;
  }
  thd->transaction.all.m_unsafe_rollback_flags|=
    (thd->transaction.stmt.m_unsafe_rollback_flags & THD_TRANS::DID_WAIT);
  DBUG_ASSERT(trans_safe || !updated || thd->transaction.stmt.modified_non_trans_table);
}
