bool JOIN::make_aggr_tables_info()
{
  List<Item> *curr_all_fields= &all_fields;
  List<Item> *curr_fields_list= &fields_list;
  JOIN_TAB *curr_tab= join_tab + const_tables;
  TABLE *exec_tmp_table= NULL;
  bool distinct= false;
  bool keep_row_order= false;
  bool is_having_added_as_table_cond= false;
  DBUG_ENTER("JOIN::make_aggr_tables_info");

  const bool has_group_by= this->group;

  sort_and_group_aggr_tab= NULL;

  if (group_optimized_away)
    implicit_grouping= true;

  bool implicit_grouping_with_window_funcs= implicit_grouping &&
                                            select_lex->have_window_funcs();
  bool implicit_grouping_without_tables= implicit_grouping &&
                                         !tables_list;


  if (join_tab && top_join_tab_count && tables_list)
  {
    join_tab[top_join_tab_count - 1].fields= &fields_list;
    join_tab[top_join_tab_count - 1].all_fields= &all_fields;
  }


  if (tables_list && (tmp_table_param.sum_func_count || group_list) &&
      !procedure)
  {


    TABLE_LIST *tbl= tables_list;
    handlerton *ht= tbl && tbl->table ? tbl->table->file->ht : 0;
    for (tbl= tbl->next_local; ht && tbl; tbl= tbl->next_local)
    {
      if (!tbl->table || tbl->table->file->ht != ht)
        ht= 0;
    }

    if (ht && ht->create_group_by)
    {

      Query query= {&all_fields, select_distinct, tables_list, conds,
                    group_list, order ? order : group_list, having};
      group_by_handler *gbh= ht->create_group_by(thd, &query);

      if (gbh)
      {
        pushdown_query= new (thd->mem_root) Pushdown_query(select_lex, gbh);


        need_tmp= query.order_by || query.group_by || query.distinct;
        distinct= query.distinct;
        keep_row_order= query.order_by || query.group_by;

        order= query.order_by;

        aggr_tables++;
        curr_tab= join_tab + exec_join_tab_cnt();
        bzero((void*)curr_tab, sizeof(JOIN_TAB));
        curr_tab->ref.key= -1;
        curr_tab->join= this;

        curr_tab->tmp_table_param= new TMP_TABLE_PARAM(tmp_table_param);
        TABLE* table= create_tmp_table(thd, curr_tab->tmp_table_param,
                                       all_fields,
                                       NULL, query.distinct,
                                       TRUE, select_options, HA_POS_ERROR,
                                       "", !need_tmp,
                                       query.order_by || query.group_by);
        if (!table)
          DBUG_RETURN(1);

        curr_tab->aggr= new (thd->mem_root) AGGR_OP(curr_tab);
        curr_tab->aggr->set_write_func(::end_send);
        curr_tab->table= table;


        init_items_ref_array();
        items1= ref_ptr_array_slice(2);

        if (change_to_use_tmp_fields(thd, items1,
                                     tmp_fields_list1, tmp_all_fields1,
                                     fields_list.elements, all_fields))
          DBUG_RETURN(1);


        gbh->table= table;
        pushdown_query->store_data_in_temp_table= need_tmp;
        pushdown_query->having= having;


        DBUG_ASSERT(query.group_by == NULL);
        group= 0; group_list= 0;
        having= tmp_having= 0;


        select_distinct= 0;
        order= query.order_by;
        tmp_table_param.field_count+= tmp_table_param.sum_func_count;
        tmp_table_param.sum_func_count= 0;

        fields= curr_fields_list;


        curr_tab->ref_array= &items1;
        curr_tab->all_fields= &tmp_all_fields1;
        curr_tab->fields= &tmp_fields_list1;

        DBUG_RETURN(thd->is_fatal_error);
      }
    }
  }


  if (join_tab && top_join_tab_count && tables_list &&
      join_tab->is_using_loose_index_scan())
    tmp_table_param.precomputed_group_by=
      !join_tab->is_using_agg_loose_index_scan();

  group_list_for_estimates= group_list;

  if (need_tmp)
  {
    aggr_tables++;
    curr_tab= join_tab + exec_join_tab_cnt();
    bzero((void*)curr_tab, sizeof(JOIN_TAB));
    curr_tab->ref.key= -1;
    if (only_const_tables())
      first_select= sub_select_postjoin_aggr;


    init_items_ref_array();

    ORDER *tmp_group= (ORDER *) 0;
    if (!simple_group && !procedure && !(test_flags & TEST_NO_KEY_GROUP))
      tmp_group= group_list;

    tmp_table_param.hidden_field_count=
      all_fields.elements - fields_list.elements;

    distinct= select_distinct && !group_list &&
              !select_lex->have_window_funcs();
    keep_row_order= false;
    bool save_sum_fields= (group_list && simple_group) ||
                           implicit_grouping_with_window_funcs;
    if (create_postjoin_aggr_table(curr_tab,
                                   &all_fields, tmp_group,
                                   save_sum_fields,
                                   distinct, keep_row_order))
      DBUG_RETURN(true);
    exec_tmp_table= curr_tab->table;

    if (exec_tmp_table->distinct)
      optimize_distinct();


    items1= ref_ptr_array_slice(2);
    if ((sort_and_group || curr_tab->table->group ||
         tmp_table_param.precomputed_group_by) &&
         !implicit_grouping_without_tables)
    {
      if (change_to_use_tmp_fields(thd, items1,
                                   tmp_fields_list1, tmp_all_fields1,
                                   fields_list.elements, all_fields))
        DBUG_RETURN(true);
    }
    else
    {
      if (change_refs_to_tmp_fields(thd, items1,
                                    tmp_fields_list1, tmp_all_fields1,
                                    fields_list.elements, all_fields))
        DBUG_RETURN(true);
    }
    curr_all_fields= &tmp_all_fields1;
    curr_fields_list= &tmp_fields_list1;

    set_items_ref_array(items1);
    curr_tab->ref_array= &items1;
    curr_tab->all_fields= &tmp_all_fields1;
    curr_tab->fields= &tmp_fields_list1;
    set_postjoin_aggr_write_func(curr_tab);


    if (tmp_having &&
        (sort_and_group || (exec_tmp_table->distinct && !group_list) ||
	 select_lex->have_window_funcs()))
    {


      if (!select_distinct && !select_lex->have_window_funcs() &&
          add_having_as_table_cond(curr_tab))
        DBUG_RETURN(true);
      is_having_added_as_table_cond= tmp_having != having;


      curr_tab->having= having;
      having= NULL;
    }

    tmp_table_param.func_count= 0;
    tmp_table_param.field_count+= tmp_table_param.func_count;
    if (sort_and_group || curr_tab->table->group)
    {
      tmp_table_param.field_count+= tmp_table_param.sum_func_count;
      tmp_table_param.sum_func_count= 0;
    }

    if (exec_tmp_table->group)
    {
      if (!order && !no_order && !skip_sort_order)
        order= group_list;
      group_list= NULL;
    }


    if ((group_list &&
         (!test_if_subpart(group_list, order) || select_distinct)) ||
        (select_distinct && tmp_table_param.using_outer_summary_function))
    {
      DBUG_PRINT("info",("Creating group table"));

      calc_group_buffer(this, group_list);
      count_field_types(select_lex, &tmp_table_param, tmp_all_fields1,
                        select_distinct && !group_list);
      tmp_table_param.hidden_field_count=
        tmp_all_fields1.elements - tmp_fields_list1.elements;

      curr_tab++;
      aggr_tables++;
      bzero((void*)curr_tab, sizeof(JOIN_TAB));
      curr_tab->ref.key= -1;


      if (join_tab->is_using_loose_index_scan())
        tmp_table_param.precomputed_group_by= TRUE;

      tmp_table_param.hidden_field_count=
        curr_all_fields->elements - curr_fields_list->elements;
      ORDER *dummy= NULL;

      if (create_postjoin_aggr_table(curr_tab,
                                     curr_all_fields, dummy, true,
                                     distinct, keep_row_order))
	DBUG_RETURN(true);

      if (group_list)
      {
        if (!only_const_tables())
        {
          if (add_sorting_to_table(curr_tab - 1, group_list))
            DBUG_RETURN(true);
        }

        if (make_group_fields(this, this))
          DBUG_RETURN(true);
      }


      if (group_list || tmp_table_param.sum_func_count)
      {
        if (make_sum_func_list(*curr_all_fields, *curr_fields_list, true, true))
          DBUG_RETURN(true);
        if (prepare_sum_aggregators(sum_funcs,
                                    !join_tab->is_using_agg_loose_index_scan()))
          DBUG_RETURN(true);
        group_list= NULL;
        if (setup_sum_funcs(thd, sum_funcs))
          DBUG_RETURN(true);
      }

      DBUG_ASSERT(items2.is_null());

      items2= ref_ptr_array_slice(3);
      if (change_to_use_tmp_fields(thd, items2,
                                   tmp_fields_list2, tmp_all_fields2,
                                   fields_list.elements, tmp_all_fields1))
        DBUG_RETURN(true);

      curr_fields_list= &tmp_fields_list2;
      curr_all_fields= &tmp_all_fields2;
      set_items_ref_array(items2);
      curr_tab->ref_array= &items2;
      curr_tab->all_fields= &tmp_all_fields2;
      curr_tab->fields= &tmp_fields_list2;
      set_postjoin_aggr_write_func(curr_tab);

      tmp_table_param.field_count+= tmp_table_param.sum_func_count;
      tmp_table_param.sum_func_count= 0;
    }
    if (curr_tab->table->distinct)
      select_distinct= false;

    if (select_distinct && !group_list)
    {
      if (having)
      {
        curr_tab->having= having;
        having->update_used_tables();
      }


      if (top_join_tab_count && tables_list)
        curr_tab->distinct= true;

      having= NULL;
      select_distinct= false;
    }

    tmp_table_param.field_count= tmp_table_param.sum_func_count=
      tmp_table_param.func_count= 0;

    tmp_table_param.copy_field= tmp_table_param.copy_field_end=0;
    first_record= sort_and_group=0;

    if (!group_optimized_away || implicit_grouping_with_window_funcs)
    {
      group= false;
    }
    else
    {


      DBUG_ASSERT(MY_TEST(select_options & OPTION_BUFFER_RESULT));

      DBUG_ASSERT(!curr_tab->table->group);
    }
    calc_group_buffer(this, group_list);
    count_field_types(select_lex, &tmp_table_param, *curr_all_fields, false);
  }

  if (group ||
      (implicit_grouping  && !implicit_grouping_with_window_funcs) ||
      tmp_table_param.sum_func_count)
  {
    if (make_group_fields(this, this))
      DBUG_RETURN(true);

    DBUG_ASSERT(items3.is_null());

    if (items0.is_null())
      init_items_ref_array();
    items3= ref_ptr_array_slice(4);
    setup_copy_fields(thd, &tmp_table_param,
                      items3, tmp_fields_list3, tmp_all_fields3,
                      curr_fields_list->elements, *curr_all_fields);

    curr_fields_list= &tmp_fields_list3;
    curr_all_fields= &tmp_all_fields3;
    set_items_ref_array(items3);
    if (join_tab)
    {
      JOIN_TAB *last_tab= join_tab + top_join_tab_count + aggr_tables - 1;

      last_tab->ref_array= &items3;
      last_tab->all_fields= &tmp_all_fields3;
      last_tab->fields= &tmp_fields_list3;
    }
    if (make_sum_func_list(*curr_all_fields, *curr_fields_list, true, true))
      DBUG_RETURN(true);
    if (prepare_sum_aggregators(sum_funcs,
                                !join_tab ||
                                !join_tab-> is_using_agg_loose_index_scan()))
      DBUG_RETURN(true);
    if (setup_sum_funcs(thd, sum_funcs) || thd->is_fatal_error)
      DBUG_RETURN(true);
  }
  if (group_list || order)
  {
    DBUG_PRINT("info",("Sorting for send_result_set_metadata"));
    THD_STAGE_INFO(thd, stage_sorting_result);

    if (tmp_having && !is_having_added_as_table_cond &&
        !group_list && !sort_and_group)
    {
      if (add_having_as_table_cond(curr_tab))
        DBUG_RETURN(true);
    }

    if (group)
      select_limit= HA_POS_ERROR;
    else if (!need_tmp)
    {


      for (uint i= const_tables + 1; i < top_join_tab_count; i++)
      {
        JOIN_TAB *const tab= join_tab + i;
        if (tab->select_cond ||
            (tab->keyuse && !tab->first_inner))
        {

          select_limit= HA_POS_ERROR;
          break;
        }
      }
    }


    DBUG_PRINT("info",("Sorting for order by/group by"));
    ORDER *order_arg= group_list ?  group_list : order;
    if (top_join_tab_count + aggr_tables > const_tables &&
        ordered_index_usage !=
        (group_list ? ordered_index_group_by : ordered_index_order_by) &&
        curr_tab->type != JT_CONST &&
        curr_tab->type != JT_EQ_REF)
    {

      JOIN_TAB *sort_tab= curr_tab;

      if (add_sorting_to_table(sort_tab, order_arg))
        DBUG_RETURN(true);


      sort_tab->filesort->limit=
        (has_group_by || (join_tab + table_count > curr_tab + 1)) ?
         select_limit : unit->select_limit_cnt;
    }
    if (!only_const_tables() &&
        !join_tab[const_tables].filesort &&
        !(select_options & SELECT_DESCRIBE))
    {


      skip_sort_order= true;
    }
  }


  curr_tab= join_tab + total_join_tab_cnt();
  if (select_lex->window_funcs.elements)
  {
    curr_tab->window_funcs_step= new Window_funcs_computation;
    if (curr_tab->window_funcs_step->setup(thd, &select_lex->window_funcs,
                                           curr_tab))
      DBUG_RETURN(true);

    status_var_increment(thd->status_var.feature_window_functions);
  }

  fields= curr_fields_list;

  set_items_ref_array(items0);
  if (join_tab)
    join_tab[exec_join_tab_cnt() + aggr_tables - 1].next_select=
      setup_end_select_func(this, NULL);
  group= has_group_by;

  DBUG_RETURN(false);
}
