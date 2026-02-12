static int h2_send(struct h2c *h2c)
{
	struct connection *conn = h2c->conn;
	int done;
	int sent = 0;

	if (conn->flags & CO_FL_ERROR)
		return 1;


	if (conn->flags & (CO_FL_HANDSHAKE|CO_FL_WAIT_L4_CONN|CO_FL_WAIT_L6_CONN)) {

		goto schedule;
	}


	done = 0;
	while (!done) {
		unsigned int flags = 0;


		while (((h2c->flags & (H2_CF_MUX_MFULL|H2_CF_MUX_MALLOC)) == 0) && !done)
			done = h2_process_mux(h2c);

		if (conn->flags & CO_FL_ERROR)
			break;

		if (h2c->flags & (H2_CF_MUX_MFULL | H2_CF_DEM_MBUSY | H2_CF_DEM_MROOM))
			flags |= CO_SFL_MSG_MORE;

		if (b_data(&h2c->mbuf)) {
			int ret = conn->xprt->snd_buf(conn, &h2c->mbuf, b_data(&h2c->mbuf), flags);
			if (!ret)
				break;
			sent = 1;
			b_del(&h2c->mbuf, ret);
			b_realign_if_empty(&h2c->mbuf);
		}


		h2c->flags &= ~(H2_CF_MUX_MFULL | H2_CF_DEM_MROOM);
	}

	if (conn->flags & CO_FL_SOCK_WR_SH) {

		b_reset(&h2c->mbuf);
	}


	if (!(h2c->flags & (H2_CF_MUX_MFULL | H2_CF_DEM_MROOM))) {
		while (!LIST_ISEMPTY(&h2c->send_list)) {
			struct h2s *h2s = LIST_ELEM(h2c->send_list.n,
			    struct h2s *, list);
			LIST_DEL(&h2s->list);
			LIST_INIT(&h2s->list);
			LIST_ADDQ(&h2c->sending_list, &h2s->list);
			h2s->send_wait->events &= ~SUB_RETRY_SEND;
			h2s->send_wait->events |= SUB_CALL_UNSUBSCRIBE;
			tasklet_wakeup(h2s->send_wait->task);
		}
	}

	if (!b_data(&h2c->mbuf))
		return sent;
schedule:
	if (!(h2c->wait_event.events & SUB_RETRY_SEND))
		conn->xprt->subscribe(conn, SUB_RETRY_SEND, &h2c->wait_event);
	return sent;
}
