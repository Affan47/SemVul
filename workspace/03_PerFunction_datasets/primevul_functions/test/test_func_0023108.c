bool Item_in_optimizer::fix_left(THD *thd)
{
  DBUG_ENTER("Item_in_optimizer::fix_left");


  Item **ref0= args;
  if (!invisible_mode())
  {


    ref0= &(((Item_in_subselect *)args[1])->left_expr);
    args[0]= ((Item_in_subselect *)args[1])->left_expr;
  }
  if ((*ref0)->fix_fields_if_needed(thd, ref0) ||
      (!cache && !(cache= (*ref0)->get_cache(thd))))
    DBUG_RETURN(1);


  if (args[0] != (*ref0))
    args[0]= (*ref0);
  DBUG_PRINT("info", ("actual fix fields"));

  cache->setup(thd, args[0]);
  if (cache->cols() == 1)
  {
    DBUG_ASSERT(args[0]->type() != ROW_ITEM);


    if ((used_tables_cache= args[0]->used_tables()) || !args[0]->const_item())
      cache->set_used_tables(OUTER_REF_TABLE_BIT);
    else
      cache->set_used_tables(0);
  }
  else
  {
    uint n= cache->cols();
    for (uint i= 0; i < n; i++)
    {

      if (args[0]->element_index(i)->walk(&Item::is_subquery_processor, 0, 0))
      {
        my_error(ER_NOT_SUPPORTED_YET, MYF(0),
                 "SUBQUERY in ROW in left expression of IN/ALL/ANY");
        DBUG_RETURN(1);
      }
      Item *element=args[0]->element_index(i);
      if (element->used_tables() || !element->const_item())
      {
	((Item_cache *)cache->element_index(i))->
          set_used_tables(OUTER_REF_TABLE_BIT);
        cache->set_used_tables(OUTER_REF_TABLE_BIT);
      }
      else
	((Item_cache *)cache->element_index(i))->set_used_tables(0);
    }
    used_tables_cache= args[0]->used_tables();
  }
  eval_not_null_tables(NULL);
  copy_with_sum_func(args[0]);
  with_param= args[0]->with_param || args[1]->with_param;
  with_field= args[0]->with_field;
  if ((const_item_cache= args[0]->const_item()))
  {
    cache->store(args[0]);
    cache->cache_value();
  }
  if (args[1]->is_fixed())
  {

    used_tables_and_const_cache_join(args[1]);
    join_with_sum_func(args[1]);
  }
  DBUG_RETURN(0);
}
