int ha_savepoint(THD *thd, SAVEPOINT *sv)
{
#ifdef WITH_WSREP


  if (WSREP_EMULATE_BINLOG(thd) && wsrep_thd_is_local(thd))
  {
    wsrep_register_binlog_handler(thd, thd->in_multi_stmt_transaction_mode());
  }
#endif
  int error=0;
  THD_TRANS *trans= (thd->in_sub_stmt ? &thd->transaction.stmt :
                                        &thd->transaction.all);
  Ha_trx_info *ha_info= trans->ha_list;
  DBUG_ENTER("ha_savepoint");

  for (; ha_info; ha_info= ha_info->next())
  {
    int err;
    handlerton *ht= ha_info->ht();
    DBUG_ASSERT(ht);
    if (! ht->savepoint_set)
    {
      my_error(ER_CHECK_NOT_IMPLEMENTED, MYF(0), "SAVEPOINT");
      error=1;
      break;
    }
    if ((err= ht->savepoint_set(ht, thd, (uchar *)(sv+1)+ht->savepoint_offset)))
    {
      my_error(ER_GET_ERRNO, MYF(0), err, hton_name(ht)->str);
      error=1;
    }
    status_var_increment(thd->status_var.ha_savepoint_count);
  }


  sv->ha_list= trans->ha_list;

  DBUG_RETURN(error);
}
