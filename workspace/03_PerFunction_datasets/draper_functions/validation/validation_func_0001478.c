memory_port(
	struct cpssp *cpssp,
	const char *port,
	enum type *typep,
	unsigned int *sidep,
	unsigned long *addrp,
	unsigned int *bitp,
	unsigned long *addr2p,
	unsigned int *bit2p
)
{
	char *port2;


	if (strncmp(port, "bitflip", strlen("bitflip")) == 0) {
		*typep = FLIP;
		port += strlen("bitflip");
	} else if (strncmp(port, "stuck_at_0", strlen("stuck_at_0")) == 0) {
		*typep = STUCK_AT_0;
		port += strlen("stuck_at_0");
	} else if (strncmp(port, "stuck_at_1", strlen("stuck_at_1")) == 0) {
		*typep = STUCK_AT_1;
		port += strlen("stuck_at_1");
	} else if (strncmp(port, "coupling", strlen("coupling")) == 0) {
		*typep = COUPLING;
		port += strlen("coupling");
	} else {
		return 1;
	}


	if (*port == '/') {
		port++;
	} else {
		return 1;
	}


	*addrp = strtoul(port, &port2, 0);
	port = port2;


	if (*port == '/') {
		port++;
	} else {
		return 1;
	}


	*bitp = strtoul(port, &port2, 0);
	port = port2;

	*bitp += (*addrp & 3) * 8;
	*addrp &= ~3;

	if (*typep == COUPLING) {

		if (*port == '/') {
			port++;
		} else {
			return 1;
		}


		*addr2p = strtoul(port, &port2, 0);
		port = port2;


		if (*port == '/') {
			port++;
		} else {
			return 1;
		}


		*bit2p = strtoul(port, &port2, 0);
		port = port2;

		*bit2p += (*addr2p & 3) * 8;
		*addr2p &= ~3;
	}

	if (*port != '\0') {
		return 1;
	}


	*sidep = *addrp / cpssp->mem_size[0];
	*addrp %= cpssp->mem_size[0];

	return 0;
}
