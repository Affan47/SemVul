g_tls_backend_gnutls_remove_session (unsigned int             type,
				     GBytes                  *session_id)
{
  GHashTable *cache;

  G_LOCK (session_cache_lock);

  cache = get_session_cache (type, FALSE);
  if (cache)
    g_hash_table_remove (cache, session_id);

  G_UNLOCK (session_cache_lock);
}
