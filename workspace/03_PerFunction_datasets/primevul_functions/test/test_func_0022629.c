static bool setup_natural_join_row_types(THD *thd,
                                         List<TABLE_LIST> *from_clause,
                                         Name_resolution_context *context)
{
  DBUG_ENTER("setup_natural_join_row_types");
  thd->where= "from clause";
  if (from_clause->elements == 0)
    DBUG_RETURN(false);


  if (!context->select_lex->first_natural_join_processing)
  {
    context->first_name_resolution_table= context->natural_join_first_table;
    DBUG_PRINT("info", ("using cached setup_natural_join_row_types"));
    DBUG_RETURN(false);
  }

  List_iterator_fast<TABLE_LIST> table_ref_it(*from_clause);
  TABLE_LIST *table_ref;

  TABLE_LIST *left_neighbor;

  TABLE_LIST *right_neighbor= NULL;


  for (left_neighbor= table_ref_it++; left_neighbor ; )
  {
    table_ref= left_neighbor;
    do
    {
      left_neighbor= table_ref_it++;
    }
    while (left_neighbor && left_neighbor->sj_subq_pred);

    if (store_top_level_join_columns(thd, table_ref,
                                     left_neighbor, right_neighbor))
      DBUG_RETURN(true);
    if (left_neighbor)
    {
      TABLE_LIST *first_leaf_on_the_right;
      first_leaf_on_the_right= table_ref->first_leaf_for_name_resolution();
      left_neighbor->next_name_resolution_table= first_leaf_on_the_right;
    }
    right_neighbor= table_ref;
  }


  DBUG_ASSERT(right_neighbor);
  context->first_name_resolution_table=
    right_neighbor->first_leaf_for_name_resolution();


  context->natural_join_first_table= context->first_name_resolution_table;
  context->select_lex->first_natural_join_processing= false;
  DBUG_RETURN (false);
}
