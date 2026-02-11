proxy_destroy_cb (DBusGProxy *proxy,
                  SyncevoServer *server)
{
    SyncevoServerPrivate *priv;
    priv = GET_PRIVATE (server);

    if (priv->proxy) {
        g_object_unref (priv->proxy);
    }
    priv->proxy = NULL;

    g_signal_emit (server, signals[SHUTDOWN], 0);
}
