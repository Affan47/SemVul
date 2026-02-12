static struct h2s *h2c_frt_handle_headers(struct h2c *h2c, struct h2s *h2s)
{
	struct buffer rxbuf = BUF_NULL;
	uint32_t flags = 0;
	int error;

	if (!h2c->dfl) {

		error = H2_ERR_FRAME_SIZE_ERROR;
		sess_log(h2c->conn->owner);
		goto conn_err;
	}

	if (!b_size(&h2c->dbuf))
		return NULL;

	if (b_data(&h2c->dbuf) < h2c->dfl && !b_full(&h2c->dbuf))
		return NULL;


	if (h2s->st != H2_SS_IDLE) {

		if (h2s->st != H2_SS_CLOSED) {
			if (!h2c_decode_headers(h2c, &h2s->rxbuf, &h2s->flags))
				goto out;
			goto done;
		}
		error = H2_ERR_PROTOCOL_ERROR;
		sess_log(h2c->conn->owner);
		goto conn_err;
	}
	else if (h2c->dsi <= h2c->max_id || !(h2c->dsi & 1)) {

		error = H2_ERR_PROTOCOL_ERROR;
		sess_log(h2c->conn->owner);
		goto conn_err;
	}
	else if (h2c->flags & H2_CF_DEM_TOOMANY)
		goto out;

	error = h2c_decode_headers(h2c, &rxbuf, &flags);


	if (h2c->st0 >= H2_CS_ERROR)
		goto out;

	if (error <= 0) {
		if (error == 0)
			goto out;


		h2s = (struct h2s*)h2_error_stream;
		goto send_rst;
	}


	h2s = h2c_frt_stream_new(h2c, h2c->dsi);
	if (!h2s) {
		h2s = (struct h2s*)h2_refused_stream;
		goto send_rst;
	}

	h2s->st = H2_SS_OPEN;
	h2s->rxbuf = rxbuf;
	h2s->flags |= flags;

 done:
	if (h2c->dff & H2_F_HEADERS_END_STREAM)
		h2s->flags |= H2_SF_ES_RCVD;

	if (h2s->flags & H2_SF_ES_RCVD) {
		h2s->st = H2_SS_HREM;
		h2s->cs->flags |= CS_FL_REOS;
	}


	if (h2s->id > h2c->max_id)
		h2c->max_id = h2s->id;

	return h2s;

 conn_err:
	h2c_error(h2c, error);
	goto out;

 out:
	h2_release_buf(h2c, &rxbuf);
	return NULL;

 send_rst:


	h2_release_buf(h2c, &rxbuf);
	h2c->st0 = H2_CS_FRAME_E;
	return h2s;
}
