__vpn_provider_create_from_config(GHashTable *settings,
				const char *config_ident,
				const char *config_entry)
{
	struct vpn_provider *provider;
	const char *type, *name, *host, *domain, *networks_str;
	GSList *networks;
	char *ident = NULL;
	GHashTableIter hash;
	gpointer value, key;
	int err;

	type = get_string(settings, "Type");
	name = get_string(settings, "Name");
	host = get_string(settings, "Host");
	domain = get_string(settings, "Domain");
	networks_str = get_string(settings, "Networks");
	networks = parse_user_networks(networks_str);

	if (host == NULL || domain == NULL) {
		err = -EINVAL;
		goto fail;
	}

	DBG("type %s name %s networks %s", type, name, networks_str);

	if (type == NULL || name == NULL) {
		err = -EOPNOTSUPP;
		goto fail;
	}

	ident = __vpn_provider_create_identifier(host, domain);
	DBG("ident %s", ident);

	provider = __vpn_provider_lookup(ident);
	if (provider == NULL) {
		provider = vpn_provider_get(ident);
		if (provider == NULL) {
			DBG("can not create provider");
			err = -EOPNOTSUPP;
			goto fail;
		}

		provider->host = g_strdup(host);
		provider->domain = g_strdup(domain);
		provider->name = g_strdup(name);
		provider->type = g_ascii_strdown(type, -1);

		provider->config_file = g_strdup(config_ident);
		provider->config_entry = g_strdup(config_entry);

		provider_register(provider);

		provider_resolv_host_addr(provider);
	}

	if (networks != NULL) {
		g_slist_free_full(provider->user_networks, free_route);
		provider->user_networks = networks;
		set_user_networks(provider, provider->user_networks);
	}

	g_hash_table_iter_init(&hash, settings);

	while (g_hash_table_iter_next(&hash, &key, &value) == TRUE)
		__vpn_provider_set_string_immutable(provider, key, value);

	provider->immutable = TRUE;

	vpn_provider_save(provider);

	err = provider_register(provider);
	if (err != 0 && err != -EALREADY)
		goto fail;

	connection_register(provider);

	DBG("provider %p index %d path %s", provider, provider->index,
							provider->path);

	connection_added_signal(provider);

	g_free(ident);

	return 0;

fail:
	g_free(ident);
	g_slist_free_full(networks, free_route);

	return err;
}
