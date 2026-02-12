sub_select_cache(JOIN *join, JOIN_TAB *join_tab, bool end_of_records)
{
  enum_nested_loop_state rc;
  JOIN_CACHE *cache= join_tab->cache;
  DBUG_ENTER("sub_select_cache");


  DBUG_ASSERT(cache != NULL);

  join_tab->cache->reset_join(join);

  if (end_of_records)
  {
    rc= cache->join_records(FALSE);
    if (rc == NESTED_LOOP_OK || rc == NESTED_LOOP_NO_MORE_ROWS ||
        rc == NESTED_LOOP_QUERY_LIMIT)
      rc= sub_select(join, join_tab, end_of_records);
    DBUG_RETURN(rc);
  }
  if (unlikely(join->thd->check_killed()))
  {

    DBUG_RETURN(NESTED_LOOP_KILLED);
  }
  if (!test_if_use_dynamic_range_scan(join_tab))
  {
    if (!cache->put_record())
      DBUG_RETURN(NESTED_LOOP_OK);


    rc= cache->join_records(FALSE);
    DBUG_RETURN(rc);
  }


  rc= cache->join_records(TRUE);
  if (rc == NESTED_LOOP_OK || rc == NESTED_LOOP_NO_MORE_ROWS ||
      rc == NESTED_LOOP_QUERY_LIMIT)
    rc= sub_select(join, join_tab, end_of_records);
  DBUG_RETURN(rc);
}
