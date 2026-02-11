do_create (EBookBackendFile *bf,
           const gchar * const *vcards,
           GQueue *out_contacts,
           GError **error)
{
	PhotoModifiedStatus status = STATUS_NORMAL;
	GQueue queue = G_QUEUE_INIT;
	guint ii, length;
	GError *local_error = NULL;

	length = g_strv_length ((gchar **) vcards);

	for (ii = 0; ii < length; ii++) {
		gchar           *id;
		const gchar     *rev;
		EContact        *contact;

		contact = e_contact_new_from_vcard (vcards[ii]);


		if (e_contact_get_const (contact, E_CONTACT_UID) == NULL) {
			id = e_book_backend_file_create_unique_id ();
			e_contact_set (contact, E_CONTACT_UID, id);
			g_free (id);
		}

		rev = e_contact_get_const (contact, E_CONTACT_REV);
		if (!(rev && *rev))
			set_revision (bf, contact);

		status = maybe_transform_vcard_for_photo (bf, NULL, contact, error);

		if (status != STATUS_ERROR) {


			g_queue_push_tail (&queue, contact);
		} else {

			g_warning (
				G_STRLOC ": Error transforming vcard with image data %s",
				(error && *error) ? (*error)->message :
				"Unknown error transforming vcard");
			g_object_unref (contact);


			break;
		}
	}

	if (status != STATUS_ERROR) {
		GList *tail, *link;
		GSList *slist = NULL;


		tail = g_queue_peek_tail_link (&queue);
		for (link = tail; link != NULL; link = g_list_previous (link))
			slist = g_slist_prepend (slist, link->data);

		if (!e_book_backend_sqlitedb_new_contacts (bf->priv->sqlitedb,
							   SQLITEDB_FOLDER_ID,
							   slist, FALSE,
							   &local_error)) {

			g_warning ("Failed to add contacts: %s", local_error->message);

			if (g_error_matches (local_error,
					     E_BOOK_SDB_ERROR,
					     E_BOOK_SDB_ERROR_CONSTRAINT)) {
				g_set_error (
					error, E_BOOK_CLIENT_ERROR,
					E_BOOK_CLIENT_ERROR_CONTACT_ID_ALREADY_EXISTS,
					_("Conflicting UIDs found in added contacts"));
				g_clear_error (&local_error);
			} else
				g_propagate_error (error, local_error);

			status = STATUS_ERROR;
		}

		g_slist_free (slist);
	}

	if (status != STATUS_ERROR && out_contacts != NULL)
		e_queue_transfer (&queue, out_contacts);

	while (!g_queue_is_empty (&queue))
		g_object_unref (g_queue_pop_head (&queue));

	return (status != STATUS_ERROR);
}
