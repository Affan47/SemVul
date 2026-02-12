static void connection_read_for_eos_plain(connection * const con) {


	ssize_t len;
	const int type = sock_addr_get_family(&con->dst_addr);
	char buf[16384];
	do {
		len = fdevent_socket_read_discard(con->fd, buf, sizeof(buf),
						  type, SOCK_STREAM);
	} while (len > 0 || (len < 0 && errno == EINTR));

	if (len < 0 && errno == EAGAIN) return;
      #if defined(EWOULDBLOCK) && EWOULDBLOCK != EAGAIN
	if (len < 0 && errno == EWOULDBLOCK) return;
      #endif


		con->close_timeout_ts = log_epoch_secs - (HTTP_LINGER_TIMEOUT+1);
}
