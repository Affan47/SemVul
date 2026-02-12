pk_transaction_set_sender (PkTransaction *transaction, const gchar *sender)
{
	PkTransactionPrivate *priv = transaction->priv;

	g_return_val_if_fail (PK_IS_TRANSACTION (transaction), FALSE);
	g_return_val_if_fail (sender != NULL, FALSE);
	g_return_val_if_fail (transaction->priv->sender == NULL, FALSE);

	g_debug ("setting sender to %s", sender);
	priv->sender = g_strdup (sender);

	priv->watch_id =
		g_bus_watch_name (G_BUS_TYPE_SYSTEM,
				  sender,
				  G_BUS_NAME_WATCHER_FLAGS_NONE,
				  NULL,
				  pk_transaction_vanished_cb,
				  transaction,
				  NULL);


	priv->subject = polkit_system_bus_name_new (sender);
	priv->uid = pk_dbus_get_uid (priv->dbus, sender);


	if (priv->role == PK_ROLE_ENUM_REMOVE_PACKAGES ||
	    priv->role == PK_ROLE_ENUM_INSTALL_PACKAGES ||
	    priv->role == PK_ROLE_ENUM_UPDATE_PACKAGES) {
		priv->cmdline = pk_dbus_get_cmdline (priv->dbus, sender);
	}

	return TRUE;
}
