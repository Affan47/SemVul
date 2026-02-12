make_cond_for_table_from_pred(THD *thd, Item *root_cond, Item *cond,
                              table_map tables, table_map used_table,
                              int join_tab_idx_arg,
                              bool exclude_expensive_cond __attribute__
                              ((unused)),
                              bool retain_ref_cond,
                              bool is_top_and_level)

{
  table_map rand_table_bit= (table_map) RAND_TABLE_BIT;

  if (used_table && !(cond->used_tables() & used_table))
    return (COND*) 0;

  if (cond->type() == Item::COND_ITEM)
  {
    if (((Item_cond*) cond)->functype() == Item_func::COND_AND_FUNC)
    {

      Item_cond_and *new_cond=new (thd->mem_root) Item_cond_and(thd);
      if (!new_cond)
	return (COND*) 0;
      List_iterator<Item> li(*((Item_cond*) cond)->argument_list());
      Item *item;
      while ((item=li++))
      {


        if (is_top_and_level && used_table == rand_table_bit &&
            (item->used_tables() & ~OUTER_REF_TABLE_BIT) != rand_table_bit)
        {

          continue;
        }
	Item *fix=make_cond_for_table_from_pred(thd, root_cond, item,
                                                tables, used_table,
                                                join_tab_idx_arg,
                                                exclude_expensive_cond,
                                                retain_ref_cond, false);
	if (fix)
	  new_cond->argument_list()->push_back(fix, thd->mem_root);
      }
      switch (new_cond->argument_list()->elements) {
      case 0:
	return (COND*) 0;
      case 1:
	return new_cond->argument_list()->head();
      default:


	if (new_cond->fix_fields(thd, 0))
          return (COND*) 0;
	new_cond->used_tables_cache=
	  ((Item_cond_and*) cond)->used_tables_cache &
	  tables;
	return new_cond;
      }
    }
    else
    {
      if (is_top_and_level && used_table == rand_table_bit &&
          (cond->used_tables() & ~OUTER_REF_TABLE_BIT) != rand_table_bit)
      {

        return (COND*) 0;
      }

      Item_cond_or *new_cond=new (thd->mem_root) Item_cond_or(thd);
      if (!new_cond)
	return (COND*) 0;
      List_iterator<Item> li(*((Item_cond*) cond)->argument_list());
      Item *item;
      while ((item=li++))
      {
	Item *fix=make_cond_for_table_from_pred(thd, root_cond, item,
                                                tables, 0L,
                                                join_tab_idx_arg,
                                                exclude_expensive_cond,
                                                retain_ref_cond, false);
	if (!fix)
	  return (COND*) 0;
	new_cond->argument_list()->push_back(fix, thd->mem_root);
      }


      new_cond->fix_fields(thd, 0);
      new_cond->used_tables_cache= ((Item_cond_or*) cond)->used_tables_cache;
      new_cond->top_level_item();
      return new_cond;
    }
  }

  if (is_top_and_level && used_table == rand_table_bit &&
      (cond->used_tables() & ~OUTER_REF_TABLE_BIT) != rand_table_bit)
  {

    return (COND*) 0;
  }


  if ((cond->marker == 3 && !retain_ref_cond) ||
      (cond->used_tables() & ~tables))
    return (COND*) 0;

  if (cond->marker == 2 || cond->eq_cmp_result() == Item::COND_OK)
  {
    cond->set_join_tab_idx(join_tab_idx_arg);
    return cond;
  }

  if (cond->type() == Item::FUNC_ITEM &&
      ((Item_func*) cond)->functype() == Item_func::EQ_FUNC)
  {
    Item *left_item=	((Item_func*) cond)->arguments()[0]->real_item();
    Item *right_item= ((Item_func*) cond)->arguments()[1]->real_item();
    if (left_item->type() == Item::FIELD_ITEM && !retain_ref_cond &&
	test_if_ref(root_cond, (Item_field*) left_item,right_item))
    {
      cond->marker=3;
      return (COND*) 0;
    }
    if (right_item->type() == Item::FIELD_ITEM && !retain_ref_cond &&
	test_if_ref(root_cond, (Item_field*) right_item,left_item))
    {
      cond->marker=3;
      return (COND*) 0;
    }
  }
  cond->marker=2;
  cond->set_join_tab_idx(join_tab_idx_arg);
  return cond;
}
