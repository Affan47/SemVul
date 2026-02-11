vnc_connection_ledstate_change(VncConnection *conn)
{
    VncConnectionPrivate *priv = conn->priv;
    struct signal_data sigdata;

    priv->ledstate = vnc_connection_read_u8(conn);

    VNC_DEBUG("LED state: %d\n", priv->ledstate);

    sigdata.params.ledstate = priv->ledstate;
    vnc_connection_emit_main_context(conn, VNC_LED_STATE, &sigdata);
}
