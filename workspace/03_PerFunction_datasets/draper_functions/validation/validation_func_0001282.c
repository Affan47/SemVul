get_nm_owner (NMSecretAgent *self)
{
	NMSecretAgentPrivate *priv = NM_SECRET_AGENT_GET_PRIVATE (self);
	GError *error = NULL;
	char *owner;

	if (!priv->nm_owner) {
		if (!dbus_g_proxy_call_with_timeout (priv->dbus_proxy,
			                                 "GetNameOwner", 2000, &error,
			                                 G_TYPE_STRING, NM_DBUS_SERVICE,
			                                 G_TYPE_INVALID,
			                                 G_TYPE_STRING, &owner,
			                                 G_TYPE_INVALID))
			return NULL;

		priv->nm_owner = g_strdup (owner);
		g_free (owner);
	}

	return priv->nm_owner;
}
