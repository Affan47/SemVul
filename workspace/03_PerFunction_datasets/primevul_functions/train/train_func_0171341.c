bool Item_allany_subselect::transform_into_max_min(JOIN *join)
{
  DBUG_ENTER("Item_allany_subselect::transform_into_max_min");
  if (!test_strategy(SUBS_MAXMIN_INJECTED | SUBS_MAXMIN_ENGINE))
    DBUG_RETURN(false);
  Item **place= optimizer->arguments() + 1;
  SELECT_LEX *select_lex= join->select_lex;
  Item *subs;
  DBUG_ASSERT(thd == join->thd);


  DBUG_ASSERT(!substitution);


  if (!select_lex->group_list.elements &&
      !select_lex->having &&
      !select_lex->with_sum_func &&
      !(select_lex->next_select()) &&
      select_lex->table_list.elements &&
      (!select_lex->ref_pointer_array[0]->maybe_null ||
       substype() != Item_subselect::ALL_SUBS))
  {
    Item_sum_hybrid *item;
    nesting_map save_allow_sum_func;
    if (func->l_op())
    {


      item= new (thd->mem_root) Item_sum_max(thd,
                                             select_lex->ref_pointer_array[0]);
    }
    else
    {


      item= new (thd->mem_root) Item_sum_min(thd,
                                             select_lex->ref_pointer_array[0]);
    }
    if (upper_item)
      upper_item->set_sum_test(item);
    thd->change_item_tree(&select_lex->ref_pointer_array[0], item);
    {
      List_iterator<Item> it(select_lex->item_list);
      it++;
      thd->change_item_tree(it.ref(), item);
    }

    DBUG_EXECUTE("where",
                 print_where(item, "rewrite with MIN/MAX", QT_ORDINARY););

    save_allow_sum_func= thd->lex->allow_sum_func;
    thd->lex->allow_sum_func|=
        (nesting_map)1 << thd->lex->current_select->nest_level;


    if (item->fix_fields(thd, 0))
      DBUG_RETURN(true);
    thd->lex->allow_sum_func= save_allow_sum_func;

    count_field_types(select_lex, &join->tmp_table_param, join->all_fields,
                      0);
    if (join->prepare_stage2())
      DBUG_RETURN(true);
    subs= new (thd->mem_root) Item_singlerow_subselect(thd, select_lex);


    set_strategy(SUBS_MAXMIN_INJECTED);
  }
  else
  {
    Item_maxmin_subselect *item;
    subs= item= new (thd->mem_root) Item_maxmin_subselect(thd, this, select_lex, func->l_op());
    if (upper_item)
      upper_item->set_sub_test(item);


    set_strategy(SUBS_MAXMIN_ENGINE);
  }


  subs= func->create_swap(thd, expr, subs);
  thd->change_item_tree(place, subs);
  if (subs->fix_fields(thd, &subs))
    DBUG_RETURN(true);
  DBUG_ASSERT(subs == (*place));

  select_lex->master_unit()->uncacheable&= ~UNCACHEABLE_DEPENDENT_INJECTED;
  select_lex->uncacheable&= ~UNCACHEABLE_DEPENDENT_INJECTED;

  DBUG_RETURN(false);
}
