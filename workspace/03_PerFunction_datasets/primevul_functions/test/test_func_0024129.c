int multi_update::send_data(List<Item> &not_used_values)
{
  TABLE_LIST *cur_table;
  DBUG_ENTER("multi_update::send_data");

  for (cur_table= update_tables; cur_table; cur_table= cur_table->next_local)
  {
    int error= 0;
    TABLE *table= cur_table->table;
    uint offset= cur_table->shared;


    if (table->status & (STATUS_NULL_ROW | STATUS_UPDATED))
      continue;

    if (table == table_to_update)
    {


      bool can_compare_record;
      can_compare_record= records_are_comparable(table);

      table->status|= STATUS_UPDATED;
      store_record(table,record[1]);

      if (fill_record_n_invoke_before_triggers(thd, table,
                                               *fields_for_table[offset],
                                               *values_for_table[offset], 0,
                                               TRG_EVENT_UPDATE))
	DBUG_RETURN(1);


      table->auto_increment_field_not_null= FALSE;
      found++;
      if (!can_compare_record || compare_record(table))
      {

        if ((error= cur_table->view_check_option(thd, ignore)) !=
            VIEW_CHECK_OK)
        {
          found--;
          if (error == VIEW_CHECK_SKIP)
            continue;
          else if (unlikely(error == VIEW_CHECK_ERROR))
            DBUG_RETURN(1);
        }
        if (unlikely(!updated++))
        {


          main_table->file->extra(HA_EXTRA_PREPARE_FOR_UPDATE);
        }
        if (unlikely((error=table->file->ha_update_row(table->record[1],
                                                       table->record[0]))) &&
            error != HA_ERR_RECORD_IS_THE_SAME)
        {
          updated--;
          if (!ignore ||
              table->file->is_fatal_error(error, HA_CHECK_ALL))
            goto error;
        }
        else
        {
          if (unlikely(error == HA_ERR_RECORD_IS_THE_SAME))
          {
            error= 0;
            updated--;
          }
          else if (has_vers_fields && table->versioned(VERS_TRX_ID))
          {
            updated_sys_ver++;
          }


          if (table->file->has_transactions())
            transactional_tables= TRUE;
          else
          {
            trans_safe= FALSE;
            thd->transaction.stmt.modified_non_trans_table= TRUE;
          }
        }
      }
      if (has_vers_fields && table->versioned(VERS_TIMESTAMP))
      {
        store_record(table, record[2]);
        if (unlikely(error= vers_insert_history_row(table)))
        {
          restore_record(table, record[2]);
          goto error;
        }
        restore_record(table, record[2]);
        updated_sys_ver++;
      }
      if (table->triggers &&
          unlikely(table->triggers->process_triggers(thd, TRG_EVENT_UPDATE,
                                                     TRG_ACTION_AFTER, TRUE)))
        DBUG_RETURN(1);
    }
    else
    {
      TABLE *tmp_table= tmp_tables[offset];
      if (copy_funcs(tmp_table_param[offset].items_to_copy, thd))
        DBUG_RETURN(1);

      if (tmp_table->field[0]->is_null())
        continue;

      DBUG_ASSERT(1 + unupdated_check_opt_tables.elements ==
                  tmp_table_param[offset].func_count);
      fill_record(thd, tmp_table,
                  tmp_table->field + 1 + unupdated_check_opt_tables.elements,
                  *values_for_table[offset], TRUE, FALSE);


      error= tmp_table->file->ha_write_tmp_row(tmp_table->record[0]);
      found++;
      if (unlikely(error))
      {
        found--;
        if (error != HA_ERR_FOUND_DUPP_KEY &&
            error != HA_ERR_FOUND_DUPP_UNIQUE)
        {
          if (create_internal_tmp_table_from_heap(thd, tmp_table,
                                                  tmp_table_param[offset].start_recinfo,
                                                  &tmp_table_param[offset].recinfo,
                                                  error, 1, NULL))
          {
            do_update= 0;
            DBUG_RETURN(1);
          }
          found++;
        }
      }
    }
    continue;
error:
    DBUG_ASSERT(error > 0);


    myf flags= 0;

    if (table->file->is_fatal_error(error, HA_CHECK_ALL))
      flags|= ME_FATALERROR;

    prepare_record_for_error_message(error, table);
    table->file->print_error(error,MYF(flags));
    DBUG_RETURN(1);
  }
  DBUG_RETURN(0);
}
