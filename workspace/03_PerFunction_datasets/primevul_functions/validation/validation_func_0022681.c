JOIN::optimize_inner()
{
  DBUG_ENTER("JOIN::optimize_inner");
  subq_exit_fl= false;
  do_send_rows = (unit->select_limit_cnt) ? 1 : 0;

  DEBUG_SYNC(thd, "before_join_optimize");

  THD_STAGE_INFO(thd, stage_optimizing);

  set_allowed_join_cache_types();
  need_distinct= TRUE;


  fields= &select_lex->item_list;

  if (select_lex->first_cond_optimization)
  {


    if (select_lex->handle_derived(thd->lex, DT_MERGE))
      DBUG_RETURN(TRUE);
    table_count= select_lex->leaf_tables.elements;
  }

  if (select_lex->first_cond_optimization &&
      transform_in_predicates_into_in_subq(thd))
    DBUG_RETURN(1);


  select_lex->update_used_tables();


  if (select_lex->first_cond_optimization &&
      conds && conds->walk(&Item::exists2in_processor, 0, thd))
    DBUG_RETURN(1);


  if (transform_max_min_subquery())
    DBUG_RETURN(1);

  if (select_lex->first_cond_optimization)
  {

    if (convert_join_subqueries_to_semijoins(this))
      DBUG_RETURN(1);

    select_lex->update_used_tables();
  }

  eval_select_list_used_tables();

  table_count= select_lex->leaf_tables.elements;

  if (select_lex->options & OPTION_SCHEMA_TABLE &&
      optimize_schema_tables_memory_usage(select_lex->leaf_tables))
    DBUG_RETURN(1);

  if (setup_ftfuncs(select_lex))
    DBUG_RETURN(-1);

  row_limit= ((select_distinct || order || group_list) ? HA_POS_ERROR :
	      unit->select_limit_cnt);

  select_limit= unit->select_limit_cnt;
  if (having || (select_options & OPTION_FOUND_ROWS))
    select_limit= HA_POS_ERROR;
#ifdef HAVE_REF_TO_FIELDS

  if (having && !group_list && !sum_func_count)
  {
    if (!conds)
    {
      conds= having;
      having= 0;
    }
    else if ((conds=new (thd->mem_root) Item_cond_and(conds,having)))
    {


      conds->fix_fields(thd, &conds);
      conds->change_ref_to_fields(thd, tables_list);
      conds->top_level_item();
      having= 0;
    }
  }
#endif

  SELECT_LEX *sel= select_lex;
  if (sel->first_cond_optimization)
  {


    create_explain_query_if_not_exists(thd->lex, thd->mem_root);

    Query_arena *arena, backup;
    arena= thd->activate_stmt_arena_if_needed(&backup);

    sel->first_cond_optimization= 0;


    conds= simplify_joins(this, join_list, conds, TRUE, FALSE);
    if (thd->is_error() || select_lex->save_leaf_tables(thd))
    {
      if (arena)
        thd->restore_active_arena(arena, &backup);
      DBUG_RETURN(1);
    }
    build_bitmap_for_nested_joins(join_list, 0);

    sel->prep_where= conds ? conds->copy_andor_structure(thd) : 0;

    sel->where= conds;

    select_lex->update_used_tables();

    if (arena)
      thd->restore_active_arena(arena, &backup);
  }

  if (optimize_constant_subqueries())
    DBUG_RETURN(1);

  if (conds && conds->with_subquery())
    (void) conds->walk(&Item::cleanup_is_expensive_cache_processor,
                       0, (void *) 0);
  if (having && having->with_subquery())
    (void) having->walk(&Item::cleanup_is_expensive_cache_processor,
			0, (void *) 0);

  if (setup_jtbm_semi_joins(this, join_list, &conds))
    DBUG_RETURN(1);

  if (select_lex->cond_pushed_into_where)
  {
    conds= and_conds(thd, conds, select_lex->cond_pushed_into_where);
    if (conds && conds->fix_fields(thd, &conds))
      DBUG_RETURN(1);
  }
  if (select_lex->cond_pushed_into_having)
  {
    having= and_conds(thd, having, select_lex->cond_pushed_into_having);
    if (having)
    {
      select_lex->having_fix_field= 1;
      select_lex->having_fix_field_for_pushed_cond= 1;
      if (having->fix_fields(thd, &having))
        DBUG_RETURN(1);
      select_lex->having_fix_field= 0;
      select_lex->having_fix_field_for_pushed_cond= 0;
    }
  }

  bool ignore_on_expr= false;


  if (!thd->stmt_arena->is_conventional() && thd->mem_root != thd->stmt_arena->mem_root)
    for (TABLE_LIST *tbl= tables_list; tbl; tbl= tbl->next_local)
      if (tbl->table && tbl->on_expr && tbl->table->versioned())
      {
        ignore_on_expr= true;
        break;
      }
  conds= optimize_cond(this, conds, join_list, ignore_on_expr,
                       &cond_value, &cond_equal, OPT_LINK_EQUAL_FIELDS);

  if (thd->is_error())
  {
    error= 1;
    DBUG_PRINT("error",("Error from optimize_cond"));
    DBUG_RETURN(1);
  }

  if (optimizer_flag(thd, OPTIMIZER_SWITCH_COND_PUSHDOWN_FOR_DERIVED))
  {
    TABLE_LIST *tbl;
    List_iterator_fast<TABLE_LIST> li(select_lex->leaf_tables);
    while ((tbl= li++))
    {


      if (tbl->is_materialized_derived())
      {
        JOIN *join= tbl->get_unit()->first_select()->join;
        if (join &&
            join->optimization_state == JOIN::OPTIMIZATION_PHASE_1_DONE &&
            join->with_two_phase_optimization)
          continue;


        if (!tbl->is_inner_table_of_outer_join())
	{
          if (pushdown_cond_for_derived(thd, conds, tbl))
	    DBUG_RETURN(1);
        }
	if (mysql_handle_single_derived(thd->lex, tbl, DT_OPTIMIZE))
	  DBUG_RETURN(1);
      }
    }
  }
  else
  {

    if (select_lex->handle_derived(thd->lex, DT_OPTIMIZE))
      DBUG_RETURN(1);
  }

  {
    having= optimize_cond(this, having, join_list, TRUE,
                          &having_value, &having_equal);

    if (unlikely(thd->is_error()))
    {
      error= 1;
      DBUG_PRINT("error",("Error from optimize_cond"));
      DBUG_RETURN(1);
    }
    if (select_lex->where)
    {
      select_lex->cond_value= cond_value;
      if (sel->where != conds && cond_value == Item::COND_OK)
        thd->change_item_tree(&sel->where, conds);
    }
    if (select_lex->having)
    {
      select_lex->having_value= having_value;
      if (sel->having != having && having_value == Item::COND_OK)
        thd->change_item_tree(&sel->having, having);
    }
    if (cond_value == Item::COND_FALSE || having_value == Item::COND_FALSE ||
        (!unit->select_limit_cnt && !(select_options & OPTION_FOUND_ROWS)))
    {
      if (unit->select_limit_cnt)
      {
        DBUG_PRINT("info", (having_value == Item::COND_FALSE ?
                              "Impossible HAVING" : "Impossible WHERE"));
        zero_result_cause=  having_value == Item::COND_FALSE ?
                             "Impossible HAVING" : "Impossible WHERE";
      }
      else
      {
        DBUG_PRINT("info", ("Zero limit"));
        zero_result_cause= "Zero limit";
      }
      table_count= top_join_tab_count= 0;
      handle_implicit_grouping_with_window_funcs();
      error= 0;
      subq_exit_fl= true;
      goto setup_subq_exit;
    }
  }

#ifdef WITH_PARTITION_STORAGE_ENGINE
  {
    TABLE_LIST *tbl;
    List_iterator_fast<TABLE_LIST> li(select_lex->leaf_tables);
    while ((tbl= li++))
    {
      Item **prune_cond= get_sargable_cond(this, tbl->table);
      tbl->table->all_partitions_pruned_away=
        prune_partitions(thd, tbl->table, *prune_cond);
    }
  }
#endif


  if (tables_list && implicit_grouping)
  {
    int res;


    if ((res=opt_sum_query(thd, select_lex->leaf_tables, all_fields, conds)))
    {
      DBUG_ASSERT(res >= 0);
      if (res == HA_ERR_KEY_NOT_FOUND)
      {
        DBUG_PRINT("info",("No matching min/max row"));
	zero_result_cause= "No matching min/max row";
        table_count= top_join_tab_count= 0;
	error=0;
        subq_exit_fl= true;
        handle_implicit_grouping_with_window_funcs();
        goto setup_subq_exit;
      }
      if (res > 1)
      {
        error= res;
        DBUG_PRINT("error",("Error from opt_sum_query"));
        DBUG_RETURN(1);
      }

      DBUG_PRINT("info",("Select tables optimized away"));
      if (!select_lex->have_window_funcs())
        zero_result_cause= "Select tables optimized away";
      tables_list= 0;
      select_lex->min_max_opt_list.empty();
      const_tables= top_join_tab_count= table_count;
      handle_implicit_grouping_with_window_funcs();


      if (conds && !(thd->lex->describe & DESCRIBE_EXTENDED))
      {
        COND *table_independent_conds=
          make_cond_for_table(thd, conds, PSEUDO_TABLE_BITS, 0, -1,
                              FALSE, FALSE);
        DBUG_EXECUTE("where",
                     print_where(table_independent_conds,
                                 "where after opt_sum_query()",
                                 QT_ORDINARY););
        conds= table_independent_conds;
      }
    }
  }
  if (!tables_list)
  {
    DBUG_PRINT("info",("No tables"));
    error= 0;
    subq_exit_fl= true;
    goto setup_subq_exit;
  }
  error= -1;

  MEM_UNDEFINED(&sort_by_table, sizeof(sort_by_table));


  if (group_list && table_count == 1)
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
      group_optimized_away= 1;
      select_distinct=0;
    }
  }


  THD_STAGE_INFO(thd, stage_statistics);
  result->prepare_to_read_rows();
  if (unlikely(make_join_statistics(this, select_lex->leaf_tables,
                                    &keyuse)) ||
      unlikely(thd->is_fatal_error))
  {
    DBUG_PRINT("error",("Error: make_join_statistics() failed"));
    DBUG_RETURN(1);
  }


  if (fix_all_splittings_in_plan())
    DBUG_RETURN(1);

setup_subq_exit:
  with_two_phase_optimization= check_two_phase_optimization(thd);
  if (with_two_phase_optimization)
    optimization_state= JOIN::OPTIMIZATION_PHASE_1_DONE;
  else
  {
    if (optimize_stage2())
      DBUG_RETURN(1);
  }
  DBUG_RETURN(0);
}
