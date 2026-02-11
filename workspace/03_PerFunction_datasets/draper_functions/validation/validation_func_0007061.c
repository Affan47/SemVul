_nm_object_cache_get (const char *path)
{
	NMObject *object;

	_init_cache ();
	object = g_hash_table_lookup (cache, path);
	return object ? g_object_ref (object) : NULL;
}
