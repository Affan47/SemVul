grab_media_player_keys_cb (GDBusProxy                 *proxy,
			   GAsyncResult               *res,
			   TotemMediaPlayerKeysPlugin *pi)
{
	GVariant *variant;
	GError *error = NULL;

	variant = g_dbus_proxy_call_finish (proxy, res, &error);
	pi->priv->cancellable = NULL;

	if (variant == NULL) {
		if (!g_error_matches (error, G_IO_ERROR, G_IO_ERROR_CANCELLED))
			g_warning ("Failed to call \"GrabMediaPlayerKeys\": %s", error->message);
		g_error_free (error);
		return;
	}
	g_variant_unref (variant);

	g_object_unref (pi);
}
