cache_node_insert (Cache *cache, const char *key)
{
	CacheNode *node;

	cache->size++;

	if (cache->size > cache->max_size)
		cache_expire_unused (cache);

	node = g_slice_alloc (cache->node_size);
	node->key = g_strdup (key);
	node->cache = cache;

	g_hash_table_insert (cache->node_hash, node->key, node);
	list_prepend (&cache->list, (ListNode *) node);

	return node;
}
