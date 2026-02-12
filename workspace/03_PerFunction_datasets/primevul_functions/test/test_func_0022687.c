bool open_tables(THD *thd, const DDL_options_st &options,
                 TABLE_LIST **start, uint *counter, uint flags,
                 Prelocking_strategy *prelocking_strategy)
{


  TABLE_LIST **table_to_open;
  Sroutine_hash_entry **sroutine_to_open;
  TABLE_LIST *tables;
  Open_table_context ot_ctx(thd, flags);
  bool error= FALSE;
  bool some_routine_modifies_data= FALSE;
  bool has_prelocking_list;
  DBUG_ENTER("open_tables");


  for (TABLE_LIST *table= *start; table; table= table->next_global)
    if (!table->schema_table)
    {
      enum xa_states xa_state= thd->transaction.xid_state.xa_state;
      if (xa_state == XA_IDLE || xa_state == XA_PREPARED)
      {
        my_error(ER_XAER_RMFAIL, MYF(0), xa_state_names[xa_state]);
        DBUG_RETURN(true);
      }
      else
        break;
    }

  thd->current_tablenr= 0;
restart:


  if (thd->handler_tables_hash.records)
    mysql_ha_flush(thd);

  has_prelocking_list= thd->lex->requires_prelocking();
  table_to_open= start;
  sroutine_to_open= &thd->lex->sroutines_list.first;
  *counter= 0;
  THD_STAGE_INFO(thd, stage_opening_tables);
  prelocking_strategy->reset(thd);


  if (! (flags & (MYSQL_OPEN_HAS_MDL_LOCK |
                  MYSQL_OPEN_FORCE_SHARED_MDL |
                  MYSQL_OPEN_FORCE_SHARED_HIGH_PRIO_MDL)))
  {
    if (thd->locked_tables_mode)
    {


      if (open_tables_check_upgradable_mdl(thd, *start,
                                           thd->lex->first_not_own_table(),
                                           flags))
      {
        error= TRUE;
        goto error;
      }
    }
    else
    {
      TABLE_LIST *table;
      if (lock_table_names(thd, options, *start,
                           thd->lex->first_not_own_table(),
                           ot_ctx.get_timeout(), flags))
      {
        error= TRUE;
        goto error;
      }
      for (table= *start; table && table != thd->lex->first_not_own_table();
           table= table->next_global)
      {
        if (table->mdl_request.type >= MDL_SHARED_UPGRADABLE)
          table->mdl_request.ticket= NULL;
      }
    }
  }


  while (*table_to_open  ||
         (thd->locked_tables_mode <= LTM_LOCK_TABLES && *sroutine_to_open))
  {


    for (tables= *table_to_open; tables;
         table_to_open= &tables->next_global, tables= tables->next_global)
    {
      error= open_and_process_table(thd, tables, counter, flags,
                                    prelocking_strategy, has_prelocking_list,
                                    &ot_ctx);

      if (error)
      {
        if (ot_ctx.can_recover_from_failed_open())
        {


          close_tables_for_reopen(thd, start, ot_ctx.start_of_statement_svp());


          if (ot_ctx.recover_from_failed_open())
            goto error;


          if (thd->open_temporary_tables(*start))
            goto error;

          error= FALSE;
          goto restart;
        }
        goto error;
      }

      DEBUG_SYNC(thd, "open_tables_after_open_and_process_table");
    }


    if (thd->locked_tables_mode <= LTM_LOCK_TABLES)
    {


      for (Sroutine_hash_entry *rt= *sroutine_to_open; rt;
           sroutine_to_open= &rt->next, rt= rt->next)
      {
        bool need_prelocking= false;
        bool routine_modifies_data;
        TABLE_LIST **save_query_tables_last= thd->lex->query_tables_last;

        error= open_and_process_routine(thd, thd->lex, rt, prelocking_strategy,
                                        has_prelocking_list, &ot_ctx,
                                        &need_prelocking,
                                        &routine_modifies_data);


        some_routine_modifies_data|= routine_modifies_data;

        if (need_prelocking && ! thd->lex->requires_prelocking())
          thd->lex->mark_as_requiring_prelocking(save_query_tables_last);

        if (need_prelocking && ! *start)
          *start= thd->lex->query_tables;

        if (error)
        {
          if (ot_ctx.can_recover_from_failed_open())
          {
            close_tables_for_reopen(thd, start,
                                    ot_ctx.start_of_statement_svp());
            if (ot_ctx.recover_from_failed_open())
              goto error;


            if (thd->open_temporary_tables(*start))
              goto error;

            error= FALSE;
            goto restart;
          }


          goto error;
        }
      }
    }
    if ((error= prelocking_strategy->handle_end(thd)))
      goto error;
  }


  for (tables= *start; tables; tables= tables->next_global)
  {
    TABLE *tbl= tables->table;

    if (!tbl)
      continue;


    if (tbl->file->ht->db_type == DB_TYPE_MRG_MYISAM)
    {

      DBUG_ASSERT(tbl->pos_in_table_list == tables);
      if (tbl->file->extra(HA_EXTRA_ATTACH_CHILDREN))
      {
        error= TRUE;
        goto error;
      }
    }


    if (tbl && tables->lock_type != TL_UNLOCK && !thd->locked_tables_mode)
    {
      if (tables->lock_type == TL_WRITE_DEFAULT)
        tbl->reginfo.lock_type= thd->update_lock_default;
      else if (tables->lock_type == TL_READ_DEFAULT)
          tbl->reginfo.lock_type=
            read_lock_type_for_table(thd, thd->lex, tables,
                                     some_routine_modifies_data);
      else
        tbl->reginfo.lock_type= tables->lock_type;
    }
  }

  if (WSREP(thd)                                       &&
      wsrep_replicate_myisam                           &&
      (*start)                                         &&
      (*start)->table                                  &&
      (*start)->table->file->ht == myisam_hton         &&
      wsrep_thd_exec_mode(thd) == LOCAL_STATE          &&
      !is_stat_table((*start)->db, (*start)->alias)    &&
      thd->get_command() != COM_STMT_PREPARE           &&
      !thd->stmt_arena->is_stmt_prepare()              &&
      ((thd->lex->sql_command == SQLCOM_INSERT         ||
        thd->lex->sql_command == SQLCOM_INSERT_SELECT  ||
        thd->lex->sql_command == SQLCOM_REPLACE        ||
        thd->lex->sql_command == SQLCOM_REPLACE_SELECT ||
        thd->lex->sql_command == SQLCOM_UPDATE         ||
        thd->lex->sql_command == SQLCOM_UPDATE_MULTI   ||
        thd->lex->sql_command == SQLCOM_LOAD           ||
        thd->lex->sql_command == SQLCOM_DELETE)))
  {
    WSREP_TO_ISOLATION_BEGIN(NULL, NULL, (*start));
  }

error:
WSREP_ERROR_LABEL:
  THD_STAGE_INFO(thd, stage_after_opening_tables);
  thd_proc_info(thd, 0);

  if (error && *table_to_open)
  {
    (*table_to_open)->table= NULL;
  }
  DBUG_PRINT("open_tables", ("returning: %d", (int) error));
  DBUG_RETURN(error);
}
