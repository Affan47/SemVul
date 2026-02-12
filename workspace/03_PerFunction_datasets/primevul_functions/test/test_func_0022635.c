open_and_process_table(THD *thd, TABLE_LIST *tables, uint *counter, uint flags,
                       Prelocking_strategy *prelocking_strategy,
                       bool has_prelocking_list, Open_table_context *ot_ctx)
{
  bool error= FALSE;
  bool safe_to_ignore_table= FALSE;
  LEX *lex= thd->lex;
  DBUG_ENTER("open_and_process_table");
  DEBUG_SYNC(thd, "open_and_process_table");


  if (tables->derived)
  {
    if (!tables->view)
    {
      if (!tables->is_derived())
        tables->set_derived();
      goto end;
    }


    tables->db= tables->view_db.str;
    tables->db_length= tables->view_db.length;
    tables->table_name= tables->view_name.str;
    tables->table_name_length= tables->view_name.length;
  }

  if (!tables->derived &&
      is_infoschema_db(tables->db, tables->db_length))
  {


    ST_SCHEMA_TABLE *schema_table= tables->schema_table;
    if (!schema_table ||
        (schema_table->hidden &&
         ((sql_command_flags[lex->sql_command] & CF_STATUS_COMMAND) == 0 ||


          lex->sql_command == SQLCOM_SHOW_FIELDS ||
          lex->sql_command == SQLCOM_SHOW_KEYS)))
    {
      my_error(ER_UNKNOWN_TABLE, MYF(0),
               tables->table_name, INFORMATION_SCHEMA_NAME.str);
      DBUG_RETURN(1);
    }
  }


  if (tables->schema_table)
  {


    if (tables->view)
    {
      MDL_ticket *mdl_ticket;


      if (!open_table_get_mdl_lock(thd, ot_ctx, &tables->mdl_request,
                                   flags, &mdl_ticket) &&
          mdl_ticket != NULL)
        goto process_view_routines;

    }
    else if (!mysql_schema_table(thd, lex, tables) &&
             !check_and_update_table_version(thd, tables, tables->table->s))
    {
      goto end;
    }
    error= TRUE;
    goto end;
  }
  DBUG_PRINT("tcache", ("opening table: '%s'.'%s'  item: %p",
                        tables->db, tables->table_name, tables));
  (*counter)++;


  if (tables->table)
  {


    DBUG_ASSERT(is_temporary_table(tables));
  }
  else if (tables->open_type == OT_TEMPORARY_ONLY)
  {


    DBUG_ASSERT(tables->open_strategy);
    DBUG_ASSERT(!tables->prelocking_placeholder);
    DBUG_ASSERT(!tables->parent_l);
    DBUG_RETURN(0);
  }


  if (tables->prelocking_placeholder)
  {


    No_such_table_error_handler no_such_table_handler;
    thd->push_internal_handler(&no_such_table_handler);


    error= thd->open_temporary_table(tables);

    if (!error && !tables->table)
      error= open_table(thd, tables, ot_ctx);

    thd->pop_internal_handler();
    safe_to_ignore_table= no_such_table_handler.safely_trapped_errors();
  }
  else if (tables->parent_l && (thd->open_options & HA_OPEN_FOR_REPAIR))
  {


    Repair_mrg_table_error_handler repair_mrg_table_handler;
    thd->push_internal_handler(&repair_mrg_table_handler);

    error= thd->open_temporary_table(tables);

    if (!error && !tables->table)
      error= open_table(thd, tables, ot_ctx);

    thd->pop_internal_handler();
    safe_to_ignore_table= repair_mrg_table_handler.safely_trapped_errors();
  }
  else
  {
    if (tables->parent_l)
    {


      error= thd->open_temporary_table(tables);
    }

    if (!error && !tables->table)
      error= open_table(thd, tables, ot_ctx);
  }

  if (error)
  {
    if (! ot_ctx->can_recover_from_failed_open() && safe_to_ignore_table)
    {
      DBUG_PRINT("info", ("open_table: ignoring table '%s'.'%s'",
                          tables->db, tables->alias));
      error= FALSE;
    }
    goto end;
  }


  if (!tables->table && tables->view)
  {

    (*counter)--;


    if (lex->query_tables_own_last == &(tables->next_global) &&
        tables->view->query_tables)
      lex->query_tables_own_last= tables->view->query_tables_last;


    my_hash_free(&tables->view->sroutines);
    goto process_view_routines;
  }


  if (tables->open_strategy && !tables->table)
    goto end;

  error= extend_table_list(thd, tables, prelocking_strategy, has_prelocking_list);
  if (error)
    goto end;


  tables->table->grant= tables->grant;


  error= check_and_update_table_version(thd, tables, tables->table->s);

  if (error)
    goto end;


  DBUG_ASSERT(tables->table->pos_in_table_list == tables);

  if (tables->table->file->extra(HA_EXTRA_ADD_CHILDREN_LIST))
  {
    error= TRUE;
    goto end;
  }

process_view_routines:


  if (tables->view &&
      thd->locked_tables_mode <= LTM_LOCK_TABLES &&
      ! has_prelocking_list)
  {
    bool need_prelocking= FALSE;
    TABLE_LIST **save_query_tables_last= lex->query_tables_last;

    error= prelocking_strategy->handle_view(thd, lex, tables,
                                            &need_prelocking);

    if (need_prelocking && ! lex->requires_prelocking())
      lex->mark_as_requiring_prelocking(save_query_tables_last);

    if (error)
      goto end;
  }

end:
  DBUG_RETURN(error);
}
