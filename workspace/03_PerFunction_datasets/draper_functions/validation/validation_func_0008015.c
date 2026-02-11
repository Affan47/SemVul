g_mime_header_list_to_string (const GMimeHeaderList *headers)
{
	GMimeStream *stream;
	GByteArray *array;
	char *str;

	g_return_val_if_fail (headers != NULL, NULL);

	array = g_byte_array_new ();
	stream = g_mime_stream_mem_new ();
	g_mime_stream_mem_set_byte_array (GMIME_STREAM_MEM (stream), array);

	if (headers->stream) {
		g_mime_stream_reset (headers->stream);
		g_mime_stream_write_to_stream (headers->stream, stream);
	} else {
		g_mime_header_list_write_to_stream (headers, stream);
	}

	g_object_unref (stream);

	g_byte_array_append (array, (unsigned char *) "", 1);
	str = (char *) array->data;
	g_byte_array_free (array, FALSE);

	return str;
}
