gdata_service_get_proxy_uri (GDataService *self)
{
	SoupURI *proxy_uri;

	g_return_val_if_fail (GDATA_IS_SERVICE (self), NULL);

	g_object_get (self->priv->session, SOUP_SESSION_PROXY_URI, &proxy_uri, NULL);
	g_object_unref (proxy_uri);

	return proxy_uri;
}
