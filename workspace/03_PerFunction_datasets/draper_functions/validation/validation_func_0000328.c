g_mime_header_list_prepend (GMimeHeaderList *headers, const char *name, const char *value)
{
	GMimeHeader *header;

	g_return_if_fail (headers != NULL);
	g_return_if_fail (name != NULL);

	header = g_mime_header_new (name, value, -1);
	list_prepend (&headers->list, (ListNode *) header);
	g_hash_table_replace (headers->hash, header->name, header);

	g_mime_header_list_set_stream (headers, NULL);
}
