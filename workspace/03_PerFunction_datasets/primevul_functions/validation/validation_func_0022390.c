greedy_search(JOIN      *join,
              table_map remaining_tables,
              uint      search_depth,
              uint      prune_level,
              uint      use_cond_selectivity)
{
  double    record_count= 1.0;
  double    read_time=    0.0;
  uint      idx= join->const_tables;
  uint      best_idx;
  uint      size_remain;
  POSITION  best_pos;
  JOIN_TAB  *best_table;

  uint      n_tables __attribute__((unused));
  DBUG_ENTER("greedy_search");


  n_tables= size_remain= my_count_bits(remaining_tables &
                                       (join->emb_sjm_nest?
                                         (join->emb_sjm_nest->sj_inner_tables &
                                          ~join->const_table_map)
                                         :
                                         ~(table_map)0));

  do {

    join->best_read= DBL_MAX;
    if (best_extension_by_limited_search(join, remaining_tables, idx, record_count,
                                         read_time, search_depth, prune_level,
                                         use_cond_selectivity))
      DBUG_RETURN(TRUE);


    DBUG_ASSERT(join->best_read < DBL_MAX);

    if (size_remain <= search_depth)
    {


      DBUG_EXECUTE("opt", print_plan(join, n_tables,
                                     record_count, read_time, read_time,
                                     "optimal"););
      DBUG_RETURN(FALSE);
    }


    best_pos= join->best_positions[idx];
    best_table= best_pos.table;


    join->positions[idx]= best_pos;


    bool is_interleave_error __attribute__((unused))=
      check_interleaving_with_nj (best_table);

    DBUG_ASSERT(!is_interleave_error);


    best_idx= idx;
    JOIN_TAB *pos= join->best_ref[best_idx];
    while (pos && best_table != pos)
      pos= join->best_ref[++best_idx];
    DBUG_ASSERT((pos != NULL));

    swap_variables(JOIN_TAB*, join->best_ref[idx], join->best_ref[best_idx]);


    record_count= COST_MULT(record_count, join->positions[idx].records_read);
    read_time= COST_ADD(read_time,
                         COST_ADD(join->positions[idx].read_time,
                                  record_count / (double) TIME_FOR_COMPARE));

    remaining_tables&= ~(best_table->table->map);
    --size_remain;
    ++idx;

    DBUG_EXECUTE("opt", print_plan(join, idx,
                                   record_count, read_time, read_time,
                                   "extended"););
  } while (TRUE);
}
