e_client_set_capabilities (EClient *client,
                           const gchar *capabilities)
{
	g_return_if_fail (E_IS_CLIENT (client));

	g_rec_mutex_lock (&client->priv->prop_mutex);

	g_slist_foreach (client->priv->capabilities, (GFunc) g_free, NULL);
	g_slist_free (client->priv->capabilities);
	client->priv->capabilities = e_client_util_parse_comma_strings (capabilities);

	g_rec_mutex_unlock (&client->priv->prop_mutex);

	g_object_notify (G_OBJECT (client), "capabilities");
}
