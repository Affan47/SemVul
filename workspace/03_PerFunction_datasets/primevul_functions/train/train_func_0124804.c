static int dhcp_l2_socket(int ifindex)
{
	int fd;
	struct sockaddr_ll sock;


	static const struct sock_filter filter_instr[] = {

		BPF_STMT(BPF_LD|BPF_B|BPF_ABS, 9),

		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, IPPROTO_UDP, 2, 0),

		BPF_STMT(BPF_LD|BPF_W|BPF_ABS, 2),
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, 0x08000604, 3, 4),

		BPF_STMT(BPF_LDX|BPF_B|BPF_MSH, 0),

		BPF_STMT(BPF_LD|BPF_W|BPF_IND, 0),

		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, SERVER_AND_CLIENT_PORTS, 0, 1),

		BPF_STMT(BPF_RET|BPF_K, 0x0fffffff),
		BPF_STMT(BPF_RET|BPF_K, 0),
	};

	static const struct sock_fprog filter_prog = {
		.len = sizeof(filter_instr) / sizeof(filter_instr[0]),

		.filter = (struct sock_filter *) filter_instr,
	};

	fd = socket(PF_PACKET, SOCK_DGRAM | SOCK_CLOEXEC, 0);
	if (fd < 0)
		return -errno;

	if (SERVER_PORT == 67 && CLIENT_PORT == 68)

		setsockopt(fd, SOL_SOCKET, SO_ATTACH_FILTER, &filter_prog,
							sizeof(filter_prog));

	memset(&sock, 0, sizeof(sock));
	sock.sll_family = AF_PACKET;
	sock.sll_protocol = htons(ETH_P_IP);
	sock.sll_ifindex = ifindex;

	if (bind(fd, (struct sockaddr *) &sock, sizeof(sock)) != 0) {
		int err = -errno;
		close(fd);
		return err;
	}

	return fd;
}
