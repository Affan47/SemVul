bool Item_subselect::is_expensive()
{
  double examined_rows= 0;
  bool all_are_simple= true;


  if (!unit->first_select()->next_select())
  {


    SELECT_LEX *sl= unit->first_select();
    JOIN *join = sl->join;
    if (join && !join->tables_list && !sl->first_inner_unit())
      return false;
  }


  for (SELECT_LEX *sl= unit->first_select(); sl; sl= sl->next_select())
  {
    JOIN *cur_join= sl->join;


    if (!cur_join)
      return true;


    if (cur_join->optimization_state != JOIN::OPTIMIZATION_DONE)
      return true;

    if (!cur_join->tables_list && !sl->first_inner_unit())
      continue;


    if ((cur_join->zero_result_cause || !cur_join->tables_list))
      continue;


    all_are_simple= false;


    if (!cur_join->join_tab)
      return true;

    if (sl->first_inner_unit())
    {


      return true;
    }

    examined_rows+= cur_join->get_examined_rows();
  }


  return !all_are_simple &&
    (examined_rows > thd->variables.expensive_subquery_limit);
}
