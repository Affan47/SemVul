int JOIN::optimize_stage2()
{
  ulonglong select_opts_for_readinfo;
  uint no_jbuf_after;
  JOIN_TAB *tab;
  DBUG_ENTER("JOIN::optimize_stage2");

  if (subq_exit_fl)
    goto setup_subq_exit;

  if (unlikely(thd->check_killed()))
    DBUG_RETURN(1);


  if (get_best_combination())
    DBUG_RETURN(1);

  if (select_lex->handle_derived(thd->lex, DT_OPTIMIZE))
    DBUG_RETURN(1);

  if (optimizer_flag(thd, OPTIMIZER_SWITCH_DERIVED_WITH_KEYS))
    drop_unused_derived_keys();

  if (rollup.state != ROLLUP::STATE_NONE)
  {
    if (rollup_process_const_fields())
    {
      DBUG_PRINT("error", ("Error: rollup_process_fields() failed"));
      DBUG_RETURN(1);
    }
  }
  else
  {

    select_distinct= select_distinct && (const_tables != table_count);
  }

  THD_STAGE_INFO(thd, stage_preparing);
  if (result->initialize_tables(this))
  {
    DBUG_PRINT("error",("Error: initialize_tables() failed"));
    DBUG_RETURN(1);
  }
  if (const_table_map != found_const_table_map &&
      !(select_options & SELECT_DESCRIBE))
  {

    zero_result_cause= "no matching row in const table";
    DBUG_PRINT("error",("Error: %s", zero_result_cause));
    error= 0;
    handle_implicit_grouping_with_window_funcs();
    goto setup_subq_exit;
  }
  if (!(thd->variables.option_bits & OPTION_BIG_SELECTS) &&
      best_read > (double) thd->variables.max_join_size &&
      !(select_options & SELECT_DESCRIBE))
  {
    my_message(ER_TOO_BIG_SELECT, ER_THD(thd, ER_TOO_BIG_SELECT), MYF(0));
    error= -1;
    DBUG_RETURN(1);
  }
  if (const_tables && !thd->locked_tables_mode &&
      !(select_options & SELECT_NO_UNLOCK))
  {


    mysql_unlock_some_tables(thd, table, const_tables,
                             GET_LOCK_SKIP_SEQUENCES);
  }
  if (!conds && outer_join)
  {

    conds= new (thd->mem_root) Item_int(thd, (longlong) 1,1);
  }

  if (impossible_where)
  {
    zero_result_cause=
      "Impossible WHERE noticed after reading const tables";
    select_lex->mark_const_derived(zero_result_cause);
    handle_implicit_grouping_with_window_funcs();
    goto setup_subq_exit;
  }

  select= make_select(*table, const_table_map,
                      const_table_map, conds, (SORT_INFO*) 0, 1, &error);
  if (unlikely(error))
  {
    error= -1;
    DBUG_PRINT("error",("Error: make_select() failed"));
    DBUG_RETURN(1);
  }

  reset_nj_counters(this, join_list);
  if (make_outerjoin_info(this))
  {
    DBUG_RETURN(1);
  }


  if (conds)
  {
    conds= substitute_for_best_equal_field(thd, NO_PARTICULAR_TAB, conds,
                                           cond_equal, map2table);
    if (unlikely(thd->is_error()))
    {
      error= 1;
      DBUG_PRINT("error",("Error from substitute_for_best_equal"));
      DBUG_RETURN(1);
    }
    conds->update_used_tables();
    DBUG_EXECUTE("where",
                 print_where(conds,
                             "after substitute_best_equal",
                             QT_ORDINARY););
  }


  for (tab= first_linear_tab(this, WITH_BUSH_ROOTS, WITHOUT_CONST_TABLES); tab;
       tab= next_linear_tab(this, tab, WITH_BUSH_ROOTS))
  {
    if (*tab->on_expr_ref)
    {
      *tab->on_expr_ref= substitute_for_best_equal_field(thd, NO_PARTICULAR_TAB,
                                                         *tab->on_expr_ref,
                                                         tab->cond_equal,
                                                         map2table);
      if (unlikely(thd->is_error()))
      {
        error= 1;
        DBUG_PRINT("error",("Error from substitute_for_best_equal"));
        DBUG_RETURN(1);
      }
      (*tab->on_expr_ref)->update_used_tables();
    }
  }


  for (tab= first_linear_tab(this, WITH_BUSH_ROOTS, WITHOUT_CONST_TABLES); tab;
       tab= next_linear_tab(this, tab, WITH_BUSH_ROOTS))
  {
    uint key_copy_index=0;
    for (uint i=0; i < tab->ref.key_parts; i++)
    {
      Item **ref_item_ptr= tab->ref.items+i;
      Item *ref_item= *ref_item_ptr;
      if (!ref_item->used_tables() && !(select_options & SELECT_DESCRIBE))
        continue;
      COND_EQUAL *equals= cond_equal;
      JOIN_TAB *first_inner= tab->first_inner;
      while (equals)
      {
        ref_item= substitute_for_best_equal_field(thd, tab, ref_item,
                                                  equals, map2table);
        if (unlikely(thd->is_fatal_error))
          DBUG_RETURN(1);

        if (first_inner)
	{
          equals= first_inner->cond_equal;
          first_inner= first_inner->first_upper;
        }
        else
          equals= 0;
      }
      ref_item->update_used_tables();
      if (*ref_item_ptr != ref_item)
      {
        *ref_item_ptr= ref_item;
        Item *item= ref_item->real_item();
        store_key *key_copy= tab->ref.key_copy[key_copy_index];
        if (key_copy->type() == store_key::FIELD_STORE_KEY)
        {
          if (item->basic_const_item())
          {

            tab->ref.key_copy[key_copy_index]=
              new store_key_const_item(*tab->ref.key_copy[key_copy_index],
                                       item);
          }
          else if (item->const_item())
	  {
            tab->ref.key_copy[key_copy_index]=
              new store_key_item(*tab->ref.key_copy[key_copy_index],
                                 item, TRUE);
          }
          else
          {
            store_key_field *field_copy= ((store_key_field *)key_copy);
            DBUG_ASSERT(item->type() == Item::FIELD_ITEM);
            field_copy->change_source_field((Item_field *) item);
          }
        }
      }
      key_copy_index++;
    }
  }

  if (conds && const_table_map != found_const_table_map &&
      (select_options & SELECT_DESCRIBE))
  {
    conds=new (thd->mem_root) Item_int(thd, (longlong) 0, 1);
  }


  cache_const_exprs();

  if (setup_semijoin_loosescan(this))
    DBUG_RETURN(1);

  if (make_join_select(this, select, conds))
  {
    zero_result_cause=
      "Impossible WHERE noticed after reading const tables";
    select_lex->mark_const_derived(zero_result_cause);
    handle_implicit_grouping_with_window_funcs();
    goto setup_subq_exit;
  }

  error= -1;


  {
    ORDER *org_order= order;
    order=remove_const(this, order,conds,1, &simple_order);
    if (unlikely(thd->is_error()))
    {
      error= 1;
      DBUG_RETURN(1);
    }


    if (!order && org_order)
      skip_sort_order= 1;
  }


  if (table_count - const_tables == 1 && (group || select_distinct) &&
      !tmp_table_param.sum_func_count &&
      (!join_tab[const_tables].select ||
       !join_tab[const_tables].select->quick ||
       join_tab[const_tables].select->quick->get_type() !=
       QUICK_SELECT_I::QS_TYPE_GROUP_MIN_MAX) &&
      !select_lex->have_window_funcs())
  {
    if (group && rollup.state == ROLLUP::STATE_NONE &&
       list_contains_unique_index(join_tab[const_tables].table,
                                 find_field_in_order_list,
                                 (void *) group_list))
    {


      if (!order || test_if_subpart(group_list, order))
      {
        if (skip_sort_order ||
            (select_lex->master_unit()->item && select_limit == HA_POS_ERROR))
          order= NULL;
        else
          order= group_list;
      }


      join_tab->table->keys_in_use_for_order_by=
        join_tab->table->keys_in_use_for_group_by;
      group_list= 0;
      group= 0;
    }
    if (select_distinct &&
       list_contains_unique_index(join_tab[const_tables].table,
                                 find_field_in_item_list,
                                 (void *) &fields_list))
    {
      select_distinct= 0;
    }
  }
  if (group || tmp_table_param.sum_func_count)
  {
    if (! hidden_group_fields && rollup.state == ROLLUP::STATE_NONE
        && !select_lex->have_window_funcs())
      select_distinct=0;
  }
  else if (select_distinct && table_count - const_tables == 1 &&
           rollup.state == ROLLUP::STATE_NONE &&
           !select_lex->have_window_funcs())
  {


    bool all_order_fields_used;

    tab= &join_tab[const_tables];
    if (order)
    {
      skip_sort_order=
        test_if_skip_sort_order(tab, order, select_limit,
                                true,
                                &tab->table->keys_in_use_for_order_by);
    }
    if ((group_list=create_distinct_group(thd, select_lex->ref_pointer_array,
                                          order, fields_list, all_fields,
				          &all_order_fields_used)))
    {
      const bool skip_group=
        skip_sort_order &&
        test_if_skip_sort_order(tab, group_list, select_limit,
                                  true,
                                  &tab->table->keys_in_use_for_group_by);
      count_field_types(select_lex, &tmp_table_param, all_fields, 0);
      if ((skip_group && all_order_fields_used) ||
	  select_limit == HA_POS_ERROR ||
	  (order && !skip_sort_order))
      {

	select_distinct= 0;
	no_order= !order;
	if (all_order_fields_used)
	{
	  if (order && skip_sort_order)
	  {


	    tmp_table_param.quick_group=0;
	  }
	  order=0;
        }
	group=1;
      }
      else
	group_list= 0;
    }
    else if (thd->is_fatal_error)
      DBUG_RETURN(1);
  }
  simple_group= rollup.state == ROLLUP::STATE_NONE;
  if (group)
  {


    group_list= remove_const(this, group_list, conds,
                             rollup.state == ROLLUP::STATE_NONE,
                             &simple_group);
    if (unlikely(thd->is_error()))
    {
      error= 1;
      DBUG_RETURN(1);
    }
    if (!group_list)
    {

      order=0;
      simple_order=1;
      select_distinct= 0;
      group_optimized_away= 1;
    }
  }

  calc_group_buffer(this, group_list);
  send_group_parts= tmp_table_param.group_parts;
  if (procedure && procedure->group)
  {
    group_list= procedure->group= remove_const(this, procedure->group, conds,
					       1, &simple_group);
    if (unlikely(thd->is_error()))
    {
      error= 1;
      DBUG_RETURN(1);
    }
    calc_group_buffer(this, group_list);
  }

  if (test_if_subpart(group_list, order) ||
      (!group_list && tmp_table_param.sum_func_count))
  {
    order=0;
    if (is_indexed_agg_distinct(this, NULL))
      sort_and_group= 0;
  }


  if (full_join || hash_join)
  {
    TABLE *stable= (sort_by_table == (TABLE *) 1 ?
      join_tab[const_tables].table : sort_by_table);


    if (!stable || (!stable->force_index_order &&
                    !map2table[stable->tablenr]->keep_current_rowid))
    {
      if (group_list)
        simple_group= 0;
      if (order)
        simple_order= 0;
    }
  }

  need_tmp= test_if_need_tmp_table();


  if (select_lex->have_window_funcs())
    simple_order= FALSE;


  no_jbuf_after= 1 ? table_count : make_join_orderinfo(this);


  select_opts_for_readinfo=
    (select_options & (SELECT_DESCRIBE | SELECT_NO_JOIN_CACHE)) |
    (select_lex->ftfunc_list->elements ?  SELECT_NO_JOIN_CACHE : 0);

  if (select_lex->options & OPTION_SCHEMA_TABLE &&
       optimize_schema_tables_reads(this))
    DBUG_RETURN(1);

  if (make_join_readinfo(this, select_opts_for_readinfo, no_jbuf_after))
    DBUG_RETURN(1);


  if (!(select_options & SELECT_DESCRIBE))
    if (init_ftfuncs(thd, select_lex, MY_TEST(order)))
      DBUG_RETURN(1);


  if (having && const_table_map && !having->with_sum_func)
  {
    having->update_used_tables();
    having= having->remove_eq_conds(thd, &select_lex->having_value, true);
    if (select_lex->having_value == Item::COND_FALSE)
    {
      having= new (thd->mem_root) Item_int(thd, (longlong) 0,1);
      zero_result_cause= "Impossible HAVING noticed after reading const tables";
      error= 0;
      select_lex->mark_const_derived(zero_result_cause);
      goto setup_subq_exit;
    }
  }

  if (optimize_unflattened_subqueries())
    DBUG_RETURN(1);

  int res;
  if ((res= rewrite_to_index_subquery_engine(this)) != -1)
    DBUG_RETURN(res);
  if (setup_subquery_caches())
    DBUG_RETURN(-1);


  if (need_tmp || select_distinct || group_list || order)
  {
    for (uint i= 0; i < table_count; i++)
    {
      if (!(table[i]->map & const_table_map))
        table[i]->prepare_for_position();
    }
  }

  DBUG_EXECUTE("info",TEST_join(this););

  if (!only_const_tables())
  {
     JOIN_TAB *tab= &join_tab[const_tables];

    if (order)
    {


      for (ORDER *tmp_order= order; tmp_order ; tmp_order=tmp_order->next)
      {
        Item *item= *tmp_order->item;
        if (item->is_expensive())
        {

          need_tmp=1; simple_order=simple_group=0;
          break;
        }
      }
    }


    if ((order || group_list) &&
        tab->type != JT_ALL &&
        tab->type != JT_FT &&
        tab->type != JT_REF_OR_NULL &&
        ((order && simple_order) || (group_list && simple_group)))
    {
      if (add_ref_to_table_cond(thd,tab)) {
        DBUG_RETURN(1);
      }
    }


    DBUG_ASSERT(ordered_index_usage == ordered_index_void);

    if (group_list)

    {


      if (!(select_options & SELECT_BIG_RESULT) ||
            (tab->select &&
             tab->select->quick &&
             tab->select->quick->get_type() ==
             QUICK_SELECT_I::QS_TYPE_GROUP_MIN_MAX))
      {
        if (simple_group &&
            !select_distinct)
        {


          const ha_rows limit = need_tmp ? HA_POS_ERROR : select_limit;
          if (test_if_skip_sort_order(tab, group_list, limit, false,
                                      &tab->table->keys_in_use_for_group_by))
          {
            ordered_index_usage= ordered_index_group_by;
          }
        }


        if ((ordered_index_usage != ordered_index_group_by) &&
            ((tmp_table_param.quick_group && !procedure) ||
	     (tab->emb_sj_nest &&
	      best_positions[const_tables].sj_strategy == SJ_OPT_LOOSE_SCAN)))
        {
          need_tmp=1;
          simple_order= simple_group= false;
        }
      }
    }
    else if (order &&
             (simple_order || skip_sort_order))
    {
      if (test_if_skip_sort_order(tab, order, select_limit, false,
                                  &tab->table->keys_in_use_for_order_by))
      {
        ordered_index_usage= ordered_index_order_by;
      }
    }
  }

  if (having)
    having_is_correlated= MY_TEST(having->used_tables() & OUTER_REF_TABLE_BIT);
  tmp_having= having;

  if (unlikely(thd->is_error()))
    DBUG_RETURN(TRUE);


  if (join_tab->is_using_loose_index_scan())
  {
    tmp_table_param.precomputed_group_by= TRUE;
    if (join_tab->is_using_agg_loose_index_scan())
    {
      need_distinct= FALSE;
      tmp_table_param.precomputed_group_by= FALSE;
    }
  }

  if (make_aggr_tables_info())
    DBUG_RETURN(1);

  if (init_join_caches())
    DBUG_RETURN(1);

  error= 0;

  if (select_options & SELECT_DESCRIBE)
    goto derived_exit;

  DBUG_RETURN(0);

setup_subq_exit:

  if (!tables_list || !table_count)
  {
    choose_tableless_subquery_plan();


    if (group_list)
    {
      group_list= NULL;
      group_optimized_away= 1;
      rollup.state= ROLLUP::STATE_NONE;
    }
    order= NULL;
    simple_order= TRUE;
    select_distinct= FALSE;

    if (select_lex->have_window_funcs())
    {
      if (!(join_tab= (JOIN_TAB*) thd->alloc(sizeof(JOIN_TAB))))
        DBUG_RETURN(1);
      need_tmp= 1;
    }
    if (make_aggr_tables_info())
      DBUG_RETURN(1);
  }


  if (optimize_unflattened_subqueries())
    DBUG_RETURN(1);
  error= 0;

derived_exit:

  select_lex->mark_const_derived(zero_result_cause);
  DBUG_RETURN(0);
}
