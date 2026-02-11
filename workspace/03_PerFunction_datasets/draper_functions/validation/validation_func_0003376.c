_gdm_xdmcp_display_set_remote_address (GdmXdmcpDisplay *display,
                                       GdmAddress      *address)
{
        if (display->priv->remote_address != NULL) {
                gdm_address_free (display->priv->remote_address);
        }

        g_assert (address != NULL);

        gdm_address_debug (address);
        display->priv->remote_address = gdm_address_copy (address);
}
