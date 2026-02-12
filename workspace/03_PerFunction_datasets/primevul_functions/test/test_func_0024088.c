evaluate_join_record(JOIN *join, JOIN_TAB *join_tab,
                     int error)
{
  bool shortcut_for_distinct= join_tab->shortcut_for_distinct;
  ha_rows found_records=join->found_records;
  COND *select_cond= join_tab->select_cond;
  bool select_cond_result= TRUE;

  DBUG_ENTER("evaluate_join_record");
  DBUG_PRINT("enter",
             ("evaluate_join_record join: %p join_tab: %p"
              " cond: %p error: %d  alias %s",
              join, join_tab, select_cond, error,
              join_tab->table->alias.ptr()));
  if (error > 0 || (join->thd->is_error()))
    DBUG_RETURN(NESTED_LOOP_ERROR);
  if (error < 0)
    DBUG_RETURN(NESTED_LOOP_NO_MORE_ROWS);
  if (join->thd->check_killed())
  {
    join->thd->send_kill_message();
    DBUG_RETURN(NESTED_LOOP_KILLED);
  }

  join_tab->tracker->r_rows++;

  if (select_cond)
  {
    select_cond_result= MY_TEST(select_cond->val_int());


    if (join->thd->is_error())
      DBUG_RETURN(NESTED_LOOP_ERROR);
  }

  if (!select_cond || select_cond_result)
  {


    join_tab->tracker->r_rows_after_where++;

    bool found= 1;
    while (join_tab->first_unmatched && found)
    {


      JOIN_TAB *first_unmatched= join_tab->first_unmatched;


      first_unmatched->found= 1;
      for (JOIN_TAB *tab= first_unmatched; tab <= join_tab; tab++)
      {


	bool not_exists_opt_is_applicable=
               tab->table->reginfo.not_exists_optimize;
	for (JOIN_TAB *first_upper= first_unmatched->first_upper;
             not_exists_opt_is_applicable && first_upper;
             first_upper= first_upper->first_upper)
        {
          if (!first_upper->found)
            not_exists_opt_is_applicable= false;
        }


        if (tab->select_cond)
        {
          const longlong res= tab->select_cond->val_int();
          if (join->thd->is_error())
            DBUG_RETURN(NESTED_LOOP_ERROR);

          if (!res)
          {

            if (tab == join_tab)
            {
              found= 0;
              if (not_exists_opt_is_applicable)
                DBUG_RETURN(NESTED_LOOP_NO_MORE_ROWS);
            }
            else
            {


              join->return_tab= tab;
              if (not_exists_opt_is_applicable)
                DBUG_RETURN(NESTED_LOOP_NO_MORE_ROWS);
              else
                DBUG_RETURN(NESTED_LOOP_OK);
            }
          }
        }
      }


      if ((first_unmatched= first_unmatched->first_upper) &&
          first_unmatched->last_inner != join_tab)
        first_unmatched= 0;
      join_tab->first_unmatched= first_unmatched;
    }

    JOIN_TAB *return_tab= join->return_tab;
    join_tab->found_match= TRUE;

    if (join_tab->check_weed_out_table && found)
    {
      int res= join_tab->check_weed_out_table->sj_weedout_check_row(join->thd);
      DBUG_PRINT("info", ("weedout_check: %d", res));
      if (res == -1)
        DBUG_RETURN(NESTED_LOOP_ERROR);
      else if (res == 1)
        found= FALSE;
    }
    else if (join_tab->do_firstmatch)
    {


      return_tab= join_tab->do_firstmatch;
    }


    join->join_examined_rows++;
    DBUG_PRINT("counts", ("join->examined_rows++: %lu  found: %d",
                          (ulong) join->join_examined_rows, (int) found));

    if (found)
    {
      enum enum_nested_loop_state rc;

      rc= (*join_tab->next_select)(join, join_tab+1, 0);
      join->thd->get_stmt_da()->inc_current_row_for_warning();
      if (rc != NESTED_LOOP_OK && rc != NESTED_LOOP_NO_MORE_ROWS)
        DBUG_RETURN(rc);
      if (return_tab < join->return_tab)
        join->return_tab= return_tab;


      if (join->thd->is_error())
        DBUG_RETURN(NESTED_LOOP_ERROR);

      if (join->return_tab < join_tab)
        DBUG_RETURN(NESTED_LOOP_OK);


      if (shortcut_for_distinct && found_records != join->found_records)
        DBUG_RETURN(NESTED_LOOP_NO_MORE_ROWS);

      DBUG_RETURN(NESTED_LOOP_OK);
    }
  }
  else
  {


    join->join_examined_rows++;
  }

  join->thd->get_stmt_da()->inc_current_row_for_warning();
  join_tab->read_record.unlock_row(join_tab);

  DBUG_RETURN(NESTED_LOOP_OK);
}
