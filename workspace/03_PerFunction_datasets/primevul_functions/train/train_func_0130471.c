static void h2_detach(struct conn_stream *cs)
{
	struct h2s *h2s = cs->ctx;
	struct h2c *h2c;
	struct session *sess;

	cs->ctx = NULL;
	if (!h2s)
		return;

	sess = h2s->sess;
	h2c = h2s->h2c;
	h2s->cs = NULL;
	h2c->nb_cs--;
	if (h2c->flags & H2_CF_DEM_TOOMANY &&
	    !h2_has_too_many_cs(h2c)) {
		h2c->flags &= ~H2_CF_DEM_TOOMANY;
		h2c_restart_reading(h2c);
	}


	if (!(cs->conn->flags & CO_FL_ERROR) &&
	    (h2c->st0 < H2_CS_ERROR) &&
	    (h2s->flags & (H2_SF_BLK_MBUSY | H2_SF_BLK_MROOM | H2_SF_BLK_MFCTL)))
		return;

	if ((h2c->flags & H2_CF_DEM_BLOCK_ANY && h2s->id == h2c->dsi) ||
	    (h2c->flags & H2_CF_MUX_BLOCK_ANY && h2s->id == h2c->msi)) {


		h2c->flags &= ~H2_CF_DEM_BLOCK_ANY;
		h2c->flags &= ~H2_CF_MUX_BLOCK_ANY;
		h2c_restart_reading(h2c);
	}

	h2s_destroy(h2s);

	if (h2c->flags & H2_CF_IS_BACK &&
	    (h2c->proxy->options2 & PR_O2_USE_HTX)) {
		if (!(h2c->conn->flags &
		    (CO_FL_ERROR | CO_FL_SOCK_RD_SH | CO_FL_SOCK_WR_SH))) {
			if (!h2c->conn->owner) {
				h2c->conn->owner = sess;
				if (!session_add_conn(sess, h2c->conn, h2c->conn->target)) {
					h2c->conn->owner = NULL;
					if (eb_is_empty(&h2c->streams_by_id)) {
						if (!srv_add_to_idle_list(objt_server(h2c->conn->target), h2c->conn))

							h2c->conn->mux->destroy(h2c->conn);
						return;
					}
				}
			}
			if (eb_is_empty(&h2c->streams_by_id)) {
				if (session_check_idle_conn(h2c->conn->owner, h2c->conn) != 0)

					return;
			}

			if ((h2c->proxy->options & PR_O_REUSE_MASK) == PR_O_REUSE_NEVR)
				h2c->conn->flags |= CO_FL_PRIVATE;
			if (LIST_ISEMPTY(&h2c->conn->list) && h2c->nb_streams < h2_settings_max_concurrent_streams) {
				struct server *srv = objt_server(h2c->conn->target);

				if (srv) {
					if (h2c->conn->flags & CO_FL_PRIVATE)
						LIST_ADD(&srv->priv_conns[tid], &h2c->conn->list);
					else
						LIST_ADD(&srv->idle_conns[tid], &h2c->conn->list);
				}

			}
		}
	}


	if (eb_is_empty(&h2c->streams_by_id) &&
	    ((h2c->conn->flags & CO_FL_ERROR) ||
	     (h2c->st0 >= H2_CS_ERROR && !h2c->task) ||
	     (h2c->flags & (H2_CF_GOAWAY_FAILED | H2_CF_GOAWAY_SENT)) ||
	     (!(h2c->conn->owner)) ||
	     (!b_data(&h2c->mbuf) &&
	      (conn_xprt_read0_pending(h2c->conn) ||
	       (h2c->last_sid >= 0 && h2c->max_id >= h2c->last_sid))))) {

		h2_release(h2c->conn);
	}
	else if (h2c->task) {
		if (eb_is_empty(&h2c->streams_by_id) || b_data(&h2c->mbuf)) {
			h2c->task->expire = tick_add(now_ms, h2c->last_sid < 0 ? h2c->timeout : h2c->shut_timeout);
			task_queue(h2c->task);
		}
		else
			h2c->task->expire = TICK_ETERNITY;
	}
}
