int ha_maria::implicit_commit(THD *thd, bool new_trn)
{
#ifndef MARIA_CANNOT_ROLLBACK
#error this method should be removed
#endif
  TRN *trn;
  int error;
  uint locked_tables;
  extern my_bool plugins_are_initialized;
  MARIA_HA *used_tables, *trn_next;
  DBUG_ENTER("ha_maria::implicit_commit");

  if (!maria_hton || !plugins_are_initialized || !(trn= THD_TRN))
    DBUG_RETURN(0);
  if (!new_trn && (thd->locked_tables_mode == LTM_LOCK_TABLES ||
                   thd->locked_tables_mode == LTM_PRELOCKED_UNDER_LOCK_TABLES))
  {


    DBUG_PRINT("info", ("locked_tables, skipping"));
    DBUG_RETURN(0);
  }


  locked_tables= trnman_has_locked_tables(trn);
  trnman_reset_locked_tables(trn, 0);
  relink_trn_used_instances(&used_tables, trn);

  error= 0;
  if (unlikely(ma_commit(trn)))
    error= HA_ERR_COMMIT_ERROR;
  if (!new_trn)
  {
    reset_thd_trn(thd, used_tables);
    goto end;
  }


  trn= trnman_new_trn(& thd->transaction->wt);
  thd_set_ha_data(thd, maria_hton, trn);
  if (unlikely(trn == NULL))
  {
    reset_thd_trn(thd, used_tables);
    error= HA_ERR_OUT_OF_MEM;
    goto end;
  }


  for (MARIA_HA *handler= used_tables; handler ;
       handler= trn_next)
  {
    trn_next= handler->trn_next;
    DBUG_ASSERT(handler->s->base.born_transactional);


    if (handler->s->lock_key_trees)
    {

      if (_ma_setup_live_state(handler))
        error= HA_ERR_OUT_OF_MEM;
    }
    else
      _ma_set_trn_for_table(handler, trn);
  }

  trnman_reset_locked_tables(trn, locked_tables);

end:
  DBUG_RETURN(error);
}
