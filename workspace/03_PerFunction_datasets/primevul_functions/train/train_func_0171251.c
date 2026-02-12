int subselect_indexsubquery_engine::exec()
{
  DBUG_ENTER("subselect_indexsubquery_engine");
  int error;
  bool null_finding= 0;
  TABLE *table= tab->table;
  Item_in_subselect *in_subs= (Item_in_subselect *) item;

  ((Item_in_subselect *) item)->value= 0;
  empty_result_set= TRUE;
  table->status= 0;

  if (check_null)
  {

    *tab->ref.null_ref_key= 0;
    ((Item_in_subselect *) item)->was_null= 0;
  }

  if (!tab->preread_init_done && tab->preread_init())
    DBUG_RETURN(1);

  if (in_subs->left_expr_has_null())
  {


    if (in_subs->is_top_level_item())
      DBUG_RETURN(1);
    else
      DBUG_RETURN(scan_table());
  }

  if (copy_ref_key(true))
  {

    in_subs->value= 0;
    DBUG_RETURN(0);
  }

  if (!table->file->inited &&
      (error= table->file->ha_index_init(tab->ref.key, 1)))
  {
    (void) report_error(table, error);
    DBUG_RETURN(true);
  }

  error= table->file->ha_index_read_map(table->record[0],
                                        tab->ref.key_buff,
                                        make_prev_keypart_map(tab->
                                                              ref.key_parts),
                                        HA_READ_KEY_EXACT);
  if (error &&
      error != HA_ERR_KEY_NOT_FOUND && error != HA_ERR_END_OF_FILE)
    error= report_error(table, error);
  else
  {
    for (;;)
    {
      error= 0;
      table->null_row= 0;
      if (!table->status)
      {
        if ((!cond || cond->val_int()) && (!having || having->val_int()))
        {
          empty_result_set= FALSE;
          if (null_finding)
            ((Item_in_subselect *) item)->was_null= 1;
          else
            ((Item_in_subselect *) item)->value= 1;
          break;
        }
        error= table->file->ha_index_next_same(table->record[0],
                                               tab->ref.key_buff,
                                               tab->ref.key_length);
        if (error && error != HA_ERR_END_OF_FILE)
        {
          error= report_error(table, error);
          break;
        }
      }
      else
      {
        if (!check_null || null_finding)
          break;
        *tab->ref.null_ref_key= 1;
        null_finding= 1;

        if ((error= (safe_index_read(tab) == 1)))
          break;
      }
    }
  }
  DBUG_RETURN(error != 0);
}
