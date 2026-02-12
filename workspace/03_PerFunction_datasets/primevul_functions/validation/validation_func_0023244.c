void close_thread_tables(THD *thd)
{
  TABLE *table;
  DBUG_ENTER("close_thread_tables");

  THD_STAGE_INFO(thd, stage_closing_tables);

#ifdef EXTRA_DEBUG
  DBUG_PRINT("tcache", ("open tables:"));
  for (table= thd->open_tables; table; table= table->next)
    DBUG_PRINT("tcache", ("table: '%s'.'%s' %p", table->s->db.str,
                          table->s->table_name.str, table));
#endif

#if defined(ENABLED_DEBUG_SYNC)

  if (thd->debug_sync_control)
    DEBUG_SYNC(thd, "before_close_thread_tables");
#endif

  DBUG_ASSERT(thd->transaction.stmt.is_empty() || thd->in_sub_stmt ||
              (thd->state_flags & Open_tables_state::BACKUPS_AVAIL));

  for (table= thd->open_tables; table; table= table->next)
  {
    if (table->update_handler)
      table->delete_update_handler();


    DBUG_PRINT("tcache", ("table: '%s'  query_id: %lu",
                          table->s->table_name.str, (ulong) table->query_id));

    if (thd->locked_tables_mode)
      table->vcol_cleanup_expr(thd);


    if (thd->locked_tables_mode <= LTM_LOCK_TABLES ||
        table->query_id == thd->query_id)
    {
      DBUG_ASSERT(table->file);
      table->file->extra(HA_EXTRA_DETACH_CHILDREN);
    }
  }


  if (thd->derived_tables)
  {
    TABLE *next;


    for (table= thd->derived_tables ; table ; table= next)
    {
      next= table->next;
      free_tmp_table(thd, table);
    }
    thd->derived_tables= 0;
  }

  if (thd->rec_tables)
  {
    TABLE *next;


    for (table= thd->rec_tables ; table ; table= next)
    {
      next= table->next;
      free_tmp_table(thd, table);
    }
    thd->rec_tables= 0;
  }


  thd->mark_tmp_tables_as_free_for_reuse();

  if (thd->locked_tables_mode)
  {


    mark_used_tables_as_free_for_reuse(thd, thd->open_tables);


    if (! thd->lex->requires_prelocking())
      DBUG_VOID_RETURN;


    if (thd->locked_tables_mode == LTM_PRELOCKED_UNDER_LOCK_TABLES)
      thd->locked_tables_mode= LTM_LOCK_TABLES;

    if (thd->locked_tables_mode == LTM_LOCK_TABLES)
      DBUG_VOID_RETURN;

    thd->leave_locked_tables_mode();


  }

  if (thd->lock)
  {


    (void)thd->binlog_flush_pending_rows_event(TRUE);
    mysql_unlock_tables(thd, thd->lock);
    thd->lock=0;
  }


  while (thd->open_tables)
    (void) close_thread_table(thd, &thd->open_tables);

  DBUG_VOID_RETURN;
}
