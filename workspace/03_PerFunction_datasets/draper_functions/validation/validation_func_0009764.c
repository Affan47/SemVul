log_tcp_connect(struct triton_md_handler_t *h)
{
	struct tcp_target_t *t = container_of(h, typeof(*t), hnd);

	if (connect(t->hnd.fd, &t->addr, sizeof(t->addr))) {
		if (errno == EAGAIN)
			return 0;
		if (errno == EINPROGRESS)
			return 0;
		log_emerg("log-tcp: connect: %s\n", strerror(errno));
		triton_md_unregister_handler(&t->hnd, 1);
		triton_timer_add(&tcp_ctx, &t->conn_timer, 0);
		return 0;
	}

	t->hnd.write = log_tcp_write;

	triton_md_disable_handler(&t->hnd, MD_MODE_WRITE);

	spin_lock(&t->lock);
	t->connected = 1;
	t->wait = 1;
	spin_unlock(&t->lock);

	if (send_log(t))
		triton_md_enable_handler(&t->hnd, MD_MODE_WRITE);

	return 0;
}
