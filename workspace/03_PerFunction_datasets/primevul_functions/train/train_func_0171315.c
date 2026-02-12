bool Item_in_subselect::exec()
{
  DBUG_ENTER("Item_in_subselect::exec");
  DBUG_ASSERT(fixed);


  if (!left_expr_cache && (test_strategy(SUBS_MATERIALIZATION)))
    init_left_expr_cache();


  if (!first_execution && left_expr_cache &&
      test_if_item_cache_changed(*left_expr_cache) < 0)
    DBUG_RETURN(FALSE);


  DBUG_RETURN(Item_subselect::exec());
}
