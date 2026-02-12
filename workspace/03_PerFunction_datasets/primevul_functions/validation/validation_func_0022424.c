end_send(JOIN *join, JOIN_TAB *join_tab __attribute__((unused)),
	 bool end_of_records)
{
  DBUG_ENTER("end_send");


  DBUG_ASSERT(join_tab == NULL || join_tab != join->join_tab);

  List<Item> *fields= join_tab ? (join_tab-1)->fields : join->fields;

  if (!end_of_records)
  {
    if (join->table_count &&
        join->join_tab->is_using_loose_index_scan())
    {

      copy_fields(&join->tmp_table_param);
    }
    if (join->having && join->having->val_int() == 0)
      DBUG_RETURN(NESTED_LOOP_OK);
    if (join->procedure)
    {
      if (join->procedure->send_row(join->procedure_fields_list))
        DBUG_RETURN(NESTED_LOOP_ERROR);
      DBUG_RETURN(NESTED_LOOP_OK);
    }
    if (join->do_send_rows)
    {
      int error;

      if (unlikely((error= join->result->send_data(*fields))))
      {
        if (error > 0)
          DBUG_RETURN(NESTED_LOOP_ERROR);

        join->duplicate_rows++;
      }
    }

    ++join->send_records;
    if (join->send_records >= join->unit->select_limit_cnt &&
        !join->do_send_rows)
    {


      if (join->order &&
          join->select_options & OPTION_FOUND_ROWS &&
          join_tab > join->join_tab &&
          (join_tab - 1)->filesort && (join_tab - 1)->filesort->using_pq)
      {
        DBUG_PRINT("info", ("filesort NESTED_LOOP_QUERY_LIMIT"));
        DBUG_RETURN(NESTED_LOOP_QUERY_LIMIT);
      }
    }
    if (join->send_records >= join->unit->select_limit_cnt &&
	join->do_send_rows)
    {
      if (join->select_options & OPTION_FOUND_ROWS)
      {
	JOIN_TAB *jt=join->join_tab;
	if ((join->table_count == 1) && !join->sort_and_group
	    && !join->send_group_parts && !join->having && !jt->select_cond &&
	    !(jt->select && jt->select->quick) &&
	    (jt->table->file->ha_table_flags() & HA_STATS_RECORDS_IS_EXACT) &&
            (jt->ref.key < 0))
	{

	  TABLE *table=jt->table;

	  if (jt->filesort_result)
	  {
	    join->send_records= jt->filesort_result->found_rows;
	  }
	  else
	  {
	    table->file->info(HA_STATUS_VARIABLE);
	    join->send_records= table->file->stats.records;
	  }
	}
	else
	{
	  join->do_send_rows= 0;
	  if (join->unit->fake_select_lex)
	    join->unit->fake_select_lex->select_limit= 0;
	  DBUG_RETURN(NESTED_LOOP_OK);
	}
      }
      DBUG_RETURN(NESTED_LOOP_QUERY_LIMIT);
    }
    else if (join->send_records >= join->fetch_limit)
    {


      DBUG_RETURN(NESTED_LOOP_CURSOR_LIMIT);
    }
  }
  else
  {
    if (join->procedure && join->procedure->end_of_records())
      DBUG_RETURN(NESTED_LOOP_ERROR);
  }
  DBUG_RETURN(NESTED_LOOP_OK);
}
