vnc_connection_read_cint(VncConnection *conn)
{
    guint32 value = 0;
    guint8 val;

    val = vnc_connection_read_u8(conn);
    value = (val & 0x7F);
    if (!(val & 0x80))
        return value;

    val = vnc_connection_read_u8(conn);
    value |= (val & 0x7F) << 7;

    if (!(val & 0x80))
        return value;

    value |= vnc_connection_read_u8(conn) << 14;

    return value;
}
