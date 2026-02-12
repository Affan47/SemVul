bool Item_in_subselect::inject_in_to_exists_cond(JOIN *join_arg)
{
  SELECT_LEX *select_lex= join_arg->select_lex;
  Item *where_item= join_arg->in_to_exists_where;
  Item *having_item= join_arg->in_to_exists_having;

  DBUG_ENTER("Item_in_subselect::inject_in_to_exists_cond");
  DBUG_ASSERT(thd == join_arg->thd);

  if (select_lex->min_max_opt_list.elements)
  {


    List_iterator_fast<Item_sum> it(select_lex->min_max_opt_list);
    Item_sum *item;
    while ((item= it++))
    {
      item->clear();
      item->reset_forced_const();
    }
    if (where_item)
      where_item->update_used_tables();
    if (having_item)
      having_item->update_used_tables();
  }

  if (where_item)
  {
    List<Item> *and_args= NULL;


    if (join_arg->conds && join_arg->conds->type() == Item::COND_ITEM &&
        ((Item_cond*) join_arg->conds)->functype() == Item_func::COND_AND_FUNC)
    {
      and_args= ((Item_cond*) join_arg->conds)->argument_list();
      if (join_arg->cond_equal)
        and_args->disjoin((List<Item> *) &join_arg->cond_equal->current_level);
    }

    where_item= and_items(thd, join_arg->conds, where_item);


    if (!where_item->fixed && where_item->fix_fields(thd, 0))
      DBUG_RETURN(true);

    thd->change_item_tree(&select_lex->where, where_item);
    select_lex->where->top_level_item();
    join_arg->conds= select_lex->where;


    if (and_args && join_arg->cond_equal)
    {


      and_args= ((Item_cond*) join_arg->conds)->argument_list();
      ((Item_cond_and *) (join_arg->conds))->m_cond_equal=
                                             *join_arg->cond_equal;
      and_args->append((List<Item> *)&join_arg->cond_equal->current_level);
    }
  }

  if (having_item)
  {
    Item* join_having= join_arg->having ? join_arg->having:join_arg->tmp_having;
    having_item= and_items(thd, join_having, having_item);
    if (fix_having(having_item, select_lex))
      DBUG_RETURN(true);

    thd->change_item_tree(&select_lex->having, having_item);
    select_lex->having->top_level_item();
    join_arg->having= select_lex->having;
  }
  join_arg->thd->change_item_tree(&unit->global_parameters()->select_limit,
                                  new (thd->mem_root)
                                  Item_int(thd, (int32) 1));
  unit->select_limit_cnt= 1;

  DBUG_RETURN(false);
}
