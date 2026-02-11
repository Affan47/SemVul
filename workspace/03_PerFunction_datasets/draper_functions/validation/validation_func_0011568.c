invalidate_table(THD *thd, uchar * key, uint32  key_length)
{
  DEBUG_SYNC(thd, "wait_in_query_cache_invalidate1");


  lock();

  DEBUG_SYNC(thd, "wait_in_query_cache_invalidate2");

  if (query_cache_size > 0)
    invalidate_table_internal(thd, key, key_length);

  unlock();
}
