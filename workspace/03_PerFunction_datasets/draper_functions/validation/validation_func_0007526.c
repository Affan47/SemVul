handle_method_call (GDBusConnection       *connection,
                    const gchar           *sender,
                    const gchar           *object_path,
                    const gchar           *interface_name,
                    const gchar           *method_name,
                    GVariant              *parameters,
                    GDBusMethodInvocation *invocation,
                    gpointer               user_data)
{
  const gchar *pac_url, *lookup_url;

  g_variant_get (parameters, "(&s&s)", &pac_url, &lookup_url);

  if (!g_ascii_strncasecmp (pac_url, "http", 4) ||
      !g_ascii_strncasecmp (pac_url, "file:", 5))
    {
      gchar *libproxy_url = g_strdup_printf ("pac+%s", pac_url);
      g_setenv ("http_proxy", libproxy_url, TRUE);
      g_free (libproxy_url);
    }
  else
    g_setenv ("http_proxy", "wpad://", TRUE);

  g_proxy_resolver_lookup_async (resolver, lookup_url,
				 NULL, got_proxies, invocation);
}
