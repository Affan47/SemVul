write_nm_created_bridges (NMManager *self)
{
	NMManagerPrivate *priv = NM_MANAGER_GET_PRIVATE (self);
	GString *br_list;
	GSList *iter;
	GError *error = NULL;
	GTimeVal tv;
	gboolean found = FALSE;


	br_list = g_string_sized_new (50);


	g_get_current_time (&tv);
	g_string_append_printf (br_list, "ts=%ld\n", tv.tv_sec);

	for (iter = priv->devices; iter; iter = g_slist_next (iter)) {
		NMDevice *device = iter->data;

		if (nm_device_get_device_type (device) == NM_DEVICE_TYPE_BRIDGE) {
			g_string_append_printf (br_list, "iface=%s\n", nm_device_get_iface (device));
			found = TRUE;
		}
	}

	if (found) {
		if (!g_file_set_contents (NM_BRIDGE_FILE, br_list->str, -1, &error)) {
			nm_log_warn (LOGD_BRIDGE, "Failed to write NetworkManager-created bridge list; "
			             "on restart bridges may not be recognized. (%s)",
			             error ? error->message : "unknown");
			g_clear_error (&error);
		}
	}
	g_string_free (br_list, TRUE);
}
