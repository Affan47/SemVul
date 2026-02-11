sys_getsockopt(struct tcb *tcp)
{
	if (entering(tcp)) {
		tprintf("%ld, ", tcp->u_arg[0]);
		printxval(socketlayers, tcp->u_arg[1], "SOL_???");
		tprintf (", ");
		switch (tcp->u_arg[1]) {
		case SOL_SOCKET:
			printxval(sockoptions, tcp->u_arg[2], "SO_???");
			break;
#ifdef SOL_IP
		case SOL_IP:
			printxval(sockipoptions, tcp->u_arg[2], "IP_???");
			break;
#endif
#ifdef SOL_IPV6
		case SOL_IPV6:
			printxval(sockipv6options, tcp->u_arg[2], "IPV6_???");
			break;
#endif
#ifdef SOL_IPX
		case SOL_IPX:
			printxval(sockipxoptions, tcp->u_arg[2], "IPX_???");
			break;
#endif
#ifdef SOL_PACKET
		case SOL_PACKET:
			printxval(sockpacketoptions, tcp->u_arg[2], "PACKET_???");
			break;
#endif
#ifdef SOL_TCP
		case SOL_TCP:
			printxval(socktcpoptions, tcp->u_arg[2], "TCP_???");
			break;
#endif


		default:
			tprintf("%lu", tcp->u_arg[2]);
			break;
		}
		tprintf (", ");
	} else {
		int len;
		if (syserror(tcp) || umove (tcp, tcp->u_arg[4], &len) < 0) {
			tprintf("%#lx, %#lx",
				tcp->u_arg[3], tcp->u_arg[4]);
			return 0;
		}

		switch (tcp->u_arg[1]) {
		case SOL_SOCKET:
			switch (tcp->u_arg[2]) {
#ifdef SO_LINGER
			case SO_LINGER:
				if (len == sizeof (struct linger)) {
					struct linger linger;
					if (umove (tcp,
						   tcp->u_arg[3],
						   &linger) < 0)
						break;
					tprintf("{onoff=%d, linger=%d}, "
						"[%d]",
						linger.l_onoff,
						linger.l_linger,
						len);
					return 0;
				}
				break;
#endif
			}
			break;
		case SOL_PACKET:
			switch (tcp->u_arg[2]) {
#ifdef PACKET_STATISTICS
			case PACKET_STATISTICS:
				if (len == sizeof(struct tpacket_stats)) {
					struct tpacket_stats stats;
					if (umove (tcp,
						   tcp->u_arg[3],
						   &stats) < 0)
						break;
					tprintf("{packets=%u, drops=%u}, "
						"[%d]",
						stats.tp_packets,
						stats.tp_drops,
						len);
					return 0;
				}
				break;
#endif
			}
			break;
		}

		if (len == sizeof (int)) {
			printnum_int(tcp, tcp->u_arg[3], "%d");
		}
		else {
			printstr (tcp, tcp->u_arg[3], len);
		}
		tprintf(", [%d]", len);
	}
	return 0;
}
