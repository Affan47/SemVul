netsnmp_tcpbase_send(netsnmp_transport *t, void *buf, int size,
                         void **opaque, int *olength) {
    int rc = -1;

    if (t != NULL && t->sock >= 0) {
	while (rc < 0) {
	    rc = sendto(t->sock, buf, size, 0, NULL, 0);
	    if (rc < 0 && errno != EINTR) {
		break;
	    }
	}
    }
    return rc;
}
