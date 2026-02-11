on_accountsservice_ready (GObject       *object,
                          GAsyncResult  *result,
                          gpointer       user_data)
{
        GdmSimpleSlave *slave = GDM_SIMPLE_SLAVE (user_data);
        GError *local_error = NULL;

        slave->priv->accountsservice_proxy = g_dbus_proxy_new_for_bus_finish (result, &local_error);
        if (!slave->priv->accountsservice_proxy) {
                g_error ("Failed to contact accountsservice: %s", local_error->message);
        }

        g_dbus_proxy_call (slave->priv->accountsservice_proxy, "ListCachedUsers", NULL, 0, -1, NULL,
                           on_list_cached_users_complete, slave);
}
