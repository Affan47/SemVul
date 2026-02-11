check_header_in_message_info (CamelMessageInfo *info,
                              gint argc,
                              struct _CamelSExpResult **argv,
                              camel_search_match_t how,
                              gboolean *matched)
{
	struct _KnownHeaders {
		const gchar *header_name;
		guint info_key;
	} known_headers[] = {
		{ "Subject", CAMEL_MESSAGE_INFO_SUBJECT },
		{ "From", CAMEL_MESSAGE_INFO_FROM },
		{ "To", CAMEL_MESSAGE_INFO_TO },
		{ "Cc", CAMEL_MESSAGE_INFO_CC }
	};
	camel_search_t type = CAMEL_SEARCH_TYPE_ENCODED;
	const gchar *name, *value;
	gboolean found = FALSE;
	gint ii;

	g_return_val_if_fail (argc > 1, FALSE);
	g_return_val_if_fail (argv != NULL, FALSE);
	g_return_val_if_fail (matched != NULL, FALSE);

	if (!info)
		return FALSE;

	name = argv[0]->value.string;
	g_return_val_if_fail (name != NULL, FALSE);


	if (!*name) {
		gint jj;

		for (jj = 0; jj < G_N_ELEMENTS (known_headers); jj++) {
			value = camel_message_info_ptr (info, known_headers[jj].info_key);
			if (!value)
				continue;

			if (known_headers[jj].info_key == CAMEL_MESSAGE_INFO_SUBJECT)
				type = CAMEL_SEARCH_TYPE_ENCODED;
			else
				type = CAMEL_SEARCH_TYPE_ADDRESS_ENCODED;

			for (ii = 1; ii < argc && !*matched; ii++) {
				if (argv[ii]->type == CAMEL_SEXP_RES_STRING)
					*matched = camel_search_header_match (value, argv[ii]->value.string, how, type, NULL);
			}

			if (*matched)
				return TRUE;
		}

		return FALSE;
	}

	value = NULL;

	for (ii = 0; ii < G_N_ELEMENTS (known_headers); ii++) {
		found = g_ascii_strcasecmp (name, known_headers[ii].header_name) == 0;
		if (found) {
			value = camel_message_info_ptr (info, known_headers[ii].info_key);
			if (known_headers[ii].info_key != CAMEL_MESSAGE_INFO_SUBJECT)
				type = CAMEL_SEARCH_TYPE_ADDRESS_ENCODED;
			break;
		}
	}

	if (!found || !value)
		return FALSE;

	for (ii = 1; ii < argc && !*matched; ii++) {
		if (argv[ii]->type == CAMEL_SEXP_RES_STRING)
			*matched = camel_search_header_match (value, argv[ii]->value.string, how, type, NULL);
	}

	return TRUE;
}
