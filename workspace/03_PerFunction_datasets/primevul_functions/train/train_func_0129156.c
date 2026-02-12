gdm_display_disconnect (GdmDisplay *self)
{
        GdmDisplayPrivate *priv;

        guint32 unused_bits = 0b11100000000000000000000000000000;
        XID highest_client, client;
        guint32 client_increment;
        const xcb_setup_t *setup;

        priv = gdm_display_get_instance_private (self);

        if (priv->xcb_connection == NULL) {
                return;
        }

        setup = xcb_get_setup (priv->xcb_connection);


        highest_client = (XID) ~unused_bits & ~setup->resource_id_mask;
        client_increment = setup->resource_id_mask + 1;


        for (client = 0;
             client <= highest_client;
             client += client_increment) {

                if (client != setup->resource_id_base)
                        xcb_kill_client (priv->xcb_connection, client);
        }

        xcb_flush (priv->xcb_connection);

        g_clear_pointer (&priv->xcb_connection, xcb_disconnect);
}
