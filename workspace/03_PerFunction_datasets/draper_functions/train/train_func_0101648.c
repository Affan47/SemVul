network_write_chunkqueue(server *srv, connection *con, chunkqueue *cq) {
	int ret = -1;
	off_t written = 0;
#ifdef TCP_CORK
	int corked = 0;
#endif
	server_socket *srv_socket = con->srv_socket;

	if (con->conf.global_kbytes_per_second &&
	    *(con->conf.global_bytes_per_second_cnt_ptr) > con->conf.global_kbytes_per_second * 1024) {


		con->traffic_limit_reached = 1;
		joblist_append(srv, con);

		return 1;
	}

	written = cq->bytes_out;

#ifdef TCP_CORK


	if (cq->first && cq->first->next) {
		corked = 1;
		setsockopt(con->fd, IPPROTO_TCP, TCP_CORK, &corked, sizeof(corked));
	}
#endif

	if (srv_socket->is_ssl) {
#ifdef USE_OPENSSL
		ret = srv->network_ssl_backend_write(srv, con, con->ssl, cq);
#endif
	} else {
		ret = srv->network_backend_write(srv, con, con->fd, cq);
	}

	if (ret >= 0) {
		chunkqueue_remove_finished_chunks(cq);
		ret = chunkqueue_is_empty(cq) ? 0 : 1;
	}

#ifdef TCP_CORK
	if (corked) {
		corked = 0;
		setsockopt(con->fd, IPPROTO_TCP, TCP_CORK, &corked, sizeof(corked));
	}
#endif

	written = cq->bytes_out - written;
	con->bytes_written += written;
	con->bytes_written_cur_second += written;

	*(con->conf.global_bytes_per_second_cnt_ptr) += written;

	if (con->conf.kbytes_per_second &&
	    (con->bytes_written_cur_second > con->conf.kbytes_per_second * 1024)) {


		con->traffic_limit_reached = 1;
		joblist_append(srv, con);
	}
	return ret;
}
