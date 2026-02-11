search_gui_file_hash(gconstpointer key)
{
	const struct result_data *rd = key;
	const record_t *rc = rd->record;
	guint hash;

	hash = rc->size;
	hash ^= rc->size >> 31;
	hash ^= rc->sha1 ? sha1_hash(rc->sha1) : 0;
	return hash;
}
