make_cond_after_sjm(THD *thd, Item *root_cond, Item *cond, table_map tables,
                    table_map sjm_tables, bool inside_or_clause)
{


  if (!inside_or_clause)
  {
    table_map cond_used_tables= cond->used_tables();
    if((!(cond_used_tables & ~tables) ||
       !(cond_used_tables & ~sjm_tables)))
      return (COND*) 0;
  }


  if (cond->type() == Item::COND_ITEM)
  {
    if (((Item_cond*) cond)->functype() == Item_func::COND_AND_FUNC)
    {

      Item_cond_and *new_cond= new (thd->mem_root) Item_cond_and(thd);
      if (!new_cond)
	return (COND*) 0;
      List_iterator<Item> li(*((Item_cond*) cond)->argument_list());
      Item *item;
      while ((item=li++))
      {
        Item *fix=make_cond_after_sjm(thd, root_cond, item, tables, sjm_tables,
                                      inside_or_clause);
	if (fix)
	  new_cond->argument_list()->push_back(fix, thd->mem_root);
      }
      switch (new_cond->argument_list()->elements) {
      case 0:
	return (COND*) 0;
      case 1:
	return new_cond->argument_list()->head();
      default:


	new_cond->quick_fix_field();
	new_cond->used_tables_cache=
	  ((Item_cond_and*) cond)->used_tables_cache &
	  tables;
	return new_cond;
      }
    }
    else
    {
      Item_cond_or *new_cond= new (thd->mem_root) Item_cond_or(thd);
      if (!new_cond)
	return (COND*) 0;
      List_iterator<Item> li(*((Item_cond*) cond)->argument_list());
      Item *item;
      while ((item=li++))
      {
        Item *fix= make_cond_after_sjm(thd, root_cond, item, tables, sjm_tables,
                                       TRUE);
	if (!fix)
	  return (COND*) 0;
	new_cond->argument_list()->push_back(fix, thd->mem_root);
      }


      new_cond->quick_fix_field();
      new_cond->used_tables_cache= ((Item_cond_or*) cond)->used_tables_cache;
      new_cond->top_level_item();
      return new_cond;
    }
  }


  if (cond->marker == 3 || (cond->used_tables() & ~(tables | sjm_tables)))
    return (COND*) 0;
  if (cond->marker == 2 || cond->eq_cmp_result() == Item::COND_OK)
    return cond;


  if (((Item_func*) cond)->functype() == Item_func::EQ_FUNC)
  {
    Item *left_item= ((Item_func*) cond)->arguments()[0]->real_item();
    Item *right_item= ((Item_func*) cond)->arguments()[1]->real_item();
    if (left_item->type() == Item::FIELD_ITEM &&
	test_if_ref(root_cond, (Item_field*) left_item,right_item))
    {
      cond->marker=3;
      return (COND*) 0;
    }
    if (right_item->type() == Item::FIELD_ITEM &&
	test_if_ref(root_cond, (Item_field*) right_item,left_item))
    {
      cond->marker=3;
      return (COND*) 0;
    }
  }
  cond->marker=2;
  return cond;
}
