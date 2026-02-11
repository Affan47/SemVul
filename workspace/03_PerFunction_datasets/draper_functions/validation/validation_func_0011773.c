print_mime_struct (GMimeStream *stream, GMimeObject *part, int depth)
{
	const GMimeContentType *type;
	GMimeMultipart *multipart;
	GMimeMessagePart *mpart;
	GMimeObject *subpart;
	int i, n;

	print_depth (stream, depth);

	type = g_mime_object_get_content_type (part);

	g_mime_stream_printf (stream, "Content-Type: %s/%s\n", type->type, type->subtype);

	if (GMIME_IS_MULTIPART (part)) {
		multipart = (GMimeMultipart *) part;

		n = g_mime_multipart_get_count (multipart);
		for (i = 0; i < n; i++) {
			subpart = g_mime_multipart_get_part (multipart, i);
			print_mime_struct (stream, subpart, depth + 1);
		}
	} else if (GMIME_IS_MESSAGE_PART (part)) {
		mpart = (GMimeMessagePart *) part;

		if (mpart->message)
			print_mime_struct (stream, mpart->message->mime_part, depth + 1);
	}
}
