updated_properties (GObject *object, GAsyncResult *result, gpointer user_data)
{
	NMClient *client = NM_CLIENT (user_data);
	GError *error = NULL;

	if (!_nm_object_reload_properties_finish (NM_OBJECT (object), result, &error)) {
		g_warning ("%s: error reading NMClient properties: %s", __func__, error->message);
		g_error_free (error);
	}

	_nm_object_queue_notify (NM_OBJECT (client), NM_CLIENT_MANAGER_RUNNING);
}
