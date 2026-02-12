get_gre_eui64_u_bit(guint32 addr)
{
    static const struct {
        guint32 mask;
        guint32 result;
    } items[] = {
        {0xff000000}, {0x7f000000},
        {0xf0000000}, {0xe0000000},
        {0xffffff00}, {0xe0000000},
        {0xffffffff}, {INADDR_BROADCAST},
        {0xff000000}, {0x00000000},
        {0xff000000}, {0x0a000000},
        {0xfff00000}, {0xac100000},
        {0xffff0000}, {0xc0a80000},
        {0xffff0000}, {0xa9fe0000},
        {0xffffff00}, {0xc0586300},
        {0xffffff00}, {0xc0000200},
        {0xfffe0000}, {0xc6120000},
    };
    guint i;

    for (i = 0; i < G_N_ELEMENTS(items); i++) {
        if ((addr & htonl(items[i].mask)) == htonl(items[i].result))
            return 0x00;
    }
    return 0x02;
}
