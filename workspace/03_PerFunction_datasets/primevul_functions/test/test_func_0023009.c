int ha_maria::start_stmt(THD *thd, thr_lock_type lock_type)
{
  TRN *trn;
  if (file->s->base.born_transactional)
  {
    trn= THD_TRN;
    DBUG_ASSERT(trn);
    DBUG_ASSERT(trnman_has_locked_tables(trn));
    DBUG_ASSERT(lock_type != TL_UNLOCK);
    DBUG_ASSERT(file->trn == trn);


    trnman_new_statement(trn);

#ifdef EXTRA_DEBUG
    if (!(trnman_get_flags(trn) & TRN_STATE_INFO_LOGGED) &&
        trnman_get_flags(trn) & TRN_STATE_TABLES_CAN_CHANGE)
    {
      trnman_set_flags(trn, trnman_get_flags(trn) | TRN_STATE_INFO_LOGGED);
      (void) translog_log_debug_info(trn, LOGREC_DEBUG_INFO_QUERY,
                                     (uchar*) thd->query(),
                                     thd->query_length());
    }
#endif
  }
  return 0;
}
