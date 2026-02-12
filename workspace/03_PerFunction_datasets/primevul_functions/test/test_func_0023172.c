void Item_func_nullif::update_used_tables()
{
  if (m_cache)
  {
    used_tables_and_const_cache_init();
    used_tables_and_const_cache_update_and_join(m_cache->get_example());
    used_tables_and_const_cache_update_and_join(arg_count, args);
  }
  else
  {


    DBUG_ASSERT(arg_count == 3);
    used_tables_and_const_cache_init();
    used_tables_and_const_cache_update_and_join(args[0] == args[2] ? 2 : 3,
                                                args);
  }
}
