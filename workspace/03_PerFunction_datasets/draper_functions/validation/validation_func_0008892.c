soup_multipart_append_form_file (SoupMultipart *multipart,
				 const char *control_name, const char *filename,
				 const char *content_type, SoupBuffer *body)
{
	SoupMessageHeaders *headers;
	GString *disposition;

	headers = soup_message_headers_new (SOUP_MESSAGE_HEADERS_MULTIPART);
	disposition = g_string_new ("form-data; ");
	soup_header_g_string_append_param_quoted (disposition, "name", control_name);
	if (filename) {
		g_string_append (disposition, "; ");
		soup_header_g_string_append_param_quoted (disposition, "filename", filename);
	}
	soup_message_headers_append (headers, "Content-Disposition",
				     disposition->str);
	g_string_free (disposition, TRUE);

	if (content_type) {
		soup_message_headers_append (headers, "Content-Type",
					     content_type);
	}

	g_ptr_array_add (multipart->headers, headers);
	g_ptr_array_add (multipart->bodies, soup_buffer_copy (body));
}
