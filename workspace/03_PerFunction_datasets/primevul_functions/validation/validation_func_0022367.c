remove_const(JOIN *join,ORDER *first_order, COND *cond,
             bool change_list, bool *simple_order)
{
  *simple_order= join->rollup.state == ROLLUP::STATE_NONE;
  if (join->only_const_tables())
    return change_list ? 0 : first_order;

  ORDER *order,**prev_ptr, *tmp_order;
  table_map UNINIT_VAR(first_table);
  table_map not_const_tables= ~join->const_table_map;
  table_map ref;
  bool first_is_base_table= FALSE;
  DBUG_ENTER("remove_const");


  if (join->join_tab)
  {
    if (join->join_tab[join->const_tables].table)
    {
      first_table= join->join_tab[join->const_tables].table->map;
      first_is_base_table= TRUE;
    }


    for (JOIN_TAB *tab= join->join_tab + join->const_tables;
         tab < join->join_tab + join->table_count;
         tab++)
      tab->cached_eq_ref_table= FALSE;

    *simple_order= *join->join_tab[join->const_tables].on_expr_ref ? 0 : 1;
  }
  else
  {
    first_is_base_table= FALSE;
    first_table= 0;
  }

  prev_ptr= &first_order;


  update_depend_map_for_order(join, first_order);
  for (order=first_order; order ; order=order->next)
  {
    table_map order_tables=order->item[0]->used_tables();
    if (order->item[0]->with_sum_func ||
        order->item[0]->with_window_func ||


        (join->table_count > 1 && join->rollup.state == ROLLUP::STATE_INITED &&
        join->outer_join))
      *simple_order=0;
    else if (!(order_tables & not_const_tables))
    {
      if (order->item[0]->with_subquery())
      {


        join->exec_const_order_group_cond.push_back(order->item[0],
                                                    join->thd->mem_root);
      }
      DBUG_PRINT("info",("removing: %s", order->item[0]->full_name()));
      continue;
    }
    else
    {
      if (order_tables & (RAND_TABLE_BIT | OUTER_REF_TABLE_BIT))
	*simple_order=0;
      else
      {
	if (cond && const_expression_in_where(cond,order->item[0]))
	{
	  DBUG_PRINT("info",("removing: %s", order->item[0]->full_name()));
	  continue;
	}
	if (first_is_base_table &&
            (ref=order_tables & (not_const_tables ^ first_table)))
	{
	  if (!(order_tables & first_table) &&
              only_eq_ref_tables(join,first_order, ref))
	  {
	    DBUG_PRINT("info",("removing: %s", order->item[0]->full_name()));
	    continue;
	  }


          bool can_subst_to_first_table= false;
          bool first_is_in_sjm_nest= false;
          if (first_is_base_table)
          {
            TABLE_LIST *tbl_for_first=
              join->join_tab[join->const_tables].table->pos_in_table_list;
            first_is_in_sjm_nest= tbl_for_first->sj_mat_info &&
                                  tbl_for_first->sj_mat_info->is_used;
          }


          if (optimizer_flag(join->thd, OPTIMIZER_SWITCH_ORDERBY_EQ_PROP) &&
              first_is_base_table && !first_is_in_sjm_nest &&
              order->item[0]->real_item()->type() == Item::FIELD_ITEM &&
              join->cond_equal)
          {
            table_map first_table_bit=
              join->join_tab[join->const_tables].table->map;

            Item *item= order->item[0];


            Item *res= item->propagate_equal_fields(join->thd,
                                                    Value_source::
                                                    Context_identity(),
                                                    join->cond_equal);
            Item_equal *item_eq;
            if ((item_eq= res->get_item_equal()))
            {
              Item *first= item_eq->get_first(NO_PARTICULAR_TAB, NULL);
              if (first->const_item() || first->used_tables() ==
                                         first_table_bit)
              {
                can_subst_to_first_table= true;
              }
            }
          }

          if (!can_subst_to_first_table)
          {
            *simple_order=0;
          }
	}
      }
    }

    for (tmp_order= first_order;
         tmp_order != order;
         tmp_order= tmp_order->next)
    {
      if (tmp_order->item[0]->eq(order->item[0],1))
        break;
    }
    if (tmp_order != order)
      continue;

    if (change_list)
      *prev_ptr= order;
    prev_ptr= &order->next;
  }
  if (change_list)
    *prev_ptr=0;
  if (prev_ptr == &first_order)
    *simple_order=1;
#ifndef DBUG_OFF
  if (unlikely(join->thd->is_error()))
    DBUG_PRINT("error",("Error from remove_const"));
#endif
  DBUG_PRINT("exit",("simple_order: %d",(int) *simple_order));
  DBUG_RETURN(first_order);
}
