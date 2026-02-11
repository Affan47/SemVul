php_sockop_read(php_stream *stream, char *buf, size_t count TSRMLS_DC)
{
	php_netstream_data_t *sock = (php_netstream_data_t*)stream->abstract;
	int nr_bytes = 0;

	if (sock->socket == -1) {
		return 0;
	}

	if (sock->is_blocked) {
		php_sock_stream_wait_for_data(stream, sock TSRMLS_CC);
		if (sock->timeout_event)
			return 0;
	}

	nr_bytes = recv(sock->socket, buf, count, (sock->is_blocked && sock->timeout.tv_sec != -1) ? MSG_DONTWAIT : 0);

	stream->eof = (nr_bytes == 0 || (nr_bytes == -1 && php_socket_errno() != EWOULDBLOCK));

	if (nr_bytes > 0) {
		php_stream_notify_progress_increment(stream->context, nr_bytes, 0);
	}

	if (nr_bytes < 0) {
		nr_bytes = 0;
	}

	return nr_bytes;
}
