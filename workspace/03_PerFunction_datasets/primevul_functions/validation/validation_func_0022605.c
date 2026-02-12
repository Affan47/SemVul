Item_cond::remove_eq_conds(THD *thd, Item::cond_result *cond_value,
                           bool top_level_arg)
{
  bool and_level= functype() == Item_func::COND_AND_FUNC;
  List<Item> *cond_arg_list= argument_list();

  if (and_level)
  {


     List<Item_equal> *cond_equalities=
      &((Item_cond_and *) this)->m_cond_equal.current_level;
     cond_arg_list->disjoin((List<Item> *) cond_equalities);
     List_iterator<Item_equal> it(*cond_equalities);
     Item_equal *eq_item;
     while ((eq_item= it++))
     {
       if (eq_item->const_item() && eq_item->val_int())
         it.remove();
     }
     cond_arg_list->append((List<Item> *) cond_equalities);
  }

  List<Item_equal> new_equalities;
  List_iterator<Item> li(*cond_arg_list);
  bool should_fix_fields= 0;
  Item::cond_result tmp_cond_value;
  Item *item;


  *cond_value= cond_arg_list->elements ? Item::COND_UNDEF : Item::COND_TRUE;

  while ((item=li++))
  {
    Item *new_item= item->remove_eq_conds(thd, &tmp_cond_value, false);
    if (!new_item)
    {

      li.remove();
    }
    else if (item != new_item)
    {


      if (new_item->type() == Item::COND_ITEM &&
          item->type() == Item::COND_ITEM)
      {
        DBUG_ASSERT(functype() == ((Item_cond *) new_item)->functype());
        List<Item> *new_item_arg_list=
          ((Item_cond *) new_item)->argument_list();
        if (and_level)
        {


          List<Item_equal> *new_item_equalities=
            &((Item_cond_and *) new_item)->m_cond_equal.current_level;
          if (!new_item_equalities->is_empty())
          {


            new_item_arg_list->disjoin((List<Item> *) new_item_equalities);
            new_equalities.append(new_item_equalities);
          }
        }
        if (new_item_arg_list->is_empty())
          li.remove();
        else
        {
          uint cnt= new_item_arg_list->elements;
          li.replace(*new_item_arg_list);

          for (cnt--; cnt; cnt--)
            li++;
          should_fix_fields= 1;
        }
      }
      else if (and_level &&
               new_item->type() == Item::FUNC_ITEM &&
               ((Item_cond*) new_item)->functype() ==
                Item_func::MULT_EQUAL_FUNC)
      {
        li.remove();
        new_equalities.push_back((Item_equal *) new_item, thd->mem_root);
      }
      else
      {
        if (new_item->type() == Item::COND_ITEM &&
            ((Item_cond*) new_item)->functype() ==  functype())
        {
          List<Item> *new_item_arg_list=
            ((Item_cond *) new_item)->argument_list();
          uint cnt= new_item_arg_list->elements;
          li.replace(*new_item_arg_list);

          for (cnt--; cnt; cnt--)
            li++;
        }
        else
          li.replace(new_item);
        should_fix_fields= 1;
      }
    }
    if (*cond_value == Item::COND_UNDEF)
      *cond_value= tmp_cond_value;
    switch (tmp_cond_value) {
    case Item::COND_OK:
      if (and_level || *cond_value == Item::COND_FALSE)
        *cond_value=tmp_cond_value;
      break;
    case Item::COND_FALSE:
      if (and_level)
      {
        *cond_value= tmp_cond_value;
        return (COND*) 0;
      }
      break;
    case Item::COND_TRUE:
      if (!and_level)
      {
        *cond_value= tmp_cond_value;
        return (COND*) 0;
      }
      break;
    case Item::COND_UNDEF:
      break;
    }
  }
  COND *cond= this;
  if (!new_equalities.is_empty())
  {
    DBUG_ASSERT(and_level);


    COND_EQUAL *cond_equal= &((Item_cond_and *) this)->m_cond_equal;
    List<Item_equal> *cond_equalities= &cond_equal->current_level;
    cond_arg_list->disjoin((List<Item> *) cond_equalities);
    Item_equal *equality;
    List_iterator_fast<Item_equal> it(new_equalities);
    while ((equality= it++))
    {
      equality->upper_levels= cond_equal->upper_levels;
      equality->merge_into_list(thd, cond_equalities, false, false);
      List_iterator_fast<Item_equal> ei(*cond_equalities);
      while ((equality= ei++))
      {
        if (equality->const_item() && !equality->val_int())
        {
          *cond_value= Item::COND_FALSE;
          return (COND*) 0;
        }
      }
    }
    cond_arg_list->append((List<Item> *) cond_equalities);


    bool is_simplifiable_cond= false;
    propagate_new_equalities(thd, this, cond_equalities,
                             cond_equal->upper_levels,
                             &is_simplifiable_cond);


    if (is_simplifiable_cond)
    {
      if (!(cond= cond->remove_eq_conds(thd, cond_value, false)))
        return cond;
    }
    should_fix_fields= 1;
  }
  if (should_fix_fields)
    cond->update_used_tables();

  if (!((Item_cond*) cond)->argument_list()->elements ||
      *cond_value != Item::COND_OK)
    return (COND*) 0;
  if (((Item_cond*) cond)->argument_list()->elements == 1)
  {
    item= ((Item_cond*) cond)->argument_list()->head();
    ((Item_cond*) cond)->argument_list()->empty();
    return item;
  }
  *cond_value= Item::COND_OK;
  return cond;
}
