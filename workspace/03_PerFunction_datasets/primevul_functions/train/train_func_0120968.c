static int originates_from_local_iface(AvahiServer *s, AvahiIfIndex iface, const AvahiAddress *a, uint16_t port) {
    assert(s);
    assert(iface != AVAHI_IF_UNSPEC);
    assert(a);


    if (port != AVAHI_MDNS_PORT)
        return 0;

    return avahi_interface_has_address(s->monitor, iface, a);
}
