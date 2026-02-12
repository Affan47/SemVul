int ha_maria::extra(enum ha_extra_function operation)
{
  int tmp;
  TRN *old_trn= file->trn;
  if ((specialflag & SPECIAL_SAFE_MODE) && operation == HA_EXTRA_KEYREAD)
    return 0;
#ifdef NOT_USED
  if (operation == HA_EXTRA_MMAP && !opt_maria_use_mmap)
    return 0;
#endif
  if (operation == HA_EXTRA_WRITE_CACHE && has_long_unique())
    return 0;


  if (file->s->now_transactional && table->in_use &&
      (operation == HA_EXTRA_PREPARE_FOR_DROP ||
       operation == HA_EXTRA_PREPARE_FOR_RENAME ||
       operation == HA_EXTRA_PREPARE_FOR_FORCED_CLOSE))
  {
    THD *thd= table->in_use;
    file->trn= THD_TRN;
  }
  DBUG_ASSERT(file->s->base.born_transactional || file->trn == 0 ||
              file->trn == &dummy_transaction_object);

  tmp= maria_extra(file, operation, 0);


  file->trn= old_trn;
  return tmp;
}
