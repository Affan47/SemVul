void JOIN::exec_inner()
{
  List<Item> *columns_list= &fields_list;
  DBUG_ENTER("JOIN::exec_inner");
  DBUG_ASSERT(optimization_state == JOIN::OPTIMIZATION_DONE);

  THD_STAGE_INFO(thd, stage_executing);


  if (!select_lex->outer_select() &&
      select_lex != select_lex->master_unit()->fake_select_lex)
    thd->lex->set_limit_rows_examined();

  if (procedure)
  {
    procedure_fields_list= fields_list;
    if (procedure->change_columns(thd, procedure_fields_list) ||
	result->prepare(procedure_fields_list, unit))
    {
      thd->set_examined_row_count(0);
      thd->limit_found_rows= 0;
      DBUG_VOID_RETURN;
    }
    columns_list= &procedure_fields_list;
  }
  if (result->prepare2(this))
    DBUG_VOID_RETURN;

  if (!tables_list && (table_count || !select_lex->with_sum_func) &&
      !select_lex->have_window_funcs())
  {
    if (select_options & SELECT_DESCRIBE)
      select_describe(this, FALSE, FALSE, FALSE,
		      (zero_result_cause?zero_result_cause:"No tables used"));

    else
    {
      if (result->send_result_set_metadata(*columns_list,
                                           Protocol::SEND_NUM_ROWS |
                                           Protocol::SEND_EOF))
      {
        DBUG_VOID_RETURN;
      }


      DBUG_ASSERT(error == 0);
      if (cond_value != Item::COND_FALSE &&
          having_value != Item::COND_FALSE &&
          (!conds || conds->val_int()) &&
          (!having || having->val_int()))
      {
	if (do_send_rows &&
            (procedure ? (procedure->send_row(procedure_fields_list) ||
             procedure->end_of_records()) : result->send_data(fields_list)> 0))
	  error= 1;
	else
	  send_records= ((select_options & OPTION_FOUND_ROWS) ? 1 :
                         thd->get_sent_row_count());
      }
      else
        send_records= 0;
      if (likely(!error))
      {
        join_free();
        error= (int) result->send_eof();
      }
    }

    thd->limit_found_rows= send_records;
    thd->set_examined_row_count(0);
    DBUG_VOID_RETURN;
  }


  if (!zero_result_cause &&
      exec_const_cond && !(select_options & SELECT_DESCRIBE) &&
      !exec_const_cond->val_int())
    zero_result_cause= "Impossible WHERE noticed after reading const tables";


  if (unlikely(thd->is_error()))
  {
    error= thd->is_error();
    DBUG_VOID_RETURN;
  }

  if (zero_result_cause)
  {
    if (select_lex->have_window_funcs() && send_row_on_empty_set())
    {


      const_tables= table_count;
      first_select= sub_select_postjoin_aggr;
    }
    else
    {
      (void) return_zero_rows(this, result, select_lex->leaf_tables,
                              *columns_list,
			      send_row_on_empty_set(),
			      select_options,
			      zero_result_cause,
			      having ? having : tmp_having, all_fields);
      DBUG_VOID_RETURN;
    }
  }


  if (exec_const_order_group_cond.elements &&
      !(select_options & SELECT_DESCRIBE))
  {
    List_iterator_fast<Item> const_item_it(exec_const_order_group_cond);
    Item *cur_const_item;
    while ((cur_const_item= const_item_it++))
    {
      cur_const_item->val_str();
      if (unlikely(thd->is_error()))
      {
        error= thd->is_error();
        DBUG_VOID_RETURN;
      }
    }
  }

  if ((this->select_lex->options & OPTION_SCHEMA_TABLE) &&
      get_schema_tables_result(this, PROCESSED_BY_JOIN_EXEC))
    DBUG_VOID_RETURN;

  if (select_options & SELECT_DESCRIBE)
  {
    select_describe(this, need_tmp,
		    order != 0 && !skip_sort_order,
		    select_distinct,
                    !table_count ? "No tables used" : NullS);
    DBUG_VOID_RETURN;
  }
  else
  {

    select_lex->mark_const_derived(zero_result_cause);
  }


  join_examined_rows= 0;


  if (unlikely(thd->is_error()))
  {
    error= thd->is_error();
    DBUG_VOID_RETURN;
  }

  THD_STAGE_INFO(thd, stage_sending_data);
  DBUG_PRINT("info", ("%s", thd->proc_info));
  result->send_result_set_metadata(
                 procedure ? procedure_fields_list : *fields,
                 Protocol::SEND_NUM_ROWS | Protocol::SEND_EOF);

  error= result->view_structure_only() ? false : do_select(this, procedure);

  thd->inc_examined_row_count(join_examined_rows);
  DBUG_PRINT("counts", ("thd->examined_row_count: %lu",
                        (ulong) thd->get_examined_row_count()));

  DBUG_VOID_RETURN;
}
