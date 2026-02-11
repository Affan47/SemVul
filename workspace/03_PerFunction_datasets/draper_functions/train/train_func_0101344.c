gc_db_get_conf(GcomprisProfile *profile, GcomprisBoard  *board )
{
  GHashTable *hash_result = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);

  SUPPORT_OR_RETURN(hash_result);

#ifdef USE_SQLITE
  return gc_db_conf_with_table_get( profile->profile_id, board->board_id, hash_result) ;
#endif
}
