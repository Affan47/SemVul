Next_select_func setup_end_select_func(JOIN *join, JOIN_TAB *tab)
{
  TMP_TABLE_PARAM *tmp_tbl= tab ? tab->tmp_table_param : &join->tmp_table_param;


  if (join->sort_and_group && !tmp_tbl->precomputed_group_by)
  {
    DBUG_PRINT("info",("Using end_send_group"));
    return end_send_group;
  }
  DBUG_PRINT("info",("Using end_send"));
  return end_send;
}
