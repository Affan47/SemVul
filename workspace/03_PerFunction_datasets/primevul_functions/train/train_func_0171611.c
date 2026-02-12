COND *Item_func_eq::build_equal_items(THD *thd,
                                      COND_EQUAL *inherited,
                                      bool link_item_fields,
                                      COND_EQUAL **cond_equal_ref)
{
  COND_EQUAL cond_equal;
  cond_equal.upper_levels= inherited;
  List<Item> eq_list;

  DBUG_ASSERT(!cond_equal_ref || !cond_equal_ref[0]);


  if (Item_func_eq::check_equality(thd, &cond_equal, &eq_list))
  {
    Item_equal *item_equal;
    int n= cond_equal.current_level.elements + eq_list.elements;
    if (n == 0)
      return new (thd->mem_root) Item_bool(thd, true);
    else if (n == 1)
    {
      if ((item_equal= cond_equal.current_level.pop()))
      {
        item_equal->fix_fields(thd, NULL);
        item_equal->update_used_tables();
        set_if_bigger(thd->lex->current_select->max_equal_elems,
                      item_equal->n_field_items());
        item_equal->upper_levels= inherited;
        if (cond_equal_ref)
          *cond_equal_ref= new (thd->mem_root) COND_EQUAL(item_equal,
                                                          thd->mem_root);
        return item_equal;
      }
      Item *res= eq_list.pop();
      res->update_used_tables();
      DBUG_ASSERT(res->type() == FUNC_ITEM);
      return res;
    }
    else
    {


      Item_cond_and *and_cond= new (thd->mem_root) Item_cond_and(thd, eq_list);
      and_cond->quick_fix_field();
      List<Item> *cond_args= and_cond->argument_list();
      List_iterator_fast<Item_equal> it(cond_equal.current_level);
      while ((item_equal= it++))
      {
        if (item_equal->fix_length_and_dec())
          return NULL;
        item_equal->update_used_tables();
        set_if_bigger(thd->lex->current_select->max_equal_elems,
                      item_equal->n_field_items());
      }
      and_cond->m_cond_equal.copy(cond_equal);
      cond_equal.current_level= and_cond->m_cond_equal.current_level;
      cond_args->append((List<Item> *)&cond_equal.current_level);
      and_cond->update_used_tables();
      if (cond_equal_ref)
        *cond_equal_ref= &and_cond->m_cond_equal;
      return and_cond;
    }
  }
  return Item_func::build_equal_items(thd, inherited, link_item_fields,
                                      cond_equal_ref);
}
