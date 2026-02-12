ns_client_dropport(in_port_t port) {
	switch (port) {
	case 7:
	case 13:
	case 19:
	case 37:
		return (DROPPORT_REQUEST);
	case 464:
		return (DROPPORT_RESPONSE);
	}
	return (DROPPORT_NO);
}
