Locked_tables_list::unlock_locked_tables(THD *thd)
{
  DBUG_ASSERT(!thd->in_sub_stmt &&
              !(thd->state_flags & Open_tables_state::BACKUPS_AVAIL));


  if (thd->locked_tables_mode != LTM_LOCK_TABLES)
    return;

  for (TABLE_LIST *table_list= m_locked_tables;
       table_list; table_list= table_list->next_global)
  {


    if (table_list->table)
      table_list->table->pos_in_locked_tables= NULL;
  }
  thd->leave_locked_tables_mode();

  TRANSACT_TRACKER(clear_trx_state(thd, TX_LOCKED_TABLES));

  DBUG_ASSERT(thd->transaction.stmt.is_empty());
  close_thread_tables(thd);


  reset();
}
