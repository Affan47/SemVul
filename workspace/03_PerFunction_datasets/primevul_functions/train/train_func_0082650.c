static int h2c_decode_headers(struct h2c *h2c, struct buffer *rxbuf, uint32_t *flags)
{
	const uint8_t *hdrs = (uint8_t *)b_head(&h2c->dbuf);
	struct buffer *tmp = get_trash_chunk();
	struct http_hdr list[MAX_HTTP_HDR * 2];
	struct buffer *copy = NULL;
	unsigned int msgf;
	struct htx *htx = NULL;
	int flen;
	int hole = 0;
	int ret = 0;
	int outlen;
	int wrap;
	int try = 0;

next_frame:
	if (b_data(&h2c->dbuf) - hole < h2c->dfl)
		goto leave;


	if (unlikely(!(h2c->dff & H2_F_HEADERS_END_HEADERS))) {
		struct h2_fh hdr;
		int clen;

		if (!h2_peek_frame_hdr(&h2c->dbuf, h2c->dfl + hole, &hdr)) {


			goto leave;
		}

		if (hdr.ft != H2_FT_CONTINUATION) {

			h2c_error(h2c, H2_ERR_PROTOCOL_ERROR);
			goto fail;
		}

		if (hdr.sid != h2c->dsi) {

			h2c_error(h2c, H2_ERR_PROTOCOL_ERROR);
			goto fail;
		}

		if ((unsigned)hdr.len > (unsigned)global.tune.bufsize) {

			h2c_error(h2c, H2_ERR_FRAME_SIZE_ERROR);
			goto fail;
		}


		h2c->dff |= hdr.ff & H2_F_HEADERS_END_HEADERS;


		clen = b_data(&h2c->dbuf) - (h2c->dfl + hole + 9);
		if (clen > hdr.len)
			clen = hdr.len;


		b_move(&h2c->dbuf, b_peek_ofs(&h2c->dbuf, h2c->dfl + hole + 9), clen, -(h2c->dpl + hole + 9));
		h2c->dfl += clen - h2c->dpl;
		hole     += h2c->dpl + 9;
		h2c->dpl  = 0;
		goto next_frame;
	}

	flen = h2c->dfl - h2c->dpl;


	wrap = b_wrap(&h2c->dbuf) - b_head(&h2c->dbuf);
	if (wrap < h2c->dfl) {
		copy = alloc_trash_chunk();
		if (!copy) {
			h2c_error(h2c, H2_ERR_INTERNAL_ERROR);
			goto fail;
		}
		memcpy(copy->area, b_head(&h2c->dbuf), wrap);
		memcpy(copy->area + wrap, b_orig(&h2c->dbuf), h2c->dfl - wrap);
		hdrs = (uint8_t *) copy->area;
	}


	if (h2c->dff & H2_F_HEADERS_PRIORITY) {
		if (read_n32(hdrs) == h2c->dsi) {

			h2c_error(h2c, H2_ERR_PROTOCOL_ERROR);
			goto fail;
		}

		hdrs += 5;
		flen -= 5;
	}

	if (!h2_get_buf(h2c, rxbuf)) {
		h2c->flags |= H2_CF_DEM_SALLOC;
		goto leave;
	}


	if (h2c->proxy->options2 & PR_O2_USE_HTX) {
		htx = htx_from_buf(rxbuf);
		if (!htx_is_empty(htx)) {
			h2c->flags |= H2_CF_DEM_SFULL;
			goto leave;
		}
	} else {
		if (b_data(rxbuf)) {
			h2c->flags |= H2_CF_DEM_SFULL;
			goto leave;
		}

		rxbuf->head = 0;
		try = b_size(rxbuf);
	}


	outlen = hpack_decode_frame(h2c->ddht, hdrs, flen, list,
	                            sizeof(list)/sizeof(list[0]), tmp);
	if (outlen < 0) {
		h2c_error(h2c, H2_ERR_COMPRESSION_ERROR);
		goto fail;
	}


	b_del(&h2c->dbuf, h2c->dfl + hole);
	h2c->dfl = hole = 0;
	h2c->st0 = H2_CS_FRAME_H;


	msgf = (h2c->dff & H2_F_HEADERS_END_STREAM) ? 0 : H2_MSGF_BODY;

	if (*flags & H2_SF_HEADERS_RCVD)
		goto trailers;


	if (htx) {

		if (h2c->flags & H2_CF_IS_BACK)
			outlen = h2_make_htx_response(list, htx, &msgf);
		else
			outlen = h2_make_htx_request(list, htx, &msgf);
	} else {

		outlen = h2_make_h1_request(list, b_tail(rxbuf), try, &msgf);
		if (outlen > 0)
			b_add(rxbuf, outlen);
	}

	if (outlen < 0) {

		goto fail;
	}

	if (msgf & H2_MSGF_BODY) {

		if (msgf & H2_MSGF_BODY_CL)
			*flags |= H2_SF_DATA_CLEN;
		else if (!(msgf & H2_MSGF_BODY_TUNNEL) && !htx)
			*flags |= H2_SF_DATA_CHNK;
	}

 done:

	*flags |= H2_SF_HEADERS_RCVD;

	if (h2c->dff & H2_F_HEADERS_END_STREAM) {


		if (htx) {
			if (!htx_add_endof(htx, HTX_BLK_EOM))
				goto fail;
		}
		else if (*flags & H2_SF_DATA_CHNK) {
			if (!b_putblk(rxbuf, "\r\n", 2))
				goto fail;
		}
	}


	ret = 1;

 leave:


	if (hole) {
		if (b_data(&h2c->dbuf) > h2c->dfl + hole)
			b_move(&h2c->dbuf, b_peek_ofs(&h2c->dbuf, h2c->dfl + hole),
			       b_data(&h2c->dbuf) - (h2c->dfl + hole), -hole);
		b_sub(&h2c->dbuf, hole);
	}

	if (b_full(&h2c->dbuf) && h2c->dfl > b_data(&h2c->dbuf)) {

		h2c_error(h2c, H2_ERR_INTERNAL_ERROR);
		ret = -1;
	}

	if (htx)
		htx_to_buf(htx, rxbuf);
	free_trash_chunk(copy);
	return ret;

 fail:
	ret = -1;
	goto leave;

 trailers:


	if (!(h2c->dff & H2_F_HEADERS_END_STREAM)) {

		h2c_error(h2c, H2_ERR_PROTOCOL_ERROR);
		goto fail;
	}


	if (htx) {
		if (!htx_add_endof(htx, HTX_BLK_EOD))
			goto fail;
		if (h2_make_htx_trailers(list, htx) <= 0)
			goto fail;
	}
	else if (*flags & H2_SF_DATA_CHNK) {


		if (!b_putblk(rxbuf, "0\r\n", 3))
			goto fail;

		outlen = h2_make_h1_trailers(list, b_tail(rxbuf), try);
		if (outlen > 0)
			b_add(rxbuf, outlen);
		else
			goto fail;
	}

	goto done;
}
