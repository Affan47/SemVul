subselect_hash_sj_engine::choose_partial_match_strategy(
  bool has_non_null_key, bool has_covering_null_row,
  MY_BITMAP *partial_match_key_parts_arg)
{
  ulonglong pm_buff_size;

  DBUG_ASSERT(strategy == PARTIAL_MATCH);


  if (!optimizer_flag(thd, OPTIMIZER_SWITCH_PARTIAL_MATCH_ROWID_MERGE) &&
       optimizer_flag(thd, OPTIMIZER_SWITCH_PARTIAL_MATCH_TABLE_SCAN))
    strategy= PARTIAL_MATCH_SCAN;
  else if
     ( optimizer_flag(thd, OPTIMIZER_SWITCH_PARTIAL_MATCH_ROWID_MERGE) &&
      !optimizer_flag(thd, OPTIMIZER_SWITCH_PARTIAL_MATCH_TABLE_SCAN))
    strategy= PARTIAL_MATCH_MERGE;


  if (strategy == PARTIAL_MATCH)
  {


    if (tmp_table->file->stats.records < 100)
      strategy= PARTIAL_MATCH_SCAN;
    else
      strategy= PARTIAL_MATCH_MERGE;
  }


  if (strategy == PARTIAL_MATCH_MERGE)
  {
    pm_buff_size= rowid_merge_buff_size(has_non_null_key,
                                        has_covering_null_row,
                                        partial_match_key_parts_arg);
    if (pm_buff_size > thd->variables.rowid_merge_buff_size)
      strategy= PARTIAL_MATCH_SCAN;
  }
}
