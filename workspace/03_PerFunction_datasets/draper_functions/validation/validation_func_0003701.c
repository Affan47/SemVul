gcr_pkcs11_get_trust_lookup_slots (void)
{
	GList *results = NULL;
	GError *error = NULL;
	gchar **uri;

	if (!initialized_modules)
		return NULL;

	initialize_uris ();

	for (uri = trust_lookup_uris; uri && *uri; ++uri) {
		results = g_list_concat (results, gck_modules_tokens_for_uri (all_modules, *uri, &error));
		if (error != NULL) {
			g_warning ("error finding slot for trust assertions: %s: %s",
			           *uri, egg_error_message (error));
			g_clear_error (&error);
		}
	}

	if (results == NULL)
		_gcr_debug ("no trust lookup slots found");

	return results;
}
