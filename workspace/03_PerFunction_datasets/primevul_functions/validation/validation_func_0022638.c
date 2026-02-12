evaluate_null_complemented_join_record(JOIN *join, JOIN_TAB *join_tab)
{


  JOIN_TAB *last_inner_tab= join_tab->last_inner;

  COND *select_cond;
  for ( ; join_tab <= last_inner_tab ; join_tab++)
  {

    join_tab->found= 1;
    join_tab->not_null_compl= 0;

    restore_record(join_tab->table,s->default_values);
    mark_as_null_row(join_tab->table);
    select_cond= join_tab->select_cond;

    if (select_cond && !select_cond->val_int())
      return NESTED_LOOP_OK;
  }
  join_tab--;


  for ( ; ; )
  {
    JOIN_TAB *first_unmatched= join_tab->first_unmatched;
    if ((first_unmatched= first_unmatched->first_upper) &&
        first_unmatched->last_inner != join_tab)
      first_unmatched= 0;
    join_tab->first_unmatched= first_unmatched;
    if (!first_unmatched)
      break;
    first_unmatched->found= 1;
    for (JOIN_TAB *tab= first_unmatched; tab <= join_tab; tab++)
    {
      if (tab->select_cond && !tab->select_cond->val_int())
      {
        join->return_tab= tab;
        return NESTED_LOOP_OK;
      }
    }
  }


  if (join_tab->check_weed_out_table)
  {
    int res= join_tab->check_weed_out_table->sj_weedout_check_row(join->thd);
    if (res == -1)
      return NESTED_LOOP_ERROR;
    else if (res == 1)
      return NESTED_LOOP_OK;
  }
  else if (join_tab->do_firstmatch)
  {


    if (join_tab->do_firstmatch < join->return_tab)
      join->return_tab= join_tab->do_firstmatch;
  }


  return (*join_tab->next_select)(join, join_tab+1, 0);
}
