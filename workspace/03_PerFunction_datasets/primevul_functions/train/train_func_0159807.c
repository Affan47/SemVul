static int rtl8139_RxWrap(RTL8139State *s)
{

    return (s->RxConfig & (1 << 7));
}
