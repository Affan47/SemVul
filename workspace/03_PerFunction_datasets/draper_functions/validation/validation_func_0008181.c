parse_device (GKeyFile *kf, GHashTable **out_device_props, GError **error)
{
	char *tmp;
	gint i;

	*out_device_props = value_hash_create ();

	i = g_key_file_get_integer (kf, "device", "state", error);
	if (i == 0)
		return FALSE;
	value_hash_add_uint (*out_device_props, NMD_DEVICE_PROPS_STATE, (guint) i);

	i = g_key_file_get_integer (kf, "device", "type", error);
	if (i == 0)
		return FALSE;
	value_hash_add_uint (*out_device_props, NMD_DEVICE_PROPS_TYPE, (guint) i);

	tmp = g_key_file_get_string (kf, "device", "interface", error);
	if (tmp == NULL)
		return FALSE;
	value_hash_add_string (*out_device_props, NMD_DEVICE_PROPS_INTERFACE, tmp);
	g_free (tmp);

	tmp = g_key_file_get_string (kf, "device", "ip-interface", error);
	if (tmp == NULL)
		return FALSE;
	value_hash_add_string (*out_device_props, NMD_DEVICE_PROPS_IP_INTERFACE, tmp);
	g_free (tmp);

	tmp = g_key_file_get_string (kf, "device", "path", error);
	if (tmp == NULL)
		return FALSE;
	value_hash_add_object_path (*out_device_props, NMD_DEVICE_PROPS_PATH, tmp);
	g_free (tmp);

	return TRUE;
}
