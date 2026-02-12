JOIN::prepare(TABLE_LIST *tables_init,
	      uint wild_num, COND *conds_init, uint og_num,
	      ORDER *order_init, bool skip_order_by,
              ORDER *group_init, Item *having_init,
	      ORDER *proc_param_init, SELECT_LEX *select_lex_arg,
	      SELECT_LEX_UNIT *unit_arg)
{
  DBUG_ENTER("JOIN::prepare");


  if (optimization_state != JOIN::NOT_OPTIMIZED)
    DBUG_RETURN(0);

  conds= conds_init;
  order= order_init;
  group_list= group_init;
  having= having_init;
  proc_param= proc_param_init;
  tables_list= tables_init;
  select_lex= select_lex_arg;
  select_lex->join= this;
  join_list= &select_lex->top_join_list;
  union_part= unit_arg->is_unit_op();


  dbug_print_item(conds);

  if (select_lex->handle_derived(thd->lex, DT_PREPARE))
    DBUG_RETURN(-1);

  thd->lex->current_select->context_analysis_place= NO_MATTER;
  thd->lex->current_select->is_item_list_lookup= 1;


  if (!(select_options & OPTION_SETUP_TABLES_DONE) &&
      setup_tables_and_check_access(thd, &select_lex->context, join_list,
                                    tables_list, select_lex->leaf_tables,
                                    FALSE, SELECT_ACL, SELECT_ACL, FALSE))
      DBUG_RETURN(-1);


  if (select_lex->vers_setup_conds(thd, tables_list) < 0)
    DBUG_RETURN(-1);


  mixed_implicit_grouping= false;
  if ((~thd->variables.sql_mode & MODE_ONLY_FULL_GROUP_BY) &&
      select_lex->with_sum_func && !group_list)
  {
    List_iterator_fast <Item> select_it(fields_list);
    Item *select_el;
    bool found_field_elem= false;
    bool found_sum_func_elem= false;

    while ((select_el= select_it++))
    {
      if (select_el->with_sum_func)
        found_sum_func_elem= true;
      if (select_el->with_field)
        found_field_elem= true;
      if (found_sum_func_elem && found_field_elem)
      {
        mixed_implicit_grouping= true;
        break;
      }
    }
  }

  table_count= select_lex->leaf_tables.elements;

  TABLE_LIST *tbl;
  List_iterator_fast<TABLE_LIST> li(select_lex->leaf_tables);
  while ((tbl= li++))
  {


    if (mixed_implicit_grouping && tbl->table)
      tbl->table->maybe_null= 1;
  }

  uint real_og_num= og_num;
  if (skip_order_by &&
      select_lex != select_lex->master_unit()->global_parameters())
    real_og_num+= select_lex->order_list.elements;

  DBUG_ASSERT(select_lex->hidden_bit_fields == 0);
  if (setup_wild(thd, tables_list, fields_list, &all_fields, wild_num,
                 &select_lex->hidden_bit_fields))
    DBUG_RETURN(-1);
  if (select_lex->setup_ref_array(thd, real_og_num))
    DBUG_RETURN(-1);

  ref_ptrs= ref_ptr_array_slice(0);

  enum_parsing_place save_place=
                     thd->lex->current_select->context_analysis_place;
  thd->lex->current_select->context_analysis_place= SELECT_LIST;
  if (setup_fields(thd, ref_ptrs, fields_list, MARK_COLUMNS_READ,
                   &all_fields, &select_lex->pre_fix, 1))
    DBUG_RETURN(-1);
  thd->lex->current_select->context_analysis_place= save_place;

  if (setup_without_group(thd, ref_ptrs, tables_list,
                          select_lex->leaf_tables, fields_list,
                          all_fields, &conds, order, group_list,
                          select_lex->window_specs,
                          select_lex->window_funcs,
                          &hidden_group_fields,
                          &select_lex->select_n_reserved))
    DBUG_RETURN(-1);


  if (select_lex->master_unit()->item &&
      select_lex->first_cond_optimization &&
      !thd->lex->is_view_context_analysis())
  {
    remove_redundant_subquery_clauses(select_lex);
  }


  if (skip_order_by && select_lex !=
                       select_lex->master_unit()->global_parameters())
  {
    nesting_map save_allow_sum_func= thd->lex->allow_sum_func;
    thd->lex->allow_sum_func.set_bit(select_lex->nest_level);
    thd->where= "order clause";
    for (ORDER *order= select_lex->order_list.first; order; order= order->next)
    {


      if (find_order_in_list(thd, ref_ptrs, tables_list, order,
                             fields_list, all_fields, false, false, false))
        DBUG_RETURN(-1);
    }
    thd->lex->allow_sum_func= save_allow_sum_func;
    select_lex->order_list.empty();
  }

  if (having)
  {
    nesting_map save_allow_sum_func= thd->lex->allow_sum_func;
    thd->where="having clause";
    thd->lex->allow_sum_func.set_bit(select_lex_arg->nest_level);
    select_lex->having_fix_field= 1;


    if (having->type() == Item::REF_ITEM &&
        ((Item_ref *)having)->ref_type() == Item_ref::REF)
      wrap_ident(thd, &having);
    bool having_fix_rc= having->fix_fields_if_needed_for_bool(thd, &having);
    select_lex->having_fix_field= 0;

    if (unlikely(having_fix_rc || thd->is_error()))
      DBUG_RETURN(-1);
    thd->lex->allow_sum_func= save_allow_sum_func;

    if (having->with_window_func)
    {
      my_error(ER_WRONG_PLACEMENT_OF_WINDOW_FUNCTION, MYF(0));
      DBUG_RETURN(-1);
    }
  }


  if (select_lex->have_window_funcs())
  {
    List_iterator_fast<Item> it(select_lex->item_list);
    Item *item;
    while ((item= it++))
    {
      if (item->with_window_func)
        item->update_used_tables();
    }
  }

  With_clause *with_clause=select_lex->get_with_clause();
  if (with_clause && with_clause->prepare_unreferenced_elements(thd))
    DBUG_RETURN(1);

  With_element *with_elem= select_lex->get_with_element();
  if (with_elem &&
      select_lex->check_unrestricted_recursive(
                      thd->variables.only_standard_compliant_cte))
    DBUG_RETURN(-1);
  if (!(select_lex->changed_elements & TOUCHED_SEL_COND))
    select_lex->check_subqueries_with_recursive_references();

  int res= check_and_do_in_subquery_rewrites(this);

  select_lex->fix_prepare_information(thd, &conds, &having);

  if (res)
    DBUG_RETURN(res);

  if (order)
  {
    bool real_order= FALSE;
    ORDER *ord;
    for (ord= order; ord; ord= ord->next)
    {
      Item *item= *ord->item;


      if (!real_order &&

          ((item->type() != Item::FIELD_ITEM ||
            ((Item_field *) item)->field->maybe_null() ||
            ((Item_field *) item)->field->sort_length()) &&

           (item->type() != Item::FUNC_ITEM ||
            item->maybe_null ||
            item->result_type() != STRING_RESULT ||
            item->max_length)))
        real_order= TRUE;

      if ((item->with_sum_func && item->type() != Item::SUM_FUNC_ITEM) ||
          item->with_window_func)
        item->split_sum_func(thd, ref_ptrs, all_fields, SPLIT_SUM_SELECT);
    }
    if (!real_order)
      order= NULL;
  }

  if (having && having->with_sum_func)
    having->split_sum_func2(thd, ref_ptrs, all_fields,
                            &having, SPLIT_SUM_SKIP_REGISTERED);
  if (select_lex->inner_sum_func_list)
  {
    Item_sum *end=select_lex->inner_sum_func_list;
    Item_sum *item_sum= end;
    do
    {
      item_sum= item_sum->next;
      item_sum->split_sum_func2(thd, ref_ptrs,
                                all_fields, item_sum->ref_by, 0);
    } while (item_sum != end);
  }

  if (select_lex->inner_refs_list.elements &&
      fix_inner_refs(thd, all_fields, select_lex, ref_ptrs))
    DBUG_RETURN(-1);

  if (group_list)
  {


    for (ORDER *ord= group_list; ord; ord= ord->next)
    {
      if ((*ord->item)->type() == Item::FIELD_ITEM &&
          (*ord->item)->field_type() == MYSQL_TYPE_BIT)
      {
        Item_field *field= new (thd->mem_root) Item_field(thd, *(Item_field**)ord->item);
        if (!field)
          DBUG_RETURN(-1);
        int el= all_fields.elements;
        ref_ptrs[el]= field;
        all_fields.push_front(field, thd->mem_root);
        ord->item= &ref_ptrs[el];
      }
    }
  }


  if (thd->variables.sql_mode & MODE_ONLY_FULL_GROUP_BY && !group_list &&
      !(select_lex->master_unit()->item &&
        select_lex->master_unit()->item->is_in_predicate() &&
        ((Item_in_subselect*)select_lex->master_unit()->item)->
        test_set_strategy(SUBS_MAXMIN_INJECTED)) &&
      select_lex->non_agg_field_used() &&
      select_lex->agg_func_used())
  {
    my_message(ER_MIX_OF_GROUP_FUNC_AND_FIELDS,
               ER_THD(thd, ER_MIX_OF_GROUP_FUNC_AND_FIELDS), MYF(0));
    DBUG_RETURN(-1);
  }
  {

    send_group_parts= 0;
    for (ORDER *group_tmp= group_list ; group_tmp ; group_tmp= group_tmp->next)
      send_group_parts++;
  }

  procedure= setup_procedure(thd, proc_param, result, fields_list, &error);
  if (unlikely(error))
    goto err;
  if (procedure)
  {
    if (setup_new_fields(thd, fields_list, all_fields,
			 procedure->param_fields))
	goto err;
    if (procedure->group)
    {
      if (!test_if_subpart(procedure->group,group_list))
      {
	my_message(ER_DIFF_GROUPS_PROC, ER_THD(thd, ER_DIFF_GROUPS_PROC),
                   MYF(0));
	goto err;
      }
    }
    if (order && (procedure->flags & PROC_NO_SORT))
    {
      my_message(ER_ORDER_WITH_PROC, ER_THD(thd, ER_ORDER_WITH_PROC),
                 MYF(0));
      goto err;
    }
    if (thd->lex->derived_tables)
    {


      my_error(ER_WRONG_USAGE, MYF(0), "PROCEDURE",
               thd->lex->derived_tables & DERIVED_VIEW ?
               "view" : "subquery");
      goto err;
    }
    if (thd->lex->sql_command != SQLCOM_SELECT)
    {

      my_error(ER_WRONG_USAGE, MYF(0), "PROCEDURE", "non-SELECT");
      goto err;
    }
  }

  if (!procedure && result && result->prepare(fields_list, unit_arg))
    goto err;

  unit= unit_arg;
  if (prepare_stage2())
    goto err;

  DBUG_RETURN(0);

err:
  delete procedure;
  procedure= 0;
  DBUG_RETURN(-1);
}
