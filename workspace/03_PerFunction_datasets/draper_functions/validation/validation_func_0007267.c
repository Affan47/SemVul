connection_unregister(struct vpn_provider *provider)
{
	DBG("provider %p path %s", provider, provider->path);

	if (provider->path == NULL)
		return -EALREADY;

	g_dbus_unregister_interface(connection, provider->path,
				VPN_CONNECTION_INTERFACE);

	g_free(provider->path);
	provider->path = NULL;

	return 0;
}
