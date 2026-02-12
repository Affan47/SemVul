void http_perform_server_redirect(struct stream *s, struct stream_interface *si)
{
	struct channel *req = &s->req;
	struct channel *res = &s->res;
	struct server *srv;
	struct htx *htx;
	struct htx_sl *sl;
	struct ist path, location;
	unsigned int flags;
	struct http_uri_parser parser;


	chunk_reset(&trash);


	srv = __objt_server(s->target);
	if (srv->rdr_len != 1 || *srv->rdr_pfx != '/') {
		if (!chunk_memcat(&trash, srv->rdr_pfx, srv->rdr_len))
			return;
	}


	htx = htxbuf(&req->buf);
	sl = http_get_stline(htx);
	parser = http_uri_parser_init(htx_sl_req_uri(sl));
	path = http_parse_path(&parser);
	if (!isttest(path))
		return;

	if (!chunk_memcat(&trash, path.ptr, path.len))
		return;
	location = ist2(trash.area, trash.data);


	htx = htx_from_buf(&res->buf);
	flags = (HTX_SL_F_IS_RESP|HTX_SL_F_VER_11|HTX_SL_F_XFER_LEN|HTX_SL_F_BODYLESS);
	sl = htx_add_stline(htx, HTX_BLK_RES_SL, flags,
			    ist("HTTP/1.1"), ist("302"), ist("Found"));
	if (!sl)
		goto fail;
	sl->info.res.status = 302;
	s->txn->status = 302;

        if (!htx_add_header(htx, ist("Cache-Control"), ist("no-cache")) ||
	    !htx_add_header(htx, ist("Connection"), ist("close")) ||
	    !htx_add_header(htx, ist("Content-length"), ist("0")) ||
	    !htx_add_header(htx, ist("Location"), location))
		goto fail;

	if (!htx_add_endof(htx, HTX_BLK_EOH))
		goto fail;

	htx->flags |= HTX_FL_EOM;
	htx_to_buf(htx, &res->buf);
	if (!http_forward_proxy_resp(s, 1))
		goto fail;


	si_shutr(si);
	si_shutw(si);
	si->err_type = SI_ET_NONE;
	si->state    = SI_ST_CLO;

	if (!(s->flags & SF_ERR_MASK))
		s->flags |= SF_ERR_LOCAL;
	if (!(s->flags & SF_FINST_MASK))
		s->flags |= SF_FINST_C;


	srv_inc_sess_ctr(srv);
	srv_set_sess_last(srv);
	return;

  fail:


	channel_htx_truncate(res, htx);
}
