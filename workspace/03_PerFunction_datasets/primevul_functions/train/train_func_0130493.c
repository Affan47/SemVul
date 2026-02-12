static int h2c_frt_handle_data(struct h2c *h2c, struct h2s *h2s)
{
	int error;


	if (!b_size(&h2c->dbuf) && h2c->dfl)
		return 0;

	if (b_data(&h2c->dbuf) < h2c->dfl && !b_full(&h2c->dbuf))
		return 0;


	if (!h2c->dsi) {

		error = H2_ERR_PROTOCOL_ERROR;
		goto conn_err;
	}

	if (h2s->st != H2_SS_OPEN && h2s->st != H2_SS_HLOC) {

		error = H2_ERR_STREAM_CLOSED;
		goto strm_err;
	}

	if (!h2_frt_transfer_data(h2s))
		return 0;


	if (!h2s->cs) {
		error = H2_ERR_STREAM_CLOSED;
		goto strm_err;
	}

	if (h2c->st0 >= H2_CS_ERROR)
		return 0;

	if (h2s->st >= H2_SS_ERROR) {

		h2c->st0 = H2_CS_FRAME_E;
	}


	if (h2c->st0 == H2_CS_FRAME_P)
		return 0;


	if (h2c->dff & H2_F_DATA_END_STREAM) {
		h2s->st = H2_SS_HREM;
		h2s->flags |= H2_SF_ES_RCVD;
		h2s->cs->flags |= CS_FL_REOS;
	}

	return 1;

 conn_err:
	h2c_error(h2c, error);
	return 0;

 strm_err:
	if (h2s) {
		h2s_error(h2s, error);
		h2c->st0 = H2_CS_FRAME_E;
	}
	else
		h2c_error(h2c, error);
	return 0;
}
