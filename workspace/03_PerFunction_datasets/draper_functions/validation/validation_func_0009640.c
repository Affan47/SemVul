set_string(struct vpn_provider *provider,
			const char *key, const char *value,
			gboolean hide_value, gboolean immutable)
{
	DBG("provider %p key %s immutable %s value %s", provider, key,
		immutable ? "yes" : "no",
		hide_value ? "<not printed>" : value);

	if (g_str_equal(key, "Type") == TRUE) {
		g_free(provider->type);
		provider->type = g_ascii_strdown(value, -1);
		send_value(provider->path, "Type", provider->type);
	} else if (g_str_equal(key, "Name") == TRUE) {
		g_free(provider->name);
		provider->name = g_strdup(value);
		send_value(provider->path, "Name", provider->name);
	} else if (g_str_equal(key, "Host") == TRUE) {
		g_free(provider->host);
		provider->host = g_strdup(value);
		send_value(provider->path, "Host", provider->host);
	} else if (g_str_equal(key, "VPN.Domain") == TRUE ||
			g_str_equal(key, "Domain") == TRUE) {
		g_free(provider->domain);
		provider->domain = g_strdup(value);
		send_value(provider->path, "Domain", provider->domain);
	} else {
		struct vpn_setting *setting;

		setting = g_hash_table_lookup(provider->setting_strings, key);
		if (setting != NULL && immutable == FALSE &&
						setting->immutable == TRUE) {
			DBG("Trying to set immutable variable %s", key);
			return -EPERM;
		}

		setting = g_try_new0(struct vpn_setting, 1);
		if (setting == NULL)
			return -ENOMEM;

		setting->value = g_strdup(value);
		setting->hide_value = hide_value;

		if (immutable == TRUE)
			setting->immutable = TRUE;

		if (hide_value == FALSE)
			send_value(provider->path, key, setting->value);

		g_hash_table_replace(provider->setting_strings,
				g_strdup(key), setting);
	}

	return 0;
}
