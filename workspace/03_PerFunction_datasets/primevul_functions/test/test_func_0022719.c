void Locked_tables_list::
unlink_all_closed_tables(THD *thd, MYSQL_LOCK *lock, size_t reopen_count)
{

  if (lock)
    mysql_unlock_tables(thd, lock);


  if (reopen_count)
  {
    while (reopen_count--)
    {


      DBUG_ASSERT(thd->open_tables == m_reopen_array[reopen_count]->table);

      thd->open_tables->pos_in_locked_tables->table= NULL;
      thd->open_tables->pos_in_locked_tables= 0;

      close_thread_table(thd, &thd->open_tables);
    }
  }

  for (TABLE_LIST *table_list= m_locked_tables; table_list; table_list=
       table_list->next_global)
  {
    if (table_list->table == NULL)
    {

      *table_list->prev_global= table_list->next_global;
      if (table_list->next_global == NULL)
        m_locked_tables_last= table_list->prev_global;
      else
        table_list->next_global->prev_global= table_list->prev_global;
      m_locked_tables_count--;
    }
  }


  if (thd->lock && thd->lock->table_count == 0)
    unlock_locked_tables(thd);
}
