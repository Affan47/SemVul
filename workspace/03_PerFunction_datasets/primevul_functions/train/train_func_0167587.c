int http_process_req_common(struct session *s, struct buffer *req, int an_bit, struct proxy *px)
{
	struct http_txn *txn = &s->txn;
	struct http_msg *msg = &txn->req;
	struct acl_cond *cond;
	struct req_acl_rule *req_acl, *req_acl_final = NULL;
	struct redirect_rule *rule;
	struct cond_wordlist *wl;
	int do_stats;

	if (unlikely(msg->msg_state < HTTP_MSG_BODY)) {

		buffer_dont_connect(req);
		return 0;
	}

	req->analysers &= ~an_bit;
	req->analyse_exp = TICK_ETERNITY;

	DPRINTF(stderr,"[%u] %s: session=%p b=%p, exp(r,w)=%u,%u bf=%08x bl=%d analysers=%02x\n",
		now_ms, __FUNCTION__,
		s,
		req,
		req->rex, req->wex,
		req->flags,
		req->l,
		req->analysers);


	list_for_each_entry(cond, &px->block_cond, list) {
		int ret = acl_exec_cond(cond, px, s, txn, ACL_DIR_REQ);

		ret = acl_pass(ret);
		if (cond->pol == ACL_COND_UNLESS)
			ret = !ret;

		if (ret) {
			txn->status = 403;

			s->logs.tv_request = now;
			stream_int_retnclose(req->prod, error_message(s, HTTP_ERR_403));
			goto return_prx_cond;
		}
	}

	do_stats = stats_check_uri(s, px);

	list_for_each_entry(req_acl, (do_stats?&px->uri_auth->req_acl:&px->req_acl), list) {
		int ret = 1;

		if (req_acl->action >= PR_REQ_ACL_ACT_MAX)
			continue;


		if (req_acl->cond) {
			ret = acl_exec_cond(req_acl->cond, px, s, txn, ACL_DIR_REQ);
			ret = acl_pass(ret);

			if (req_acl->cond->pol == ACL_COND_UNLESS)
				ret = !ret;
		}

		if (ret) {
			req_acl_final = req_acl;
			break;
		}
	}

	if (req_acl_final && req_acl_final->action == PR_REQ_ACL_ACT_DENY) {
			txn->status = 403;
			s->logs.tv_request = now;
			stream_int_retnclose(req->prod, error_message(s, HTTP_ERR_403));
			goto return_prx_cond;
	}


	if (px->req_exp != NULL) {
		if (apply_filters_to_request(s, req, px) < 0)
			goto return_bad_req;


		if (txn->flags & TX_CLDENY) {

			txn->status = 403;

			s->logs.tv_request = now;
			stream_int_retnclose(req->prod, error_message(s, HTTP_ERR_403));
			goto return_prx_cond;
		}


		if (txn->flags & TX_CLTARPIT) {
			buffer_erase(s->req);


			buffer_dont_connect(req);
			req->analysers = 0;
			req->analysers |= AN_REQ_HTTP_TARPIT;
			req->analyse_exp = tick_add_ifset(now_ms,  s->be->timeout.tarpit);
			if (!req->analyse_exp)
				req->analyse_exp = tick_add(now_ms, 0);
			return 1;
		}
	}


	if ((!(txn->flags & TX_HDR_CONN_PRS) &&
	     (s->fe->options & (PR_O_KEEPALIVE|PR_O_SERVER_CLO|PR_O_HTTP_CLOSE|PR_O_FORCE_CLO))) ||
	    ((s->fe->options & (PR_O_KEEPALIVE|PR_O_SERVER_CLO|PR_O_HTTP_CLOSE|PR_O_FORCE_CLO)) !=
	     (s->be->options & (PR_O_KEEPALIVE|PR_O_SERVER_CLO|PR_O_HTTP_CLOSE|PR_O_FORCE_CLO)))) {
		int tmp = TX_CON_WANT_TUN;

		if ((s->fe->options|s->be->options) & PR_O_KEEPALIVE ||
		    ((s->fe->options2|s->be->options2) & PR_O2_FAKE_KA))
			tmp = TX_CON_WANT_KAL;
		if ((s->fe->options|s->be->options) & PR_O_SERVER_CLO)
			tmp = TX_CON_WANT_SCL;
		if ((s->fe->options|s->be->options) & PR_O_FORCE_CLO)
			tmp = TX_CON_WANT_CLO;

		if ((txn->flags & TX_CON_WANT_MSK) < tmp)
			txn->flags = (txn->flags & ~TX_CON_WANT_MSK) | tmp;

		if (!(txn->flags & TX_HDR_CONN_PRS)) {

			int to_del = 0;
			if ((txn->flags & TX_REQ_VER_11) ||
			    ((txn->flags & TX_CON_WANT_MSK) >= TX_CON_WANT_SCL &&
			     !((s->fe->options2|s->be->options2) & PR_O2_FAKE_KA)))
				to_del |= 2;
			if (!(txn->flags & TX_REQ_VER_11))
				to_del |= 1;
			http_parse_connection_header(txn, msg, req, to_del);
		}


		if (((txn->flags & TX_CON_WANT_MSK) == TX_CON_WANT_KAL ||
		     (txn->flags & TX_CON_WANT_MSK) == TX_CON_WANT_SCL) &&
		    ((txn->flags & TX_HDR_CONN_CLO) ||
		     (txn->flags & (TX_REQ_VER_11|TX_HDR_CONN_KAL)) == 0 ||
		     ((s->fe->options|s->be->options) & PR_O_HTTP_CLOSE) ||
		     !(txn->flags & TX_REQ_XFER_LEN) ||
		     s->fe->state == PR_STSTOPPED))
		    txn->flags = (txn->flags & ~TX_CON_WANT_MSK) | TX_CON_WANT_CLO;
	}


	list_for_each_entry(wl, &px->req_add, list) {
		if (wl->cond) {
			int ret = acl_exec_cond(wl->cond, px, s, txn, ACL_DIR_REQ);
			ret = acl_pass(ret);
			if (((struct acl_cond *)wl->cond)->pol == ACL_COND_UNLESS)
				ret = !ret;
			if (!ret)
				continue;
		}

		if (unlikely(http_header_add_tail(req, &txn->req, &txn->hdr_idx, wl->s) < 0))
			goto return_bad_req;
	}

	if (req_acl_final && req_acl_final->action == PR_REQ_ACL_ACT_HTTP_AUTH) {
		struct chunk msg;
		char *realm = req_acl_final->http_auth.realm;

		if (!realm)
			realm = do_stats?STATS_DEFAULT_REALM:px->id;

		sprintf(trash, (txn->flags & TX_USE_PX_CONN) ? HTTP_407_fmt : HTTP_401_fmt, realm);
		chunk_initlen(&msg, trash, trashlen, strlen(trash));
		txn->status = 401;
		stream_int_retnclose(req->prod, &msg);
		goto return_prx_cond;
	}

	if (do_stats) {
		struct stats_admin_rule *stats_admin_rule;


		list_for_each_entry(stats_admin_rule, &s->be->uri_auth->admin_rules, list) {
			int ret = 1;

			if (stats_admin_rule->cond) {
				ret = acl_exec_cond(stats_admin_rule->cond, s->be, s, &s->txn, ACL_DIR_REQ);
				ret = acl_pass(ret);
				if (stats_admin_rule->cond->pol == ACL_COND_UNLESS)
					ret = !ret;
			}

			if (ret) {

				s->data_ctx.stats.flags |= STAT_ADMIN;
				break;
			}
		}


		if (txn->meth == HTTP_METH_POST) {
			if (s->data_ctx.stats.flags & STAT_ADMIN) {
				if (msg->msg_state < HTTP_MSG_100_SENT) {


					if (txn->flags & TX_REQ_VER_11) {
						struct hdr_ctx ctx;
						ctx.idx = 0;

						if (http_find_header2("Expect", 6, msg->sol, &txn->hdr_idx, &ctx) &&
						    unlikely(ctx.vlen == 12 && strncasecmp(ctx.line+ctx.val, "100-continue", 12) == 0)) {
							buffer_write(s->rep, http_100_chunk.str, http_100_chunk.len);
						}
					}
					msg->msg_state = HTTP_MSG_100_SENT;
					s->logs.tv_request = now;
				}
				if (!http_process_req_stat_post(s, req)) {

					req->analysers |= an_bit;
					buffer_dont_connect(req);
					return 0;
				}
			} else {
				s->data_ctx.stats.st_code = STAT_STATUS_DENY;
			}
		}

		s->logs.tv_request = now;
		s->data_source = DATA_SRC_STATS;
		s->data_state  = DATA_ST_INIT;
		s->task->nice = -32;
		stream_int_register_handler(s->rep->prod, http_stats_io_handler);
		s->rep->prod->private = s;
		s->rep->prod->st0 = s->rep->prod->st1 = 0;
		req->analysers = 0;

		return 0;

	}


	list_for_each_entry(rule, &px->redirect_rules, list) {
		int ret = ACL_PAT_PASS;

		if (rule->cond) {
			ret = acl_exec_cond(rule->cond, px, s, txn, ACL_DIR_REQ);
			ret = acl_pass(ret);
			if (rule->cond->pol == ACL_COND_UNLESS)
				ret = !ret;
		}

		if (ret) {
			struct chunk rdr = { .str = trash, .size = trashlen, .len = 0 };
			const char *msg_fmt;


			switch(rule->code) {
			case 308:
				msg_fmt = HTTP_308;
				break;
			case 307:
				msg_fmt = HTTP_307;
				break;
			case 303:
				msg_fmt = HTTP_303;
				break;
			case 301:
				msg_fmt = HTTP_301;
				break;
			case 302:
			default:
				msg_fmt = HTTP_302;
				break;
			}

			if (unlikely(!chunk_strcpy(&rdr, msg_fmt)))
				goto return_bad_req;

			switch(rule->type) {
			case REDIRECT_TYPE_PREFIX: {
				const char *path;
				int pathlen;

				path = http_get_path(txn);

				if (path) {
					pathlen = txn->req.sl.rq.u_l + (txn->req.sol + txn->req.sl.rq.u) - path;
					if (rule->flags & REDIRECT_FLAG_DROP_QS) {
						int qs = 0;
						while (qs < pathlen) {
							if (path[qs] == '?') {
								pathlen = qs;
								break;
							}
							qs++;
						}
					}
				} else {
					path = "/";
					pathlen = 1;
				}

				if (rdr.len + rule->rdr_len + pathlen > rdr.size - 4)
					goto return_bad_req;


				if (rule->rdr_len != 1 || *rule->rdr_str != '/') {
					memcpy(rdr.str + rdr.len, rule->rdr_str, rule->rdr_len);
					rdr.len += rule->rdr_len;
				}


				memcpy(rdr.str + rdr.len, path, pathlen);
				rdr.len += pathlen;


				if (rdr.len && rdr.str[rdr.len - 1] != '/' &&
				    (rule->flags & REDIRECT_FLAG_APPEND_SLASH)) {
					if (rdr.len > rdr.size - 5)
						goto return_bad_req;
					rdr.str[rdr.len] = '/';
					rdr.len++;
				}

				break;
			}
			case REDIRECT_TYPE_LOCATION:
			default:
				if (rdr.len + rule->rdr_len > rdr.size - 4)
					goto return_bad_req;


				memcpy(rdr.str + rdr.len, rule->rdr_str, rule->rdr_len);
				rdr.len += rule->rdr_len;
				break;
			}

			if (rule->cookie_len) {
				memcpy(rdr.str + rdr.len, "\r\nSet-Cookie: ", 14);
				rdr.len += 14;
				memcpy(rdr.str + rdr.len, rule->cookie_str, rule->cookie_len);
				rdr.len += rule->cookie_len;
				memcpy(rdr.str + rdr.len, "\r\n", 2);
				rdr.len += 2;
			}


			txn->status = rule->code;

			s->logs.tv_request = now;

			if (rule->rdr_len >= 1 && *rule->rdr_str == '/' &&
			    (txn->flags & TX_REQ_XFER_LEN) &&
			    !(txn->flags & TX_REQ_TE_CHNK) && !txn->req.body_len &&
			    ((txn->flags & TX_CON_WANT_MSK) == TX_CON_WANT_SCL ||
			     (txn->flags & TX_CON_WANT_MSK) == TX_CON_WANT_KAL)) {

				if (!(txn->flags & TX_REQ_VER_11)) {
					if (unlikely(txn->flags & TX_USE_PX_CONN)) {
						memcpy(rdr.str + rdr.len, "\r\nProxy-Connection: keep-alive", 30);
						rdr.len += 30;
					} else {
						memcpy(rdr.str + rdr.len, "\r\nConnection: keep-alive", 24);
						rdr.len += 24;
					}
				}
				memcpy(rdr.str + rdr.len, "\r\n\r\n", 4);
				rdr.len += 4;
				buffer_write(req->prod->ob, rdr.str, rdr.len);

				buffer_ignore(req, msg->sov - msg->som);
				msg->som = msg->sov;
				req->analysers = AN_REQ_HTTP_XFER_BODY;
				s->rep->analysers = AN_RES_HTTP_XFER_BODY;
				txn->req.msg_state = HTTP_MSG_CLOSED;
				txn->rsp.msg_state = HTTP_MSG_DONE;
				if (!(s->flags & SN_ERR_MASK))
					s->flags |= SN_ERR_PRXCOND;
				if (!(s->flags & SN_FINST_MASK))
					s->flags |= SN_FINST_R;
				break;
			} else {

				if (unlikely(txn->flags & TX_USE_PX_CONN)) {
					memcpy(rdr.str + rdr.len, "\r\nProxy-Connection: close\r\n\r\n", 29);
					rdr.len += 29;
				} else {
					memcpy(rdr.str + rdr.len, "\r\nConnection: close\r\n\r\n", 23);
					rdr.len += 23;
				}
				stream_int_retnclose(req->prod, &rdr);
				goto return_prx_cond;
			}
		}
	}


	req->flags |= BF_SEND_DONTWAIT;


	return 1;

 return_bad_req:

	if (unlikely(msg->msg_state == HTTP_MSG_ERROR) || msg->err_pos >= 0) {


		http_capture_bad_message(&s->fe->invalid_req, s, req, msg, msg->msg_state, s->fe);
	}

	txn->req.msg_state = HTTP_MSG_ERROR;
	txn->status = 400;
	stream_int_retnclose(req->prod, error_message(s, HTTP_ERR_400));

	s->fe->counters.failed_req++;
	if (s->listener->counters)
		s->listener->counters->failed_req++;

 return_prx_cond:
	if (!(s->flags & SN_ERR_MASK))
		s->flags |= SN_ERR_PRXCOND;
	if (!(s->flags & SN_FINST_MASK))
		s->flags |= SN_FINST_R;

	req->analysers = 0;
	req->analyse_exp = TICK_ETERNITY;
	return 0;
}
