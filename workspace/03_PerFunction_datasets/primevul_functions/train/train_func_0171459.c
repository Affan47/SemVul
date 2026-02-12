static int write_locked_table_maps(THD *thd)
{
  DBUG_ENTER("write_locked_table_maps");
  DBUG_PRINT("enter", ("thd:%p  thd->lock:%p "
                       "thd->extra_lock: %p",
                       thd, thd->lock, thd->extra_lock));

  DBUG_PRINT("debug", ("get_binlog_table_maps(): %d", thd->get_binlog_table_maps()));

  MYSQL_LOCK *locks[2];
  locks[0]= thd->extra_lock;
  locks[1]= thd->lock;
  my_bool with_annotate= IF_WSREP(!wsrep_fragments_certified_for_stmt(thd),
                                  true) &&
    thd->variables.binlog_annotate_row_events &&
    thd->query() && thd->query_length();

  for (uint i= 0 ; i < sizeof(locks)/sizeof(*locks) ; ++i )
  {
    MYSQL_LOCK const *const lock= locks[i];
    if (lock == NULL)
      continue;

    TABLE **const end_ptr= lock->table + lock->table_count;
    for (TABLE **table_ptr= lock->table ;
         table_ptr != end_ptr ;
         ++table_ptr)
    {
      TABLE *const table= *table_ptr;
      DBUG_PRINT("info", ("Checking table %s", table->s->table_name.str));
      if (table->current_lock == F_WRLCK &&
          table->file->check_table_binlog_row_based(0))
      {


        bool const has_trans= thd->lex->sql_command == SQLCOM_CREATE_TABLE ||
          table->file->has_transactions();
        int const error= thd->binlog_write_table_map(table, has_trans,
                                                     &with_annotate);


        if (unlikely(error))
          DBUG_RETURN(1);
      }
    }
  }
  DBUG_RETURN(0);
}
