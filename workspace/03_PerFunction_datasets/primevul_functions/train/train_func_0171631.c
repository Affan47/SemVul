void optimize_wo_join_buffering(JOIN *join, uint first_tab, uint last_tab,
                                table_map last_remaining_tables,
                                bool first_alt, uint no_jbuf_before,
                                double *outer_rec_count, double *reopt_cost)
{
  double cost, rec_count;
  table_map reopt_remaining_tables= last_remaining_tables;
  uint i;
  THD *thd= join->thd;
  Json_writer_temp_disable trace_wo_join_buffering(thd);

  if (first_tab > join->const_tables)
  {
    cost=      join->positions[first_tab - 1].prefix_cost.total_cost();
    rec_count= join->positions[first_tab - 1].prefix_record_count;
  }
  else
  {
    cost= 0.0;
    rec_count= 1;
  }

  *outer_rec_count= rec_count;
  for (i= first_tab; i <= last_tab; i++)
    reopt_remaining_tables |= join->positions[i].table->table->map;


  table_map save_cur_sj_inner_tables= join->cur_sj_inner_tables;
  join->cur_sj_inner_tables= 0;

  for (i= first_tab; i <= last_tab; i++)
  {
    JOIN_TAB *rs= join->positions[i].table;
    POSITION pos, loose_scan_pos;

    if ((i == first_tab && first_alt) || join->positions[i].use_join_buffer)
    {

      best_access_path(join, rs, reopt_remaining_tables,
                       join->positions, i,
                       TRUE, rec_count,
                       &pos, &loose_scan_pos);
    }
    else
      pos= join->positions[i];

    if ((i == first_tab && first_alt))
      pos= loose_scan_pos;

    reopt_remaining_tables &= ~rs->table->map;
    rec_count= COST_MULT(rec_count, pos.records_read);
    cost= COST_ADD(cost, pos.read_time);
    cost= COST_ADD(cost, rec_count / (double) TIME_FOR_COMPARE);

    double pushdown_cond_selectivity= 1.0;
    table_map real_table_bit= rs->table->map;
    if (join->thd->variables.optimizer_use_condition_selectivity > 1)
    {
      pushdown_cond_selectivity= table_cond_selectivity(join, i, rs,
                                                        reopt_remaining_tables &
                                                        ~real_table_bit);
    }
    (*outer_rec_count) *= pushdown_cond_selectivity;
    if (!rs->emb_sj_nest)
      *outer_rec_count= COST_MULT(*outer_rec_count, pos.records_read);

  }
  join->cur_sj_inner_tables= save_cur_sj_inner_tables;

  *reopt_cost= cost;
}
