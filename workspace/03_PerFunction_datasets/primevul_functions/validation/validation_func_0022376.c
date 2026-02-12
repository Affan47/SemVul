COND *Item_cond::build_equal_items(THD *thd,
                                   COND_EQUAL *inherited,
                                   bool link_item_fields,
                                   COND_EQUAL **cond_equal_ref)
{
  List<Item> *cond_args= argument_list();

  List_iterator<Item> li(*cond_args);
  Item *item;

  DBUG_ASSERT(!cond_equal_ref || !cond_equal_ref[0]);


  used_tables_and_const_cache_init();
  while ((item= li++))
  {
    Item *new_item;
    if ((new_item= item->build_equal_items(thd, inherited, false, NULL))
        != item)
    {


      li.replace(new_item);
    }
    used_tables_and_const_cache_join(new_item);
  }
  return this;
}
