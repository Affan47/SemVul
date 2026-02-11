kernel_send(uint8_t *packet, size_t bytes, struct nhrp_interface *out,
		struct nhrp_address *to)
{
	struct sockaddr_ll lladdr;
	struct iovec iov = {
		.iov_base = (void*) packet,
		.iov_len = bytes
	};
	struct msghdr msg = {
		.msg_name = &lladdr,
		.msg_namelen = sizeof(lladdr),
		.msg_iov = &iov,
		.msg_iovlen = 1,
	};
	int status;

	if (to->addr_len > sizeof(lladdr.sll_addr)) {
		nhrp_error("Destination NBMA address too long");
		return FALSE;
	}

	memset(&lladdr, 0, sizeof(lladdr));
	lladdr.sll_family = AF_PACKET;
	lladdr.sll_protocol = ETHPROTO_NHRP;
	lladdr.sll_ifindex = out->index;
	lladdr.sll_halen = to->addr_len;
	memcpy(lladdr.sll_addr, to->addr, to->addr_len);

	status = sendmsg(packet_io.fd, &msg, 0);
	if (status < 0) {
		nhrp_error("Cannot send packet to %s(%d): %s",
			   out->name, out->index, strerror(errno));
		return FALSE;
	}

	return TRUE;
}
