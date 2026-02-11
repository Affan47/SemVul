type_bucket_foreach (gpointer key, gpointer value, gpointer user_data)
{
	struct _type_bucket *bucket = value;

	g_free (bucket->type);

	if (bucket->subtype_hash) {
		g_hash_table_foreach (bucket->subtype_hash, subtype_bucket_foreach, NULL);
		g_hash_table_destroy (bucket->subtype_hash);
	}

	g_free (bucket);
}
