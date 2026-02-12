void remove_redundant_subquery_clauses(st_select_lex *subq_select_lex)
{
  DBUG_ENTER("remove_redundant_subquery_clauses");
  Item_subselect *subq_predicate= subq_select_lex->master_unit()->item;


  if (subq_predicate->substype() == Item_subselect::SINGLEROW_SUBS)
    DBUG_VOID_RETURN;


  DBUG_ASSERT (subq_predicate->substype() == Item_subselect::EXISTS_SUBS ||
               subq_predicate->is_in_predicate());

  if (subq_select_lex->options & SELECT_DISTINCT)
  {
    subq_select_lex->join->select_distinct= false;
    subq_select_lex->options&= ~SELECT_DISTINCT;
    DBUG_PRINT("info", ("DISTINCT removed"));
  }


  if (subq_select_lex->group_list.elements &&
      !subq_select_lex->with_sum_func && !subq_select_lex->join->having)
  {
    for (ORDER *ord= subq_select_lex->group_list.first; ord; ord= ord->next)
    {


      if (!ord->in_field_list)
        (*ord->item)->walk(&Item::eliminate_subselect_processor, FALSE, NULL);
    }
    subq_select_lex->join->group_list= NULL;
    subq_select_lex->group_list.empty();
    DBUG_PRINT("info", ("GROUP BY removed"));
  }


  DBUG_VOID_RETURN;
}
