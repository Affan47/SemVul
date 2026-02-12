bool Item_in_subselect::create_in_to_exists_cond(JOIN *join_arg)
{
  bool res;

  DBUG_ASSERT(engine->engine_type() == subselect_engine::SINGLE_SELECT_ENGINE ||
              engine->engine_type() == subselect_engine::UNION_ENGINE);


  init_cond_guards();
  if (left_expr->cols() == 1)
    res= create_single_in_to_exists_cond(join_arg,
                                         &(join_arg->in_to_exists_where),
                                         &(join_arg->in_to_exists_having));
  else
    res= create_row_in_to_exists_cond(join_arg,
                                      &(join_arg->in_to_exists_where),
                                      &(join_arg->in_to_exists_having));


  if (!left_expr->const_item() || left_expr->is_expensive())
  {
    join_arg->select_lex->uncacheable|= UNCACHEABLE_DEPENDENT_INJECTED;
    join_arg->select_lex->master_unit()->uncacheable|=
                                         UNCACHEABLE_DEPENDENT_INJECTED;
  }


  join_arg->select_lex->master_unit()->uncacheable|= UNCACHEABLE_EXPLAIN;
  join_arg->select_lex->uncacheable|= UNCACHEABLE_EXPLAIN;
  return (res);
}
