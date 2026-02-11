evd_dbus_agent_search_conn_in_global_cache (const gchar *addr, gboolean reuse)
{
  if (conn_cache != NULL)
    return (ConnData *) g_hash_table_lookup (conn_cache, addr);
  else
    return NULL;
}
