check_remove_uri_for_field (EContact *old_contact,
                            EContact *new_contact,
                            EContactField field)
{
	EContactPhoto *old_photo = NULL, *new_photo = NULL;
	gchar         *uri = NULL;

	old_photo = e_contact_get (old_contact, field);
	if (!old_photo)
		return NULL;

	if (new_contact) {

		new_photo = e_contact_get (new_contact, field);

		if (new_photo == NULL ||
		    g_ascii_strcasecmp (old_photo->data.uri, new_photo->data.uri))
			uri = g_strdup (old_photo->data.uri);
	} else {
		uri = g_strdup (old_photo->data.uri);
	}

	e_contact_photo_free (old_photo);
	e_contact_photo_free (new_photo);

	return uri;
}
