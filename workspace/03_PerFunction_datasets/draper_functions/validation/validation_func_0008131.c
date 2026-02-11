ews_settings_get_property (GObject *object,
                            guint property_id,
                            GValue *value,
                            GParamSpec *pspec)
{
	switch (property_id) {
		case PROP_AUTH_MECHANISM:
			g_value_take_string (
				value,
				camel_network_settings_dup_auth_mechanism (
				CAMEL_NETWORK_SETTINGS (object)));
			return;

		case PROP_CHECK_ALL:
			g_value_set_boolean (
				value,
				camel_ews_settings_get_check_all (
				CAMEL_EWS_SETTINGS (object)));
			return;

		case PROP_EMAIL:
			g_value_take_string (
				value,
				camel_ews_settings_dup_email (
				CAMEL_EWS_SETTINGS (object)));
			return;

		case PROP_FILTER_JUNK:
			g_value_set_boolean (
				value,
				camel_ews_settings_get_filter_junk (
				CAMEL_EWS_SETTINGS (object)));
			return;

		case PROP_FILTER_JUNK_INBOX:
			g_value_set_boolean (
				value,
				camel_ews_settings_get_filter_junk_inbox (
				CAMEL_EWS_SETTINGS (object)));
			return;

		case PROP_FOLDERS_INITIALIZED:
			g_value_set_boolean (
				value,
				camel_ews_settings_get_folders_initialized (
				CAMEL_EWS_SETTINGS (object)));
			return;

		case PROP_GAL_UID:
			g_value_take_string (
				value,
				camel_ews_settings_dup_gal_uid (
				CAMEL_EWS_SETTINGS (object)));
			return;

		case PROP_HOST:
			g_value_take_string (
				value,
				camel_network_settings_dup_host (
				CAMEL_NETWORK_SETTINGS (object)));
			return;

		case PROP_HOSTURL:
			g_value_take_string (
				value,
				camel_ews_settings_dup_hosturl (
				CAMEL_EWS_SETTINGS (object)));
			return;

		case PROP_OABURL:
			g_value_take_string (
				value,
				camel_ews_settings_dup_oaburl (
				CAMEL_EWS_SETTINGS (object)));
			return;

		case PROP_OAB_OFFLINE:
			g_value_set_boolean (
				value,
				camel_ews_settings_get_oab_offline (
				CAMEL_EWS_SETTINGS (object)));
			return;

		case PROP_OAL_SELECTED:
			g_value_take_string (
				value,
				camel_ews_settings_dup_oal_selected (
				CAMEL_EWS_SETTINGS (object)));
			return;

		case PROP_PORT:
			g_value_set_uint (
				value,
				camel_network_settings_get_port (
				CAMEL_NETWORK_SETTINGS (object)));
			return;

		case PROP_SECURITY_METHOD:
			g_value_set_enum (
				value,
				camel_network_settings_get_security_method (
				CAMEL_NETWORK_SETTINGS (object)));
			return;

		case PROP_TIMEOUT:
			g_value_set_uint (
				value,
				camel_ews_settings_get_timeout (
				CAMEL_EWS_SETTINGS (object)));
			return;

		case PROP_USER:
			g_value_take_string (
				value,
				camel_network_settings_dup_user (
				CAMEL_NETWORK_SETTINGS (object)));
			return;

		case PROP_USE_IMPERSONATION:
			g_value_set_boolean (
				value,
				camel_ews_settings_get_use_impersonation (
				CAMEL_EWS_SETTINGS (object)));
			return;

		case PROP_IMPERSONATE_USER:
			g_value_take_string (
				value,
				camel_ews_settings_dup_impersonate_user (
				CAMEL_EWS_SETTINGS (object)));
			return;
	}

	G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
}
