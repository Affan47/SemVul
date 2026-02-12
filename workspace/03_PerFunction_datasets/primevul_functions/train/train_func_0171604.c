Item *eliminate_item_equal(THD *thd, COND *cond, COND_EQUAL *upper_levels,
                           Item_equal *item_equal)
{
  List<Item> eq_list;
  Item_func_eq *eq_item= 0;
  if (((Item *) item_equal)->const_item() && !item_equal->val_int())
    return new (thd->mem_root) Item_bool(thd, false);
  Item *item_const= item_equal->get_const();
  Item_equal_fields_iterator it(*item_equal);
  Item *head;
  TABLE_LIST *current_sjm= NULL;
  Item *current_sjm_head= NULL;

  DBUG_ASSERT(!cond ||
              cond->is_bool_literal() ||
              (cond->type() == Item::FUNC_ITEM &&
               ((Item_func *) cond)->functype() == Item_func::EQ_FUNC) ||
              (cond->type() == Item::COND_ITEM  &&
               ((Item_func *) cond)->functype() == Item_func::COND_AND_FUNC));


  if (item_const)
    head= item_const;
  else
  {
    TABLE_LIST *emb_nest;
    head= item_equal->get_first(NO_PARTICULAR_TAB, NULL);
    it++;
    if ((emb_nest= embedding_sjm(head)))
    {
      current_sjm= emb_nest;
      current_sjm_head= head;
    }
  }

  Item *field_item;


  while ((field_item= it++))
  {
    Item_equal *upper= field_item->find_item_equal(upper_levels);
    Item *item= field_item;
    TABLE_LIST *field_sjm= embedding_sjm(field_item);
    if (!field_sjm)
    {
      current_sjm= NULL;
      current_sjm_head= NULL;
    }


    if (upper)
    {
      TABLE_LIST *native_sjm= embedding_sjm(item_equal->context_field);
      Item *upper_const= upper->get_const();
      if (item_const && upper_const)
      {


        Item_func_eq *func= new (thd->mem_root) Item_func_eq(thd, item_const, upper_const);
        func->set_cmp_func();
        func->quick_fix_field();
        if (func->val_int())
          item= 0;
      }
      else
      {
        Item_equal_fields_iterator li(*item_equal);
        while ((item= li++) != field_item)
        {
          if (embedding_sjm(item) == field_sjm &&
              item->find_item_equal(upper_levels) == upper)
            break;
        }
      }
      if (embedding_sjm(field_item) != native_sjm)
        item= NULL;
    }

    bool produce_equality= MY_TEST(item == field_item);
    if (!item_const && field_sjm && field_sjm != current_sjm)
    {

      current_sjm_head= field_item;
      if (!field_sjm->sj_mat_info->is_sj_scan)
        produce_equality= FALSE;
    }

    if (produce_equality)
    {
      if (eq_item && eq_list.push_back(eq_item, thd->mem_root))
        return 0;


      Item *head_item= (!item_const && current_sjm &&
                        current_sjm_head != field_item) ? current_sjm_head: head;
      eq_item= new (thd->mem_root) Item_func_eq(thd,
                                                field_item->remove_item_direct_ref(),
                                                head_item->remove_item_direct_ref());

      if (!eq_item || eq_item->set_cmp_func())
        return 0;
      eq_item->quick_fix_field();
    }
    current_sjm= field_sjm;
  }


  if (eq_item && eq_list.push_back(eq_item, thd->mem_root))
    return 0;
  COND *res= 0;
  switch (eq_list.elements)
  {
  case 0:
    res= cond ? cond : new (thd->mem_root) Item_bool(thd, true);
    break;
  case 1:
    if (!cond || cond->is_bool_literal())
      res= eq_item;
    break;
  default:
    break;
  }
  if (!res)
  {
    if (cond)
    {
      if (cond->type() == Item::COND_ITEM)
      {
        res= cond;
        ((Item_cond *) res)->add_at_end(&eq_list);
      }
      else if (eq_list.push_front(cond, thd->mem_root))
        return 0;
    }
  }
  if (!res)
    res= new (thd->mem_root) Item_cond_and(thd, eq_list);
  if (res)
  {
    res->quick_fix_field();
    res->update_used_tables();
  }

  return res;
}
