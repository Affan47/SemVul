g_mime_message_set_reply_to (GMimeMessage *message, const char *reply_to)
{
	InternetAddressList *addrlist;
	char *encoded;

	g_return_if_fail (GMIME_IS_MESSAGE (message));
	g_return_if_fail (reply_to != NULL);

	g_free (message->reply_to);

	if ((addrlist = internet_address_list_parse_string (reply_to))) {
		message->reply_to = internet_address_list_to_string (addrlist, FALSE);
		encoded = internet_address_list_to_string (addrlist, TRUE);
		g_mime_header_list_set (GMIME_OBJECT (message)->headers, "Reply-To", encoded);
		g_object_unref (addrlist);
		g_free (encoded);
	} else {
		g_mime_header_list_set (GMIME_OBJECT (message)->headers, "Reply-To", "");
		message->reply_to = NULL;
	}

	if (message->mime_part)
		g_mime_header_list_set_stream (message->mime_part->headers, NULL);
}
