return_zero_rows(JOIN *join, select_result *result, List<TABLE_LIST> &tables,
		 List<Item> &fields, bool send_row, ulonglong select_options,
		 const char *info, Item *having, List<Item> &all_fields)
{
  DBUG_ENTER("return_zero_rows");

  if (select_options & SELECT_DESCRIBE)
  {
    select_describe(join, FALSE, FALSE, FALSE, info);
    DBUG_RETURN(0);
  }

  join->join_free();

  if (send_row)
  {


    List_iterator<TABLE_LIST> ti(tables);
    TABLE_LIST *table;
    while ((table= ti++))
    {


      if (!table->is_jtbm())
        mark_as_null_row(table->table);
    }
    List_iterator_fast<Item> it(all_fields);
    Item *item;


    while ((item= it++))
      item->no_rows_in_result();
    if (having && having->val_int() == 0)
      send_row=0;
  }


  if (!join->send_row_on_empty_set())
  {
    join->thd->set_examined_row_count(0);
    join->thd->limit_found_rows= 0;
  }

  if (!(result->send_result_set_metadata(fields,
                              Protocol::SEND_NUM_ROWS | Protocol::SEND_EOF)))
  {
    bool send_error= FALSE;
    if (send_row)
      send_error= result->send_data(fields) > 0;
    if (likely(!send_error))
      result->send_eof();
  }
  DBUG_RETURN(0);
}
