source_ldap_set_property (GObject *object,
                          guint property_id,
                          const GValue *value,
                          GParamSpec *pspec)
{
	switch (property_id) {
		case PROP_AUTHENTICATION:
			e_source_ldap_set_authentication (
				E_SOURCE_LDAP (object),
				g_value_get_enum (value));
			return;

		case PROP_CAN_BROWSE:
			e_source_ldap_set_can_browse (
				E_SOURCE_LDAP (object),
				g_value_get_boolean (value));
			return;

		case PROP_FILTER:
			e_source_ldap_set_filter (
				E_SOURCE_LDAP (object),
				g_value_get_string (value));
			return;

		case PROP_LIMIT:
			e_source_ldap_set_limit (
				E_SOURCE_LDAP (object),
				g_value_get_uint (value));
			return;

		case PROP_ROOT_DN:
			e_source_ldap_set_root_dn (
				E_SOURCE_LDAP (object),
				g_value_get_string (value));
			return;

		case PROP_SCOPE:
			e_source_ldap_set_scope (
				E_SOURCE_LDAP (object),
				g_value_get_enum (value));
			return;

		case PROP_SECURITY:
			e_source_ldap_set_security (
				E_SOURCE_LDAP (object),
				g_value_get_enum (value));
			return;
	}

	G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
}
