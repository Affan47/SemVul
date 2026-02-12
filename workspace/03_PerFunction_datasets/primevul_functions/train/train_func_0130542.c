static size_t h2s_htx_frt_make_resp_data(struct h2s *h2s, struct buffer *buf, size_t count)
{
	struct h2c *h2c = h2s->h2c;
	struct htx *htx;
	struct buffer outbuf;
	size_t total = 0;
	int es_now = 0;
	int bsize;
	int fsize;
	struct htx_blk *blk;
	enum htx_blk_type type;
	int idx;

	if (h2c_mux_busy(h2c, h2s)) {
		h2s->flags |= H2_SF_BLK_MBUSY;
		goto end;
	}

	if (!h2_get_buf(h2c, &h2c->mbuf)) {
		h2c->flags |= H2_CF_MUX_MALLOC;
		h2s->flags |= H2_SF_BLK_MROOM;
		goto end;
	}

	htx = htx_from_buf(buf);


 new_frame:
	if (!count || htx_is_empty(htx))
		goto end;

	idx   = htx_get_head(htx);
	blk   = htx_get_blk(htx, idx);
	type  = htx_get_blk_type(blk);
	bsize = htx_get_blksz(blk);
	fsize = bsize;

	if (type == HTX_BLK_EOD) {


		htx_remove_blk(htx, blk);
		total++;
		count--;
		goto end;
	}
	else if (type == HTX_BLK_EOM) {
		if (h2s->flags & H2_SF_ES_SENT) {

			htx_remove_blk(htx, blk);
			total++;
			count--;
			goto end;
		}
	}
	else if (type != HTX_BLK_DATA)
		goto end;


	if (unlikely(fsize == count &&
	             htx->used == 1 && type == HTX_BLK_DATA &&
	             fsize <= h2s->mws && fsize <= h2c->mws && fsize <= h2c->mfs)) {
		void *old_area = h2c->mbuf.area;

		if (b_data(&h2c->mbuf)) {


			if (fsize <= b_size(&h2c->mbuf) / 4 && fsize + 9 <= b_room(&h2c->mbuf))
				goto copy;
			h2c->flags |= H2_CF_MUX_MFULL;
			h2s->flags |= H2_SF_BLK_MROOM;
			goto end;
		}


		h2c->mbuf.area = buf->area;
		h2c->mbuf.head = sizeof(struct htx) + blk->addr - 9;
		h2c->mbuf.data = fsize + 9;
		outbuf.area    = b_head(&h2c->mbuf);


		memcpy(outbuf.area, "\x00\x00\x00\x00\x00", 5);
		write_n32(outbuf.area + 5, h2s->id);
		h2_set_frame_size(outbuf.area, fsize);


		h2s->mws -= fsize;
		h2c->mws -= fsize;


		buf->area = old_area;
		buf->data = buf->head = 0;
		total += fsize;
		goto end;
	}

 copy:


	while (1) {
		outbuf.area  = b_tail(&h2c->mbuf);
		outbuf.size = b_contig_space(&h2c->mbuf);
		outbuf.data = 0;

		if (outbuf.size >= 9 || !b_space_wraps(&h2c->mbuf))
			break;
	realign_again:
		b_slow_realign(&h2c->mbuf, trash.area, b_data(&h2c->mbuf));
	}

	if (outbuf.size < 9) {
		h2c->flags |= H2_CF_MUX_MFULL;
		h2s->flags |= H2_SF_BLK_MROOM;
		goto end;
	}


	memcpy(outbuf.area, "\x00\x00\x00\x00\x00", 5);
	write_n32(outbuf.area + 5, h2s->id);
	outbuf.data = 9;


	if (type == HTX_BLK_EOM)
		bsize = fsize = 0;

	if (!fsize)
		goto send_empty;

	if (h2s->mws <= 0) {
		h2s->flags |= H2_SF_BLK_SFCTL;
		if (h2s->send_wait) {
			LIST_DEL(&h2s->list);
			LIST_INIT(&h2s->list);
		}
		goto end;
	}

	if (fsize > count)
		fsize = count;

	if (fsize > h2s->mws)
		fsize = h2s->mws;

	if (h2c->mfs && fsize > h2c->mfs)
		fsize = h2c->mfs;

	if (fsize + 9 > outbuf.size) {


		if (b_space_wraps(&h2c->mbuf))
			goto realign_again;
		fsize = outbuf.size - 9;

		if (fsize <= 0) {

			h2c->flags |= H2_CF_MUX_MFULL;
			h2s->flags |= H2_SF_BLK_MROOM;
			goto end;
		}
	}

	if (h2c->mws <= 0) {
		h2s->flags |= H2_SF_BLK_MFCTL;
		goto end;
	}

	if (fsize > h2c->mws)
		fsize = h2c->mws;


	memcpy(outbuf.area + 9, htx_get_blk_ptr(htx, blk), fsize);
	h2s->mws -= fsize;
	h2c->mws -= fsize;
	count    -= fsize;

 send_empty:

	h2_set_frame_size(outbuf.area, fsize);


	if (type == HTX_BLK_EOM) {
		total++;
		count--;
		es_now = 1;
	}

	if (es_now)
		outbuf.area[4] |= H2_F_DATA_END_STREAM;


	b_add(&h2c->mbuf, fsize + 9);


	total += fsize;
	if (fsize == bsize) {
		htx_remove_blk(htx, blk);
		if (fsize)
			goto new_frame;
	} else {

		htx_cut_data_blk(htx, blk, fsize);
	}

	if (es_now) {
		if (h2s->st == H2_SS_OPEN)
			h2s->st = H2_SS_HLOC;
		else
			h2s_close(h2s);

		h2s->flags |= H2_SF_ES_SENT;
	}

 end:
	return total;
}
