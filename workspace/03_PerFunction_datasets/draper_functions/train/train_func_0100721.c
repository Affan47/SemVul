get_book_at_row (EContactStore *contact_store,
                 gint row)
{
	GArray *array;
	ContactSource *source;
	gint source_index;

	source_index = find_contact_source_by_offset (contact_store, row);
	if (source_index < 0)
		return NULL;

	array = contact_store->priv->contact_sources;
	source = &g_array_index (array, ContactSource, source_index);

	return source->book_client;
}
