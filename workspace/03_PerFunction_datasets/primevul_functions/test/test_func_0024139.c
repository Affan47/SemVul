int mysql_update(THD *thd,
                 TABLE_LIST *table_list,
                 List<Item> &fields,
		 List<Item> &values,
                 COND *conds,
                 uint order_num, ORDER *order,
                 ha_rows limit,
                 bool ignore,
                 ha_rows *found_return, ha_rows *updated_return)
{
  bool		using_limit= limit != HA_POS_ERROR;
  bool          safe_update= (thd->variables.option_bits & OPTION_SAFE_UPDATES)
                             && !thd->lex->describe;
  bool          used_key_is_modified= FALSE, transactional_table;
  bool          will_batch= FALSE;
  bool		can_compare_record;
  int           res;
  int		error, loc_error;
  ha_rows       dup_key_found;
  bool          need_sort= TRUE;
  bool          reverse= FALSE;
#ifndef NO_EMBEDDED_ACCESS_CHECKS
  uint		want_privilege;
#endif
  uint          table_count= 0;
  ha_rows	updated, found;
  key_map	old_covering_keys;
  TABLE		*table;
  SQL_SELECT	*select= NULL;
  SORT_INFO     *file_sort= 0;
  READ_RECORD	info;
  SELECT_LEX    *select_lex= &thd->lex->select_lex;
  ulonglong     id;
  List<Item> all_fields;
  killed_state killed_status= NOT_KILLED;
  bool has_triggers, binlog_is_row, do_direct_update= FALSE;
  Update_plan query_plan(thd->mem_root);
  Explain_update *explain;
  TABLE_LIST *update_source_table;
  query_plan.index= MAX_KEY;
  query_plan.using_filesort= FALSE;


  ha_rows updated_sys_ver= 0;

  DBUG_ENTER("mysql_update");

  create_explain_query(thd->lex, thd->mem_root);
  if (open_tables(thd, &table_list, &table_count, 0))
    DBUG_RETURN(1);


  if (mysql_handle_derived(thd->lex, DT_INIT))
    DBUG_RETURN(1);

  if (((update_source_table=unique_table(thd, table_list,
                                        table_list->next_global, 0)) ||
        table_list->is_multitable()))
  {
    DBUG_ASSERT(update_source_table || table_list->view != 0);
    DBUG_PRINT("info", ("Switch to multi-update"));

    thd->lex->table_count= table_count;

    DBUG_RETURN(2);
  }
  if (lock_tables(thd, table_list, table_count, 0))
    DBUG_RETURN(1);

  (void) read_statistics_for_tables_if_needed(thd, table_list);

  THD_STAGE_INFO(thd, stage_init_update);
  if (table_list->handle_derived(thd->lex, DT_MERGE_FOR_INSERT))
    DBUG_RETURN(1);
  if (table_list->handle_derived(thd->lex, DT_PREPARE))
    DBUG_RETURN(1);

  table= table_list->table;

  if (!table_list->single_table_updatable())
  {
    my_error(ER_NON_UPDATABLE_TABLE, MYF(0), table_list->alias.str, "UPDATE");
    DBUG_RETURN(1);
  }
  query_plan.updating_a_view= MY_TEST(table_list->view);


  table->covering_keys= table->s->keys_in_use;
  table->quick_keys.clear_all();

  query_plan.select_lex= &thd->lex->select_lex;
  query_plan.table= table;
#ifndef NO_EMBEDDED_ACCESS_CHECKS

  want_privilege= (table_list->view ? UPDATE_ACL :
                   table_list->grant.want_privilege);
#endif
  promote_select_describe_flag_if_needed(thd->lex);

  if (mysql_prepare_update(thd, table_list, &conds, order_num, order))
    DBUG_RETURN(1);

  old_covering_keys= table->covering_keys;

#ifndef NO_EMBEDDED_ACCESS_CHECKS
  table_list->grant.want_privilege= table->grant.want_privilege= want_privilege;
  table_list->register_want_access(want_privilege);
#endif

  if (table_list->is_view())
    unfix_fields(fields);

  if (setup_fields_with_no_wrap(thd, Ref_ptr_array(),
                                fields, MARK_COLUMNS_WRITE, 0, 0))
    DBUG_RETURN(1);
  if (check_fields(thd, fields, table_list->view))
  {
    DBUG_RETURN(1);
  }
  bool has_vers_fields= table->vers_check_update(fields);
  if (check_key_in_view(thd, table_list))
  {
    my_error(ER_NON_UPDATABLE_TABLE, MYF(0), table_list->alias.str, "UPDATE");
    DBUG_RETURN(1);
  }

  if (table->default_field)
    table->mark_default_fields_for_write(false);

#ifndef NO_EMBEDDED_ACCESS_CHECKS

  table_list->grant.want_privilege= table->grant.want_privilege=
    (SELECT_ACL & ~table->grant.privilege);
#endif
  if (setup_fields(thd, Ref_ptr_array(), values, MARK_COLUMNS_READ, 0, NULL, 0))
  {
    free_underlaid_joins(thd, select_lex);
    DBUG_RETURN(1);
  }

  if (check_unique_table(thd, table_list))
    DBUG_RETURN(TRUE);

  switch_to_nullable_trigger_fields(fields, table);
  switch_to_nullable_trigger_fields(values, table);


  if (select_lex->optimize_unflattened_subqueries(false))
    DBUG_RETURN(TRUE);

  if (select_lex->inner_refs_list.elements &&
    fix_inner_refs(thd, all_fields, select_lex, select_lex->ref_pointer_array))
    DBUG_RETURN(1);

  if (conds)
  {
    Item::cond_result cond_value;
    conds= conds->remove_eq_conds(thd, &cond_value, true);
    if (cond_value == Item::COND_FALSE)
    {
      limit= 0;
      query_plan.set_impossible_where();
      if (thd->lex->describe || thd->lex->analyze_stmt)
        goto produce_explain_and_leave;
    }
  }


  table->covering_keys.clear_all();

#ifdef WITH_PARTITION_STORAGE_ENGINE
  if (prune_partitions(thd, table, conds))
  {
    free_underlaid_joins(thd, select_lex);

    query_plan.set_no_partitions();
    if (thd->lex->describe || thd->lex->analyze_stmt)
      goto produce_explain_and_leave;
    if (thd->is_error())
      DBUG_RETURN(1);

    my_ok(thd);
    DBUG_RETURN(0);
  }
#endif

  table->file->info(HA_STATUS_VARIABLE | HA_STATUS_NO_LOCK);
  set_statistics_for_table(thd, table);

  select= make_select(table, 0, 0, conds, (SORT_INFO*) 0, 0, &error);
  if (unlikely(error || !limit || thd->is_error() ||
               (select && select->check_quick(thd, safe_update, limit))))
  {
    query_plan.set_impossible_where();
    if (thd->lex->describe || thd->lex->analyze_stmt)
      goto produce_explain_and_leave;

    delete select;
    free_underlaid_joins(thd, select_lex);


    if (error || thd->is_error())
    {
      DBUG_RETURN(1);
    }
    my_ok(thd);
    DBUG_RETURN(0);
  }


  if (!select || !select->quick)
  {
    thd->set_status_no_index_used();
    if (safe_update && !using_limit)
    {
      my_message(ER_UPDATE_WITHOUT_KEY_IN_SAFE_MODE,
		 ER_THD(thd, ER_UPDATE_WITHOUT_KEY_IN_SAFE_MODE), MYF(0));
      goto err;
    }
  }
  if (unlikely(init_ftfuncs(thd, select_lex, 1)))
    goto err;

  table->mark_columns_needed_for_update();

  table->update_const_key_parts(conds);
  order= simple_remove_const(order, conds);
  query_plan.scanned_rows= select? select->records: table->file->stats.records;

  if (select && select->quick && select->quick->unique_key_range())
  {

    need_sort= FALSE;
    query_plan.index= MAX_KEY;
    used_key_is_modified= FALSE;
  }
  else
  {
    ha_rows scanned_limit= query_plan.scanned_rows;
    query_plan.index= get_index_for_order(order, table, select, limit,
                                          &scanned_limit, &need_sort,
                                          &reverse);
    if (!need_sort)
      query_plan.scanned_rows= scanned_limit;

    if (select && select->quick)
    {
      DBUG_ASSERT(need_sort || query_plan.index == select->quick->index);
      used_key_is_modified= (!select->quick->unique_key_range() &&
                             select->quick->is_keys_used(table->write_set));
    }
    else
    {
      if (need_sort)
      {

        query_plan.index= table->file->key_used_on_scan;
      }
      if (query_plan.index != MAX_KEY)
      {

        used_key_is_modified= is_key_used(table, query_plan.index,
                                          table->write_set);
      }
    }
  }


  query_plan.select= select;
  query_plan.possible_keys= select? select->possible_keys: key_map(0);

  if (used_key_is_modified || order ||
      partition_key_modified(table, table->write_set))
  {
    if (order && need_sort)
      query_plan.using_filesort= true;
    else
      query_plan.using_io_buffer= true;
  }


  if (thd->lex->describe)
    goto produce_explain_and_leave;
  if (!(explain= query_plan.save_explain_update_data(query_plan.mem_root, thd)))
    goto err;

  ANALYZE_START_TRACKING(&explain->command_tracker);

  DBUG_EXECUTE_IF("show_explain_probe_update_exec_start",
                  dbug_serve_apcs(thd, 1););

  has_triggers= (table->triggers &&
                 (table->triggers->has_triggers(TRG_EVENT_UPDATE,
                                                TRG_ACTION_BEFORE) ||
                 table->triggers->has_triggers(TRG_EVENT_UPDATE,
                                               TRG_ACTION_AFTER)));
  DBUG_PRINT("info", ("has_triggers: %s", has_triggers ? "TRUE" : "FALSE"));
  binlog_is_row= thd->is_current_stmt_binlog_format_row();
  DBUG_PRINT("info", ("binlog_is_row: %s", binlog_is_row ? "TRUE" : "FALSE"));

  if (!(select && select->quick))
    status_var_increment(thd->status_var.update_scan_count);


  if ((table->file->ha_table_flags() & HA_CAN_DIRECT_UPDATE_AND_DELETE) &&
      !has_triggers && !binlog_is_row &&
      !query_plan.using_io_buffer && !ignore &&
      !table->check_virtual_columns_marked_for_read() &&
      !table->check_virtual_columns_marked_for_write())
  {
    DBUG_PRINT("info", ("Trying direct update"));
    bool use_direct_update= !select || !select->cond;
    if (!use_direct_update &&
        (select->cond->used_tables() & ~RAND_TABLE_BIT) == table->map)
    {
      DBUG_ASSERT(!table->file->pushed_cond);
      if (!table->file->cond_push(select->cond))
      {
        use_direct_update= TRUE;
        table->file->pushed_cond= select->cond;
      }
    }

    if (use_direct_update &&
        !table->file->info_push(INFO_KIND_UPDATE_FIELDS, &fields) &&
        !table->file->info_push(INFO_KIND_UPDATE_VALUES, &values) &&
        !table->file->direct_update_rows_init(&fields))
    {
      do_direct_update= TRUE;


      goto update_begin;
    }
  }

  if (query_plan.using_filesort || query_plan.using_io_buffer)
  {


    if (query_plan.using_filesort)
    {


      Filesort fsort(order, limit, true, select);

      Filesort_tracker *fs_tracker=
        thd->lex->explain->get_upd_del_plan()->filesort_tracker;

      if (!(file_sort= filesort(thd, table, &fsort, fs_tracker)))
	goto err;
      thd->inc_examined_row_count(file_sort->examined_rows);


      delete select;
      select= 0;
    }
    else
    {
      MY_BITMAP *save_read_set= table->read_set;
      MY_BITMAP *save_write_set= table->write_set;

      if (query_plan.index < MAX_KEY && old_covering_keys.is_set(query_plan.index))
        table->prepare_for_keyread(query_plan.index);
      else
        table->use_all_columns();


      explain->buf_tracker.on_scan_init();
      IO_CACHE tempfile;
      if (open_cached_file(&tempfile, mysql_tmpdir,TEMP_PREFIX,
			   DISK_BUFFER_SIZE, MYF(MY_WME)))
	goto err;


      if (select && select->quick && select->quick->reset())
      {
        close_cached_file(&tempfile);
        goto err;
      }

      table->file->try_semi_consistent_read(1);


      if (query_plan.index == MAX_KEY || (select && select->quick))
        error= init_read_record(&info, thd, table, select, NULL, 0, 1, FALSE);
      else
        error= init_read_record_idx(&info, thd, table, 1, query_plan.index,
                                    reverse);

      if (unlikely(error))
      {
        close_cached_file(&tempfile);
        goto err;
      }

      THD_STAGE_INFO(thd, stage_searching_rows_for_update);
      ha_rows tmp_limit= limit;

      while (likely(!(error=info.read_record())) && likely(!thd->killed))
      {
        explain->buf_tracker.on_record_read();
        thd->inc_examined_row_count(1);
	if (!select || (error= select->skip_record(thd)) > 0)
	{
          if (table->file->ha_was_semi_consistent_read())
	    continue;

          explain->buf_tracker.on_record_after_where();
	  table->file->position(table->record[0]);
	  if (unlikely(my_b_write(&tempfile,table->file->ref,
                                  table->file->ref_length)))
	  {
	    error=1;
	    break;
	  }
	  if (!--limit && using_limit)
	  {
	    error= -1;
	    break;
	  }
	}
	else
        {


          if (unlikely(error < 0))
          {

            error= 1;
            break;
          }
          else
            table->file->unlock_row();
        }
      }
      if (unlikely(thd->killed) && !error)
	error= 1;
      limit= tmp_limit;
      table->file->try_semi_consistent_read(0);
      end_read_record(&info);


      if (select)
      {
	delete select->quick;
	if (select->free_cond)
	  delete select->cond;
	select->quick=0;
	select->cond=0;
      }
      else
      {
	if (!(select= new SQL_SELECT))
          goto err;
	select->head=table;
      }

      if (unlikely(reinit_io_cache(&tempfile,READ_CACHE,0L,0,0)))
	error= 1;
      select->file= tempfile;
       if (unlikely(error >= 0))
	goto err;

      table->file->ha_end_keyread();
      table->column_bitmaps_set(save_read_set, save_write_set);
    }
  }

update_begin:
  if (ignore)
    table->file->extra(HA_EXTRA_IGNORE_DUP_KEY);

  if (select && select->quick && select->quick->reset())
    goto err;
  table->file->try_semi_consistent_read(1);
  if (init_read_record(&info, thd, table, select, file_sort, 0, 1, FALSE))
    goto err;

  updated= found= 0;


  thd->count_cuted_fields= CHECK_FIELD_WARN;
  thd->cuted_fields=0L;

  transactional_table= table->file->has_transactions();
  thd->abort_on_warning= !ignore && thd->is_strict_mode();

  if (do_direct_update)
  {

    DBUG_PRINT("info", ("Using direct update"));
    table->reset_default_fields();
    if (unlikely(!(error= table->file->ha_direct_update_rows(&updated))))
      error= -1;
    found= updated;
    goto update_end;
  }

  if ((table->file->ha_table_flags() & HA_CAN_FORCE_BULK_UPDATE) &&
      !table->prepare_triggers_for_update_stmt_or_event())
    will_batch= !table->file->start_bulk_update();


  if (table->file->ha_table_flags() & HA_PARTIAL_COLUMN_READ)
    table->prepare_for_position();

  table->reset_default_fields();


  can_compare_record= records_are_comparable(table);
  explain->tracker.on_scan_init();

  THD_STAGE_INFO(thd, stage_updating);
  while (!(error=info.read_record()) && !thd->killed)
  {
    explain->tracker.on_record_read();
    thd->inc_examined_row_count(1);
    if (!select || select->skip_record(thd) > 0)
    {
      if (table->file->ha_was_semi_consistent_read())
        continue;

      explain->tracker.on_record_after_where();
      store_record(table,record[1]);

      if (fill_record_n_invoke_before_triggers(thd, table, fields, values, 0,
                                               TRG_EVENT_UPDATE))
        break;

      found++;

      if (!can_compare_record || compare_record(table))
      {
        if ((res= table_list->view_check_option(thd, ignore)) !=
            VIEW_CHECK_OK)
        {
          found--;
          if (res == VIEW_CHECK_SKIP)
            continue;
          else if (res == VIEW_CHECK_ERROR)
          {
            error= 1;
            break;
          }
        }
        if (will_batch)
        {


          DBUG_PRINT("info", ("Batched update"));
          error= table->file->ha_bulk_update_row(table->record[1],
                                                 table->record[0],
                                                 &dup_key_found);
          limit+= dup_key_found;
          updated-= dup_key_found;
        }
        else
        {

          error= table->file->ha_update_row(table->record[1],
                                            table->record[0]);
        }
        if (unlikely(error == HA_ERR_RECORD_IS_THE_SAME))
        {
          error= 0;
        }
        else if (likely(!error))
        {
          if (has_vers_fields && table->versioned(VERS_TRX_ID))
            updated_sys_ver++;
          updated++;
        }

        if (unlikely(error) &&
            (!ignore || table->file->is_fatal_error(error, HA_CHECK_ALL)))
        {
          goto error;
        }
      }

      if (likely(!error) && has_vers_fields && table->versioned(VERS_TIMESTAMP))
      {
        store_record(table, record[2]);
        table->mark_columns_per_binlog_row_image();
        error= vers_insert_history_row(table);
        restore_record(table, record[2]);
        if (unlikely(error))
        {
error:


          myf flags= 0;

          if (table->file->is_fatal_error(error, HA_CHECK_ALL))
            flags|= ME_FATALERROR;

          prepare_record_for_error_message(error, table);
          table->file->print_error(error,MYF(flags));
          error= 1;
          break;
        }
        updated_sys_ver++;
      }

      if (table->triggers &&
          unlikely(table->triggers->process_triggers(thd, TRG_EVENT_UPDATE,
                                                     TRG_ACTION_AFTER, TRUE)))
      {
        error= 1;
        break;
      }

      if (!--limit && using_limit)
      {


        if (will_batch &&
            ((error= table->file->exec_bulk_update(&dup_key_found)) ||
             dup_key_found))
        {
 	  if (error)
          {


            prepare_record_for_error_message(error, table);
            table->file->print_error(error,MYF(0));
            error= 1;
            break;

          }


          limit= dup_key_found;
          updated-= dup_key_found;
        }
        else
        {
	  error= -1;
	  break;
        }
      }
    }


    else if (likely(!thd->is_error()))
      table->file->unlock_row();
    else
    {
      error= 1;
      break;
    }
    thd->get_stmt_da()->inc_current_row_for_warning();
    if (unlikely(thd->is_error()))
    {
      error= 1;
      break;
    }
  }
  ANALYZE_STOP_TRACKING(&explain->command_tracker);
  table->auto_increment_field_not_null= FALSE;
  dup_key_found= 0;


  killed_status= thd->killed;

  DBUG_EXECUTE_IF("simulate_kill_bug27571",
                  {
                    thd->set_killed(KILL_QUERY);
                  };);
  error= (killed_status == NOT_KILLED)?  error : 1;

  if (likely(error) &&
      will_batch &&
      (loc_error= table->file->exec_bulk_update(&dup_key_found)))


  {

    prepare_record_for_error_message(loc_error, table);
    table->file->print_error(loc_error,MYF(ME_FATALERROR));
    error= 1;

  }
  else
    updated-= dup_key_found;
  if (will_batch)
    table->file->end_bulk_update();

update_end:
  table->file->try_semi_consistent_read(0);

  if (!transactional_table && updated > 0)
    thd->transaction.stmt.modified_non_trans_table= TRUE;

  end_read_record(&info);
  delete select;
  select= NULL;
  THD_STAGE_INFO(thd, stage_end);
  (void) table->file->extra(HA_EXTRA_NO_IGNORE_DUP_KEY);


  if (updated)
  {
    query_cache_invalidate3(thd, table_list, 1);
  }

  if (thd->transaction.stmt.modified_non_trans_table)
      thd->transaction.all.modified_non_trans_table= TRUE;
  thd->transaction.all.m_unsafe_rollback_flags|=
    (thd->transaction.stmt.m_unsafe_rollback_flags & THD_TRANS::DID_WAIT);


  if (likely(error < 0) || thd->transaction.stmt.modified_non_trans_table)
  {
    if (WSREP_EMULATE_BINLOG(thd) || mysql_bin_log.is_open())
    {
      int errcode= 0;
      if (likely(error < 0))
        thd->clear_error();
      else
        errcode= query_error_code(thd, killed_status == NOT_KILLED);

      ScopedStatementReplication scoped_stmt_rpl(
          table->versioned(VERS_TRX_ID) ? thd : NULL);

      if (thd->binlog_query(THD::ROW_QUERY_TYPE,
                            thd->query(), thd->query_length(),
                            transactional_table, FALSE, FALSE, errcode) > 0)
      {
        error=1;
      }
    }
  }
  DBUG_ASSERT(transactional_table || !updated || thd->transaction.stmt.modified_non_trans_table);
  free_underlaid_joins(thd, select_lex);
  delete file_sort;
  if (table->file->pushed_cond)
  {
    table->file->pushed_cond= 0;
    table->file->cond_pop();
  }


  id= thd->arg_of_last_insert_id_function ?
    thd->first_successful_insert_id_in_prev_stmt : 0;

  if (likely(error < 0) && likely(!thd->lex->analyze_stmt))
  {
    char buff[MYSQL_ERRMSG_SIZE];
    if (!table->versioned(VERS_TIMESTAMP))
      my_snprintf(buff, sizeof(buff), ER_THD(thd, ER_UPDATE_INFO), (ulong) found,
                  (ulong) updated,
                  (ulong) thd->get_stmt_da()->current_statement_warn_count());
    else
      my_snprintf(buff, sizeof(buff),
                  ER_THD(thd, ER_UPDATE_INFO_WITH_SYSTEM_VERSIONING),
                  (ulong) found, (ulong) updated, (ulong) updated_sys_ver,
                  (ulong) thd->get_stmt_da()->current_statement_warn_count());
    my_ok(thd, (thd->client_capabilities & CLIENT_FOUND_ROWS) ? found : updated,
          id, buff);
    DBUG_PRINT("info",("%ld records updated", (long) updated));
  }
  thd->count_cuted_fields= CHECK_FIELD_IGNORE;
  thd->abort_on_warning= 0;
  if (thd->lex->current_select->first_cond_optimization)
  {
    thd->lex->current_select->save_leaf_tables(thd);
    thd->lex->current_select->first_cond_optimization= 0;
  }
  *found_return= found;
  *updated_return= updated;

  if (unlikely(thd->lex->analyze_stmt))
    goto emit_explain_and_leave;

  DBUG_RETURN((error >= 0 || thd->is_error()) ? 1 : 0);

err:
  delete select;
  delete file_sort;
  free_underlaid_joins(thd, select_lex);
  table->file->ha_end_keyread();
  if (table->file->pushed_cond)
    table->file->cond_pop();
  thd->abort_on_warning= 0;
  DBUG_RETURN(1);

produce_explain_and_leave:


  if (unlikely(!query_plan.save_explain_update_data(query_plan.mem_root, thd)))
    goto err;

emit_explain_and_leave:
  int err2= thd->lex->explain->send_explain(thd);

  delete select;
  free_underlaid_joins(thd, select_lex);
  DBUG_RETURN((err2 || thd->is_error()) ? 1 : 0);
}
