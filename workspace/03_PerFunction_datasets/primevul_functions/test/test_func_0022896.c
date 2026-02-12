void SELECT_LEX::update_used_tables()
{
  TABLE_LIST *tl;
  List_iterator<TABLE_LIST> ti(leaf_tables);

  while ((tl= ti++))
  {
    if (tl->table && !tl->is_view_or_derived())
    {
      TABLE_LIST *embedding= tl->embedding;
      for (embedding= tl->embedding; embedding; embedding=embedding->embedding)
      {
        if (embedding->is_view_or_derived())
	{
          DBUG_ASSERT(embedding->is_merged_derived());
          TABLE *tab= tl->table;
          tab->covering_keys= tab->s->keys_for_keyread;
          tab->covering_keys.intersect(tab->keys_in_use_for_query);


          bitmap_clear_all(tab->read_set);
          if (tab->vcol_set)
            bitmap_clear_all(tab->vcol_set);
          break;
        }
      }
    }
  }

  ti.rewind();
  while ((tl= ti++))
  {
    TABLE_LIST *embedding= tl;
    do
    {
      bool maybe_null;
      if ((maybe_null= MY_TEST(embedding->outer_join)))
      {
	tl->table->maybe_null= maybe_null;
        break;
      }
    }
    while ((embedding= embedding->embedding));
    if (tl->on_expr)
    {
      tl->on_expr->update_used_tables();
      tl->on_expr->walk(&Item::eval_not_null_tables, 0, NULL);
    }


    if (tl->jtbm_subselect)
    {
      Item *left_expr= tl->jtbm_subselect->left_expr;
      left_expr->walk(&Item::update_table_bitmaps_processor, FALSE, NULL);
    }

    embedding= tl->embedding;
    while (embedding)
    {
      if (embedding->on_expr &&
          embedding->nested_join->join_list.head() == tl)
      {
        embedding->on_expr->update_used_tables();
        embedding->on_expr->walk(&Item::eval_not_null_tables, 0, NULL);
      }
      tl= embedding;
      embedding= tl->embedding;
    }
  }

  if (join->conds)
  {
    join->conds->update_used_tables();
    join->conds->walk(&Item::eval_not_null_tables, 0, NULL);
  }
  if (join->having)
  {
    join->having->update_used_tables();
  }

  Item *item;
  List_iterator_fast<Item> it(join->all_fields);
  select_list_tables= 0;
  while ((item= it++))
  {
    item->update_used_tables();
    select_list_tables|= item->used_tables();
  }
  Item_outer_ref *ref;
  List_iterator_fast<Item_outer_ref> ref_it(inner_refs_list);
  while ((ref= ref_it++))
  {
    item= ref->outer_ref;
    item->update_used_tables();
  }
  for (ORDER *order= group_list.first; order; order= order->next)
    (*order->item)->update_used_tables();
  if (!master_unit()->is_union() || master_unit()->global_parameters() != this)
  {
    for (ORDER *order= order_list.first; order; order= order->next)
      (*order->item)->update_used_tables();
  }
  join->result->update_used_tables();
}
