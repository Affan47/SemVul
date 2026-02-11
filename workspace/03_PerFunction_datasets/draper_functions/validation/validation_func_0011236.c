data_file_entry_added (GkmGnome2File *store, const gchar *identifier, GkmGnome2Storage *self)
{
	GError *error = NULL;
	GkmObject *object;
	GBytes *bytes;
	gboolean ret;
	guchar *data;
	gsize n_data;
	GType type;
	gchar *path;

	g_return_if_fail (GKM_IS_GNOME2_STORAGE (self));
	g_return_if_fail (identifier);


	object = g_hash_table_lookup (self->identifier_to_object, identifier);
	if (object != NULL)
		return;


	type = type_from_identifier (identifier);
	if (type == 0) {
		g_warning ("don't know how to load file in user store: %s", identifier);
		return;
	}


	path = g_build_filename (self->directory, identifier, NULL);
	ret = g_file_get_contents (path, (gchar**)&data, &n_data, &error);
	g_free (path);

	if (ret == FALSE) {
		g_warning ("couldn't read file in user store: %s: %s", identifier,
		           egg_error_message (error));
		g_clear_error (&error);
		return;
	}


	if (!check_object_hash (self, identifier, data, n_data)) {
		g_message ("file in user store doesn't match hash: %s", identifier);
		g_free (data);
		return;
	}


	object = g_object_new (type, "unique", identifier, "module", self->module,
	                       "manager", gkm_module_get_manager (self->module), NULL);
	g_return_if_fail (GKM_IS_SERIALIZABLE (object));
	g_return_if_fail (GKM_SERIALIZABLE_GET_INTERFACE (object)->extension);

	bytes = g_bytes_new_take (data, n_data);


	if (gkm_serializable_load (GKM_SERIALIZABLE (object), self->login, bytes))
		take_object_ownership (self, identifier, object);
	else
		g_message ("failed to load file in user store: %s", identifier);

	g_bytes_unref (bytes);
	g_object_unref (object);
}
