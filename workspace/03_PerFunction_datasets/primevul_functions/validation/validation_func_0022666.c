choose_plan(JOIN *join, table_map join_tables)
{
  uint search_depth= join->thd->variables.optimizer_search_depth;
  uint prune_level=  join->thd->variables.optimizer_prune_level;
  uint use_cond_selectivity=
         join->thd->variables.optimizer_use_condition_selectivity;
  bool straight_join= MY_TEST(join->select_options & SELECT_STRAIGHT_JOIN);
  DBUG_ENTER("choose_plan");

  join->cur_embedding_map= 0;
  reset_nj_counters(join, join->join_list);
  qsort2_cmp jtab_sort_func;

  if (join->emb_sjm_nest)
  {


    jtab_sort_func= join_tab_cmp_embedded_first;
  }
  else
  {


    jtab_sort_func= straight_join ? join_tab_cmp_straight : join_tab_cmp;
  }


  my_qsort2(join->best_ref + join->const_tables,
            join->table_count - join->const_tables, sizeof(JOIN_TAB*),
            jtab_sort_func, (void*)join->emb_sjm_nest);

  if (!join->emb_sjm_nest)
  {
    choose_initial_table_order(join);
  }
  join->cur_sj_inner_tables= 0;

  if (straight_join)
  {
    optimize_straight_join(join, join_tables);
  }
  else
  {
    DBUG_ASSERT(search_depth <= MAX_TABLES + 1);
    if (search_depth == 0)

      search_depth= determine_search_depth(join);
    if (greedy_search(join, join_tables, search_depth, prune_level,
                      use_cond_selectivity))
      DBUG_RETURN(TRUE);
  }


  if (join->thd->lex->is_single_level_stmt())
    join->thd->status_var.last_query_cost= join->best_read;
  DBUG_RETURN(FALSE);
}
