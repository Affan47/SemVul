portset_remove(isc_portset_t *portset, in_port_t port) {
	if (portset_isset(portset, port)) {
		portset->nports--;
		portset->buf[port >> 5] &= ~(1 << (port & 31));
	}
}
