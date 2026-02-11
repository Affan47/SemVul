find_client_by_contact (GSList *clients,
                        const gchar *contact_uid,
                        const gchar *source_uid)
{
	GSList *l;

	if (source_uid && *source_uid) {

		for (l = clients; l; l = g_slist_next (l)) {
			EBookClient *client = l->data;
			ESource *source = e_client_get_source (E_CLIENT (client));

			if (!source)
				continue;

			if (g_strcmp0 (source_uid, e_source_get_uid (source)) == 0)
				return client;
		}
	}

	for (l = clients; l; l = g_slist_next (l)) {
		EBookClient *client = l->data;
		EContact *contact = NULL;
		gboolean  result;

		result = e_book_client_get_contact_sync (client, contact_uid, &contact, NULL, NULL);
		if (contact)
			g_object_unref (contact);

		if (result)
			return client;
	}

	return NULL;
}
