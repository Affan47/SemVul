vnc_connection_hextile_rect(VncConnection *conn,
                                        guint8 flags,
                                        guint16 x, guint16 y,
                                        guint16 width, guint16 height,
                                        guint8 *fg, guint8 *bg)
{
    VncConnectionPrivate *priv = conn->priv;
    int i;

    if (flags & 0x01) {
        vnc_connection_raw_update(conn, x, y, width, height);
    } else {

        if (flags & 0x02)
            vnc_connection_read_pixel(conn, bg);


        if (flags & 0x04)
            vnc_connection_read_pixel(conn, fg);

        vnc_framebuffer_fill(priv->fb, bg, x, y, width, height);


        if (flags & 0x08) {
            guint8 n_rects = vnc_connection_read_u8(conn);

            for (i = 0; i < n_rects; i++) {
                guint8 xy, wh;


                if (flags & 0x10)
                    vnc_connection_read_pixel(conn, fg);

                xy = vnc_connection_read_u8(conn);
                wh = vnc_connection_read_u8(conn);

                vnc_framebuffer_fill(priv->fb, fg,
                                     x + nibhi(xy), y + niblo(xy),
                                     nibhi(wh) + 1, niblo(wh) + 1);
            }
        }
    }
}
