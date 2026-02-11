process_header (GMimeObject *object, int action, const char *header, const char *value)
{
	GMimeMessage *message = (GMimeMessage *) object;
	InternetAddressList *addrlist;
	time_t date;
	int offset;
	guint i;

	for (i = 0; i < G_N_ELEMENTS (message_headers); i++) {
		if (!g_ascii_strcasecmp (message_headers[i], header))
			break;
	}

	switch (i) {
	case HEADER_FROM:
		g_free (message->from);
		if ((addrlist = internet_address_list_parse_string (value))) {
			message->from = internet_address_list_to_string (addrlist, FALSE);
			g_object_unref (addrlist);
		} else {
			message->from = NULL;
		}
		break;
	case HEADER_REPLY_TO:
		g_free (message->reply_to);
		if ((addrlist = internet_address_list_parse_string (value))) {
			message->reply_to = internet_address_list_to_string (addrlist, FALSE);
			g_object_unref (addrlist);
		} else {
			message->reply_to = NULL;
		}
		break;
	case HEADER_TO:
		block_changed_event (message, GMIME_RECIPIENT_TYPE_TO);
		message_add_recipients_from_string (message, action, GMIME_RECIPIENT_TYPE_TO, value);
		unblock_changed_event (message, GMIME_RECIPIENT_TYPE_TO);
		break;
	case HEADER_CC:
		block_changed_event (message, GMIME_RECIPIENT_TYPE_CC);
		message_add_recipients_from_string (message, action, GMIME_RECIPIENT_TYPE_CC, value);
		unblock_changed_event (message, GMIME_RECIPIENT_TYPE_CC);
		break;
	case HEADER_BCC:
		block_changed_event (message, GMIME_RECIPIENT_TYPE_BCC);
		message_add_recipients_from_string (message, action, GMIME_RECIPIENT_TYPE_BCC, value);
		unblock_changed_event (message, GMIME_RECIPIENT_TYPE_BCC);
		break;
	case HEADER_SUBJECT:
		g_free (message->subject);
		message->subject = g_mime_utils_header_decode_text (value);
		break;
	case HEADER_DATE:
		if (value) {
			date = g_mime_utils_header_decode_date (value, &offset);
			message->date = date;
			message->tz_offset = offset;
		}
		break;
	case HEADER_MESSAGE_ID:
		g_free (message->message_id);
		message->message_id = g_mime_utils_decode_message_id (value);
		break;
	case HEADER_MIME_VERSION:
		break;
	default:
		return FALSE;
	}

	return TRUE;
}
