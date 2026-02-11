notify_notification_finalize (GObject *object)
{
        NotifyNotification        *obj = NOTIFY_NOTIFICATION (object);
        NotifyNotificationPrivate *priv = obj->priv;
        GDBusProxy                *proxy;

        _notify_cache_remove_notification (obj);

        g_free (priv->app_name);
        g_free (priv->summary);
        g_free (priv->body);
        g_free (priv->icon_name);

        if (priv->actions != NULL) {
                g_slist_foreach (priv->actions, (GFunc) g_free, NULL);
                g_slist_free (priv->actions);
        }

        if (priv->action_map != NULL)
                g_hash_table_destroy (priv->action_map);

        if (priv->hints != NULL)
                g_hash_table_destroy (priv->hints);

        proxy = _notify_get_proxy (NULL);
        if (proxy != NULL && priv->proxy_signal_handler != 0) {
                g_signal_handler_disconnect (proxy, priv->proxy_signal_handler);
        }

        g_free (obj->priv);

        G_OBJECT_CLASS (parent_class)->finalize (object);
}
