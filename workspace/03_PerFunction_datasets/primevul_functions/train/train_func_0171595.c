int ha_rollback_trans(THD *thd, bool all)
{
  int error=0;
  THD_TRANS *trans=all ? &thd->transaction.all : &thd->transaction.stmt;
  Ha_trx_info *ha_info= trans->ha_list, *ha_info_next;


  bool is_real_trans=all || thd->transaction.all.ha_list == 0;
  DBUG_ENTER("ha_rollback_trans");


  DBUG_ASSERT(thd->transaction.stmt.ha_list == NULL ||
              trans == &thd->transaction.stmt);

#ifdef HAVE_REPLICATION
  if (is_real_trans)
  {


    DBUG_ASSERT(!(thd->rgi_slave && thd->rgi_slave->did_mark_start_commit));
    if (thd->rgi_slave && thd->rgi_slave->did_mark_start_commit)
      thd->rgi_slave->unmark_start_commit();
  }
#endif

  if (thd->in_sub_stmt)
  {
    DBUG_ASSERT(0);


    if (!all)
      DBUG_RETURN(0);
    my_error(ER_COMMIT_NOT_ALLOWED_IN_SF_OR_TRG, MYF(0));
    DBUG_RETURN(1);
  }

#ifdef WITH_WSREP
  (void) wsrep_before_rollback(thd, all);
#endif
  if (ha_info)
  {

    if (is_real_trans)
      thd->stmt_map.close_transient_cursors();

    for (; ha_info; ha_info= ha_info_next)
    {
      int err;
      handlerton *ht= ha_info->ht();
      if ((err= ht->rollback(ht, thd, all)))
      {
        my_error(ER_ERROR_DURING_ROLLBACK, MYF(0), err);
        error=1;
#ifdef WITH_WSREP
        WSREP_WARN("handlerton rollback failed, thd %lld %lld conf %d SQL %s",
                   thd->thread_id, thd->query_id, thd->wsrep_trx().state(),
                   thd->query());
#endif
      }
      status_var_increment(thd->status_var.ha_rollback_count);
      ha_info_next= ha_info->next();
      ha_info->reset();
    }
    trans->ha_list= 0;
    trans->no_2pc=0;
  }

#ifdef WITH_WSREP
  if (thd->is_error())
  {
    WSREP_DEBUG("ha_rollback_trans(%lld, %s) rolled back: %s: %s; is_real %d",
                thd->thread_id, all?"TRUE":"FALSE", wsrep_thd_query(thd),
                thd->get_stmt_da()->message(), is_real_trans);
  }
  (void) wsrep_after_rollback(thd, all);
#endif

  if (is_real_trans)
  {


    if (thd->transaction_rollback_request &&
        thd->transaction.xid_state.is_explicit_XA())
      thd->transaction.xid_state.set_error(thd->get_stmt_da()->sql_errno());

    thd->has_waiter= false;
    thd->transaction.cleanup();
  }
  if (all)
    thd->transaction_rollback_request= FALSE;


  if (is_real_trans && thd->transaction.all.modified_non_trans_table &&
      !thd->slave_thread && thd->killed < KILL_CONNECTION)
    push_warning(thd, Sql_condition::WARN_LEVEL_WARN,
                 ER_WARNING_NOT_COMPLETE_ROLLBACK,
                 ER_THD(thd, ER_WARNING_NOT_COMPLETE_ROLLBACK));
#ifdef HAVE_REPLICATION
  repl_semisync_master.wait_after_rollback(thd, all);
#endif
  DBUG_RETURN(error);
}
