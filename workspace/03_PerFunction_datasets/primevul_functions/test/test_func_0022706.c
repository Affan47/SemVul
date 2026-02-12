void Locked_tables_list::unlink_from_list(THD *thd,
                                          TABLE_LIST *table_list,
                                          bool remove_from_locked_tables)
{


  if (thd->locked_tables_mode != LTM_LOCK_TABLES &&
      thd->locked_tables_mode != LTM_PRELOCKED_UNDER_LOCK_TABLES)
    return;


  DBUG_ASSERT(table_list->table->pos_in_locked_tables == table_list);


  table_list->table->pos_in_locked_tables= NULL;


  table_list->table= NULL;


  if (remove_from_locked_tables)
  {
    *table_list->prev_global= table_list->next_global;
    if (table_list->next_global == NULL)
      m_locked_tables_last= table_list->prev_global;
    else
      table_list->next_global->prev_global= table_list->prev_global;
    m_locked_tables_count--;
  }
}
