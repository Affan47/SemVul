int ha_maria::external_lock(THD *thd, int lock_type)
{
  int result= 0, result2;
  DBUG_ENTER("ha_maria::external_lock");
  file->external_ref= (void*) table;


  if (file->s->base.born_transactional)
  {

    if (lock_type != F_UNLCK)
    {
      if (file->trn)
      {

        DBUG_PRINT("info",("file->trn: %p", file->trn));
        trnman_increment_locked_tables(file->trn);
      }

      if (!thd->transaction->on)
      {


        DBUG_PRINT("info", ("Disabling logging for table"));
        _ma_tmp_disable_logging_for_table(file, TRUE);
        file->autocommit= 0;
      }
      else
        file->autocommit= !(thd->variables.option_bits &
                            (OPTION_NOT_AUTOCOMMIT | OPTION_BEGIN));
#ifndef ARIA_HAS_TRANSACTIONS


      file->autocommit=1;
#endif
    }
    else
    {

      TRN *trn= (file->trn != &dummy_transaction_object && THD_TRN ? file->trn : 0);


      if (_ma_reenable_logging_for_table(file, TRUE))
        DBUG_RETURN(1);
      _ma_reset_trn_for_table(file);


      file->state= &file->s->state.state;
      if (trn)
      {
        DBUG_PRINT("info",
                   ("locked_tables: %u", trnman_has_locked_tables(trn)));
        DBUG_ASSERT(trnman_has_locked_tables(trn) > 0);
        if (trnman_has_locked_tables(trn) &&
            !trnman_decrement_locked_tables(trn))
        {


          DBUG_ASSERT(!thd->get_stmt_da()->is_sent() ||
                      thd->killed);


          if (file->autocommit)
          {
            if (ma_commit(trn))
              result= HA_ERR_COMMIT_ERROR;
            thd_set_ha_data(thd, maria_hton, 0);
          }
        }
        trnman_set_flags(trn, trnman_get_flags(trn) & ~ TRN_STATE_INFO_LOGGED);
      }
    }
  }
  if ((result2= maria_lock_database(file, !table->s->tmp_table ?
                                    lock_type : ((lock_type == F_UNLCK) ?
                                                 F_UNLCK : F_EXTRA_LCK))))
    result= result2;
  if (!file->s->base.born_transactional)
    file->state= &file->s->state.state;


  file->stack_end_ptr= &ha_thd()->mysys_var->stack_ends_here;
  DBUG_RETURN(result);
}
