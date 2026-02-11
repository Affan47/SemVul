init (void)
{
#ifdef HAVE_GUPNP
	upnp_context = gupnp_context_new(NULL, NULL, 0, NULL);
	g_assert(upnp_context != NULL);

	upnp_control_point = gupnp_control_point_new(upnp_context, "urn:schemas-upnp-org:service:WANIPConnection:1");
	g_assert(upnp_control_point != NULL);

	upnp_service_proxy = NULL;

	g_signal_connect(upnp_control_point, "service-proxy-available", G_CALLBACK(on_service_proxy_available), NULL);

	gssdp_resource_browser_set_active(GSSDP_RESOURCE_BROWSER(upnp_control_point), TRUE);
#endif

#ifdef HAVE_GUPNP_IGD
	upnp_igd = gupnp_simple_igd_new();
	g_assert(upnp_igd != NULL);
#endif

#ifdef HAVE_MINIUPNPC
	{
		gchar addr[64] = { '\0' };
#ifdef HAVE_MINIUPNPC_16
		gint error;

		miniupnpc_dev = upnpDiscover(1000, NULL, NULL, 0, 0, &error);
#else
		miniupnpc_dev = upnpDiscover(1000, NULL, NULL, 0);
#endif
		g_assert(miniupnpc_dev != NULL);

		UPNP_GetValidIGD(miniupnpc_dev, &miniupnpc_urls, &miniupnpc_datas, addr, sizeof(addr));
	}
#endif

	return TRUE;
}
