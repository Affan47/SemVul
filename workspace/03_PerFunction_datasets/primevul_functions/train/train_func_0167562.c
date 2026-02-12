int http_process_req_stat_post(struct session *s, struct buffer *req)
{
	struct http_txn *txn = &s->txn;
	struct proxy *px = NULL;
	struct server *sv = NULL;

	char key[LINESIZE];
	int action = ST_ADM_ACTION_NONE;
	int reprocess = 0;

	int total_servers = 0;
	int altered_servers = 0;

	char *first_param, *cur_param, *next_param, *end_params;
	char *st_cur_param = NULL;
	char *st_next_param = NULL;

	first_param = req->data + txn->req.eoh + 2;
	end_params  = first_param + txn->req.body_len;

	cur_param = next_param = end_params;

	if (end_params >= req->data + req->size - global.tune.maxrewrite) {

		s->data_ctx.stats.st_code = STAT_STATUS_EXCD;
		return 1;
	}
	else if (end_params > req->data + req->l) {

		s->data_ctx.stats.st_code = STAT_STATUS_NONE;
		return 0;
	}

	*end_params = '\0';

	s->data_ctx.stats.st_code = STAT_STATUS_NONE;


	while (cur_param > first_param) {
		char *value;
		int poffset, plen;

		cur_param--;
		if ((*cur_param == '&') || (cur_param == first_param)) {
 reprocess_servers:

			poffset = (cur_param != first_param ? 1 : 0);
			plen = next_param - cur_param + (cur_param == first_param ? 1 : 0);
			if ((plen > 0) && (plen <= sizeof(key))) {
				strncpy(key, cur_param + poffset, plen);
				key[plen - 1] = '\0';
			} else {
				s->data_ctx.stats.st_code = STAT_STATUS_EXCD;
				goto out;
			}


			value = key;
			while (*value != '\0' && *value != '=') {
				value++;
			}
			if (*value == '=') {

				*value++ = '\0';
			}

			if (!url_decode(key) || !url_decode(value))
				break;


			if (!px && (strcmp(key, "b") == 0)) {
				if ((px = findproxy(value, PR_CAP_BE)) == NULL) {

					s->data_ctx.stats.st_code = STAT_STATUS_ERRP;
					goto out;
				}
			}
			else if (!action && (strcmp(key, "action") == 0)) {
				if (strcmp(value, "disable") == 0) {
					action = ST_ADM_ACTION_DISABLE;
				}
				else if (strcmp(value, "enable") == 0) {
					action = ST_ADM_ACTION_ENABLE;
				}
				else if (strcmp(value, "stop") == 0) {
					action = ST_ADM_ACTION_STOP;
				}
				else if (strcmp(value, "start") == 0) {
					action = ST_ADM_ACTION_START;
				}
				else {
					s->data_ctx.stats.st_code = STAT_STATUS_ERRP;
					goto out;
				}
			}
			else if (strcmp(key, "s") == 0) {
				if (!(px && action)) {


					if (!reprocess) {
						st_cur_param  = cur_param;
						st_next_param = next_param;
					}
					reprocess = 1;
				}
				else if ((sv = findserver(px, value)) != NULL) {
					switch (action) {
					case ST_ADM_ACTION_DISABLE:
						if ((px->state != PR_STSTOPPED) && !(sv->state & SRV_MAINTAIN)) {

							sv->state |= SRV_MAINTAIN;
							set_server_down(sv);
							altered_servers++;
							total_servers++;
						}
						break;
					case ST_ADM_ACTION_ENABLE:
						if ((px->state != PR_STSTOPPED) && (sv->state & SRV_MAINTAIN)) {

							set_server_up(sv);
							sv->health = sv->rise;
							altered_servers++;
							total_servers++;
						}
						break;
					case ST_ADM_ACTION_STOP:
					case ST_ADM_ACTION_START:
						if (action == ST_ADM_ACTION_START)
							sv->uweight = sv->iweight;
						else
							sv->uweight = 0;

						if (px->lbprm.algo & BE_LB_PROP_DYN) {

							if ((sv->state & SRV_WARMINGUP) && (px->lbprm.algo & BE_LB_PROP_DYN))
								sv->eweight = (BE_WEIGHT_SCALE * (now.tv_sec - sv->last_change) + sv->slowstart - 1) / sv->slowstart;
							else
								sv->eweight = BE_WEIGHT_SCALE;
							sv->eweight *= sv->uweight;
						} else {
							sv->eweight = sv->uweight;
						}


						if (px->lbprm.update_server_eweight)
							px->lbprm.update_server_eweight(sv);
						else if (sv->eweight) {
							if (px->lbprm.set_server_status_up)
								px->lbprm.set_server_status_up(sv);
						}
						else {
							if (px->lbprm.set_server_status_down)
								px->lbprm.set_server_status_down(sv);
						}
						altered_servers++;
						total_servers++;
						break;
					}
				} else {

					total_servers++;
				}
			}
			if (reprocess && px && action) {


				cur_param  = st_cur_param;
				next_param = st_next_param;
				reprocess = 0;
				goto reprocess_servers;
			}

			next_param = cur_param;
		}
	}

	if (total_servers == 0) {
		s->data_ctx.stats.st_code = STAT_STATUS_NONE;
	}
	else if (altered_servers == 0) {
		s->data_ctx.stats.st_code = STAT_STATUS_ERRP;
	}
	else if (altered_servers == total_servers) {
		s->data_ctx.stats.st_code = STAT_STATUS_DONE;
	}
	else {
		s->data_ctx.stats.st_code = STAT_STATUS_PART;
	}
 out:
	return 1;
}
