fr_packet_list_recv(fr_packet_list_t *pl, fd_set *set)
{
	int start;
	RADIUS_PACKET *packet;

	if (!pl || !set) return NULL;

	start = pl->last_recv;
	do {
		start++;
		start &= SOCKOFFSET_MASK;

		if (pl->sockets[start].sockfd == -1) continue;

		if (!FD_ISSET(pl->sockets[start].sockfd, set)) continue;

#ifdef WITH_TCP
		if (pl->sockets[start].proto == IPPROTO_TCP) {
			packet = fr_tcp_recv(pl->sockets[start].sockfd, 0);
		} else
#endif
		packet = rad_recv(pl->sockets[start].sockfd, 0);
		if (!packet) continue;


		pl->last_recv = start;
		return packet;
	} while (start != pl->last_recv);

	return NULL;
}
