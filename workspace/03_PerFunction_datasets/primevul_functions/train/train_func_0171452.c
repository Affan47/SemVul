int del_global_index_stats_for_table(THD *thd, uchar* cache_key, size_t cache_key_length)
{
  int res = 0;
  DBUG_ENTER("del_global_index_stats_for_table");

  mysql_mutex_lock(&LOCK_global_index_stats);

  for (uint i= 0; i < global_index_stats.records;)
  {
    INDEX_STATS *index_stats =
      (INDEX_STATS*) my_hash_element(&global_index_stats, i);


    if (index_stats &&
	index_stats->index_name_length >= cache_key_length &&
	!memcmp(index_stats->index, cache_key, cache_key_length))
    {
      res= my_hash_delete(&global_index_stats, (uchar*)index_stats);


    }
    else
      i++;
  }

  mysql_mutex_unlock(&LOCK_global_index_stats);
  DBUG_RETURN(res);
}
