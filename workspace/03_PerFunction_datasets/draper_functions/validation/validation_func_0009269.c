write_one_secret_to_keyring (NMSetting *setting,
                             const char *key,
                             const GValue *value,
                             GParamFlags flags,
                             gpointer user_data)
{
	CopyOneSettingValueInfo *info = (CopyOneSettingValueInfo *) user_data;
	GType type = G_VALUE_TYPE (value);
	const char *secret;
	const char *setting_name;


	if (   !(flags & NM_SETTING_PARAM_SECRET)
	    || (NM_IS_SETTING_802_1X (setting) && string_in_list (key, applet_8021x_cert_keys)))
		return;

	setting_name = nm_setting_get_name (setting);


	if (   (type == DBUS_TYPE_G_MAP_OF_STRING)
	    && NM_IS_SETTING_VPN (setting)
	    && !strcmp (key, NM_SETTING_VPN_SECRETS))
		return;

	if (type != G_TYPE_STRING) {
		g_warning ("Unhandled setting secret type (write) '%s/%s' : '%s'",
				 setting_name, key, g_type_name (type));
		return;
	}

	secret = g_value_get_string (value);
	if (secret && strlen (secret)) {
		nm_gconf_add_keyring_item (info->connection_uuid,
		                           info->connection_name,
		                           setting_name,
		                           key,
		                           secret);
	} else {


		keyring_delete_item (info->connection_uuid,
		                     setting_name,
		                     key);
	}
}
