int http_process_res_common(struct session *t, struct channel *rep, int an_bit, struct proxy *px)
{
	struct http_txn *txn = &t->txn;
	struct http_msg *msg = &txn->rsp;
	struct proxy *cur_proxy;
	struct cond_wordlist *wl;

	DPRINTF(stderr,"[%u] %s: session=%p b=%p, exp(r,w)=%u,%u bf=%08x bh=%d analysers=%02x\n",
		now_ms, __FUNCTION__,
		t,
		rep,
		rep->rex, rep->wex,
		rep->flags,
		rep->buf->i,
		rep->analysers);

	if (unlikely(msg->msg_state < HTTP_MSG_BODY))
		return 0;

	rep->analysers &= ~an_bit;
	rep->analyse_exp = TICK_ETERNITY;


	if (unlikely((txn->meth == HTTP_METH_CONNECT && txn->status == 200) ||
		     txn->status == 101)) {


		txn->flags = (txn->flags & ~TX_CON_WANT_MSK) | TX_CON_WANT_TUN;
	}
	else if ((txn->status >= 200) && !(txn->flags & TX_HDR_CONN_PRS) &&
		 ((txn->flags & TX_CON_WANT_MSK) != TX_CON_WANT_TUN ||
		  ((t->fe->options|t->be->options) & PR_O_HTTP_CLOSE))) {
		int to_del = 0;


		if (!(msg->flags & HTTP_MSGF_XFER_LEN) &&
		    (txn->flags & TX_CON_WANT_MSK) != TX_CON_WANT_TUN)
			txn->flags = (txn->flags & ~TX_CON_WANT_MSK) | TX_CON_WANT_CLO;


		if ((txn->flags & TX_CON_WANT_MSK) == TX_CON_WANT_TUN ||
		    (txn->flags & TX_CON_WANT_MSK) == TX_CON_WANT_CLO) {
			to_del |= 2;
			if (!(msg->flags & HTTP_MSGF_VER_11))
				to_del |= 1;
		}
		else {
			to_del |= 1;
			if (txn->req.flags & msg->flags & HTTP_MSGF_VER_11)
				to_del |= 2;
		}


		http_parse_connection_header(txn, msg, to_del);


		if ((txn->flags & TX_CON_WANT_MSK) == TX_CON_WANT_KAL) {
			if ((txn->flags & TX_HDR_CONN_CLO) ||
			    (!(txn->flags & TX_HDR_CONN_KAL) && !(msg->flags & HTTP_MSGF_VER_11)))
				txn->flags = (txn->flags & ~TX_CON_WANT_MSK) | TX_CON_WANT_SCL;
		}
	}

	if (1) {


		cur_proxy = t->be;
		while (1) {
			struct proxy *rule_set = cur_proxy;


			if (rule_set->rsp_exp != NULL) {
				if (apply_filters_to_response(t, rep, rule_set) < 0) {
				return_bad_resp:
					if (objt_server(t->target)) {
						objt_server(t->target)->counters.failed_resp++;
						health_adjust(objt_server(t->target), HANA_STATUS_HTTP_RSP);
					}
					t->be->be_counters.failed_resp++;
				return_srv_prx_502:
					rep->analysers = 0;
					txn->status = 502;
					rep->prod->flags |= SI_FL_NOLINGER;
					bi_erase(rep);
					stream_int_retnclose(rep->cons, http_error_message(t, HTTP_ERR_502));
					if (!(t->flags & SN_ERR_MASK))
						t->flags |= SN_ERR_PRXCOND;
					if (!(t->flags & SN_FINST_MASK))
						t->flags |= SN_FINST_H;
					return 0;
				}
			}


			if (txn->flags & TX_SVDENY) {
				if (objt_server(t->target))
					objt_server(t->target)->counters.failed_secu++;

				t->be->be_counters.denied_resp++;
				t->fe->fe_counters.denied_resp++;
				if (t->listener->counters)
					t->listener->counters->denied_resp++;

				goto return_srv_prx_502;
			}


			list_for_each_entry(wl, &rule_set->rsp_add, list) {
				if (txn->status < 200)
					break;
				if (wl->cond) {
					int ret = acl_exec_cond(wl->cond, px, t, txn, SMP_OPT_DIR_RES|SMP_OPT_FINAL);
					ret = acl_pass(ret);
					if (((struct acl_cond *)wl->cond)->pol == ACL_COND_UNLESS)
						ret = !ret;
					if (!ret)
						continue;
				}
				if (unlikely(http_header_add_tail(&txn->rsp, &txn->hdr_idx, wl->s) < 0))
					goto return_bad_resp;
			}


			if (cur_proxy == t->fe)
				break;
			cur_proxy = t->fe;
		}


		if (unlikely(txn->status == 100)) {
			hdr_idx_init(&txn->hdr_idx);
			msg->next -= channel_forward(rep, msg->next);
			msg->msg_state = HTTP_MSG_RPBEFORE;
			txn->status = 0;
			rep->analysers |= AN_RES_WAIT_HTTP | an_bit;
			return 1;
		}
		else if (unlikely(txn->status < 200))
			goto skip_header_mangling;


		if (t->be->cookie_name || t->be->appsession_name || t->fe->capture_name ||
		    (t->be->options & PR_O_CHK_CACHE))
			manage_server_side_cookies(t, rep);


		if ((t->be->options & PR_O_CHK_CACHE) || (t->be->ck_opts & PR_CK_NOC))
			check_response_for_cacheability(t, rep);


		if (objt_server(t->target) && (t->be->ck_opts & PR_CK_INS) &&
		    !((txn->flags & TX_SCK_FOUND) && (t->be->ck_opts & PR_CK_PSV)) &&
		    (!(t->flags & SN_DIRECT) ||
		     ((t->be->cookie_maxidle || txn->cookie_last_date) &&
		      (!txn->cookie_last_date || (txn->cookie_last_date - date.tv_sec) < 0)) ||
		     (t->be->cookie_maxlife && !txn->cookie_first_date) ||
		     (!t->be->cookie_maxlife && txn->cookie_first_date)) &&
		    (!(t->be->ck_opts & PR_CK_POST) || (txn->meth == HTTP_METH_POST)) &&
		    !(t->flags & SN_IGNORE_PRST)) {


			if (!objt_server(t->target)->cookie) {
				chunk_printf(&trash,
					      "Set-Cookie: %s=; Expires=Thu, 01-Jan-1970 00:00:01 GMT; path=/",
					      t->be->cookie_name);
			}
			else {
				chunk_printf(&trash, "Set-Cookie: %s=%s", t->be->cookie_name, objt_server(t->target)->cookie);

				if (t->be->cookie_maxidle || t->be->cookie_maxlife) {

					trash.str[trash.len++] = COOKIE_DELIM_DATE;
					s30tob64((date.tv_sec+3) >> 2, trash.str + trash.len);
					trash.len += 5;

					if (t->be->cookie_maxlife) {


						trash.str[trash.len++] = COOKIE_DELIM_DATE;
						s30tob64(txn->cookie_first_date ?
							 txn->cookie_first_date >> 2 :
							 (date.tv_sec+3) >> 2, trash.str + trash.len);
						trash.len += 5;
					}
				}
				chunk_appendf(&trash, "; path=/");
			}

			if (t->be->cookie_domain)
				chunk_appendf(&trash, "; domain=%s", t->be->cookie_domain);

			if (t->be->ck_opts & PR_CK_HTTPONLY)
				chunk_appendf(&trash, "; HttpOnly");

			if (t->be->ck_opts & PR_CK_SECURE)
				chunk_appendf(&trash, "; Secure");

			if (unlikely(http_header_add_tail2(&txn->rsp, &txn->hdr_idx, trash.str, trash.len) < 0))
				goto return_bad_resp;

			txn->flags &= ~TX_SCK_MASK;
			if (objt_server(t->target)->cookie && (t->flags & SN_DIRECT))

				txn->flags |= TX_SCK_UPDATED;
			else
				txn->flags |= TX_SCK_INSERTED;


			if ((t->be->ck_opts & PR_CK_NOC) && (txn->flags & TX_CACHEABLE)) {

				txn->flags &= ~TX_CACHEABLE & ~TX_CACHE_COOK;

				if (unlikely(http_header_add_tail2(&txn->rsp, &txn->hdr_idx,
								   "Cache-control: private", 22) < 0))
					goto return_bad_resp;
			}
		}


		if (((txn->flags & (TX_CACHEABLE | TX_CACHE_COOK | TX_SCK_PRESENT)) ==
		     (TX_CACHEABLE | TX_CACHE_COOK | TX_SCK_PRESENT)) &&
		    (t->be->options & PR_O_CHK_CACHE)) {


			if (objt_server(t->target))
				objt_server(t->target)->counters.failed_secu++;

			t->be->be_counters.denied_resp++;
			t->fe->fe_counters.denied_resp++;
			if (t->listener->counters)
				t->listener->counters->denied_resp++;

			Alert("Blocking cacheable cookie in response from instance %s, server %s.\n",
			      t->be->id, objt_server(t->target) ? objt_server(t->target)->id : "<dispatch>");
			send_log(t->be, LOG_ALERT,
				 "Blocking cacheable cookie in response from instance %s, server %s.\n",
				 t->be->id, objt_server(t->target) ? objt_server(t->target)->id : "<dispatch>");
			goto return_srv_prx_502;
		}


		if (!(txn->flags & TX_HDR_CONN_UPG) &&
		    (((txn->flags & TX_CON_WANT_MSK) != TX_CON_WANT_TUN) ||
		     ((t->fe->options|t->be->options) & PR_O_HTTP_CLOSE))) {
			unsigned int want_flags = 0;

			if ((txn->flags & TX_CON_WANT_MSK) == TX_CON_WANT_KAL ||
			    (txn->flags & TX_CON_WANT_MSK) == TX_CON_WANT_SCL) {


				if (!(txn->req.flags & msg->flags & HTTP_MSGF_VER_11))
					want_flags |= TX_CON_KAL_SET;
			}
			else {


				if (msg->flags & HTTP_MSGF_VER_11)
					want_flags |= TX_CON_CLO_SET;
			}

			if (want_flags != (txn->flags & (TX_CON_CLO_SET|TX_CON_KAL_SET)))
				http_change_connection_header(txn, msg, want_flags);
		}

	skip_header_mangling:
		if ((msg->flags & HTTP_MSGF_XFER_LEN) ||
		    (txn->flags & TX_CON_WANT_MSK) == TX_CON_WANT_TUN)
			rep->analysers |= AN_RES_HTTP_XFER_BODY;


		t->logs.t_data = tv_ms_elapsed(&t->logs.tv_accept, &now);


		if (!LIST_ISEMPTY(&t->fe->logformat) && !(t->logs.logwait & LW_BYTES)) {
			t->logs.t_close = t->logs.t_data;
			t->logs.bytes_out = txn->rsp.eoh;
			t->do_log(t);
			t->logs.bytes_out = 0;
		}


		return 1;
	}
	return 1;
}
