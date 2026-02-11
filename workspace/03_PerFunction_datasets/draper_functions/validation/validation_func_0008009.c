qof_string_cache_insert(gconstpointer key)
{
    if (key)
    {
        GHashTable* cache = qof_get_string_cache();
        gpointer value;
        gpointer cache_key;
        if (g_hash_table_lookup_extended(cache, key, &cache_key, &value))
        {
            guint* refcount = (guint*)value;
            ++(*refcount);
            return cache_key;
        }
        else
        {
            gpointer new_key = g_strdup(key);
            guint* refcount = g_malloc(sizeof(guint));
            *refcount = 1;
            g_hash_table_insert(cache, new_key, refcount);
            return new_key;
        }
    }
    return NULL;
}
