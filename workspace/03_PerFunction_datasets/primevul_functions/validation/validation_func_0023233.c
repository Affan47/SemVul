open_system_tables_for_read(THD *thd, TABLE_LIST *table_list,
                            Open_tables_backup *backup)
{
  Query_tables_list query_tables_list_backup;
  LEX *lex= thd->lex;
  DBUG_ENTER("open_system_tables_for_read");


  lex->reset_n_backup_query_tables_list(&query_tables_list_backup);
  thd->reset_n_backup_open_tables_state(backup);
  thd->lex->sql_command= SQLCOM_SELECT;


  if (open_and_lock_tables(thd, table_list, FALSE,
                           (MYSQL_OPEN_IGNORE_FLUSH |
                            (table_list->lock_type < TL_WRITE_ALLOW_WRITE ?
                             MYSQL_LOCK_IGNORE_TIMEOUT : 0))))
  {
    lex->restore_backup_query_tables_list(&query_tables_list_backup);
    thd->restore_backup_open_tables_state(backup);
    DBUG_RETURN(TRUE);
  }

  for (TABLE_LIST *tables= table_list; tables; tables= tables->next_global)
  {
    DBUG_ASSERT(tables->table->s->table_category == TABLE_CATEGORY_SYSTEM);
    tables->table->use_all_columns();
  }
  lex->restore_backup_query_tables_list(&query_tables_list_backup);

  DBUG_RETURN(FALSE);
}
