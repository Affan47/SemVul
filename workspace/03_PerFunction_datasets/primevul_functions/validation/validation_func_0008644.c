int h2_make_htx_response(struct http_hdr *list, struct htx *htx, unsigned int *msgf, unsigned long long *body_len, char *upgrade_protocol)
{
	struct ist phdr_val[H2_PHDR_NUM_ENTRIES];
	uint32_t fields;
	uint32_t idx;
	int phdr;
	int ret;
	int i;
	struct htx_sl *sl = NULL;
	unsigned int sl_flags = 0;
	const char *ctl;

	fields = 0;
	for (idx = 0; list[idx].n.len != 0; idx++) {
		if (!list[idx].n.ptr) {

			phdr = list[idx].n.len;
		}
		else {


			phdr = h2_str_to_phdr(list[idx].n);

			for (i = !!phdr; i < list[idx].n.len; i++)
				if ((uint8_t)(list[idx].n.ptr[i] - 'A') < 'Z' - 'A' || !HTTP_IS_TOKEN(list[idx].n.ptr[i]))
					goto fail;
		}


		ctl = ist_find_ctl(list[idx].v);
		if (unlikely(ctl) && has_forbidden_char(list[idx].v, ctl))
			goto fail;

		if (phdr > 0 && phdr < H2_PHDR_NUM_ENTRIES) {

			if (fields & ((1 << phdr) | H2_PHDR_FND_NONE)) {
				if (fields & H2_PHDR_FND_NONE) {

					goto fail;
				}
				else {

					goto fail;
				}
			}
			fields |= 1 << phdr;
			phdr_val[phdr] = list[idx].v;
			continue;
		}
		else if (phdr != 0) {

			goto fail;
		}


		if (!(fields & H2_PHDR_FND_NONE)) {

			sl = h2_prepare_htx_stsline(fields, phdr_val, htx, msgf);
			if (!sl)
				goto fail;
			fields |= H2_PHDR_FND_NONE;
		}

		if (isteq(list[idx].n, ist("content-length"))) {
			ret = h2_parse_cont_len_header(msgf, &list[idx].v, body_len);
			if (ret < 0)
				goto fail;

			sl_flags |= HTX_SL_F_CLEN;
			if (ret == 0)
				continue;
		}


		if (isteq(list[idx].n, ist("connection")) ||
		    isteq(list[idx].n, ist("proxy-connection")) ||
		    isteq(list[idx].n, ist("keep-alive")) ||
		    isteq(list[idx].n, ist("upgrade")) ||
		    isteq(list[idx].n, ist("transfer-encoding")))
			goto fail;

		if (!htx_add_header(htx, list[idx].n, list[idx].v))
			goto fail;
	}


	if (fields & (H2_PHDR_FND_AUTH|H2_PHDR_FND_METH|H2_PHDR_FND_PATH|H2_PHDR_FND_SCHM))
		goto fail;


	if (!(fields & H2_PHDR_FND_NONE)) {
		sl = h2_prepare_htx_stsline(fields, phdr_val, htx, msgf);
		if (!sl)
			goto fail;
	}

	if (sl->info.res.status == 101 && upgrade_protocol) {
		if (!htx_add_header(htx, ist("connection"), ist("upgrade")))
			goto fail;
		if (!htx_add_header(htx, ist("upgrade"), ist(upgrade_protocol)))
			goto fail;
		sl_flags |= HTX_SL_F_CONN_UPG;
	}

	if ((*msgf & H2_MSGF_BODY_TUNNEL) &&
	    ((sl->info.res.status >= 200 && sl->info.res.status < 300) || sl->info.res.status == 101))
		*msgf &= ~(H2_MSGF_BODY|H2_MSGF_BODY_CL);
	else
		*msgf &= ~H2_MSGF_BODY_TUNNEL;

	if (!(*msgf & H2_MSGF_BODY) || ((*msgf & H2_MSGF_BODY_CL) && *body_len == 0) ||
	    (*msgf & H2_MSGF_BODY_TUNNEL)) {

		sl_flags |= HTX_SL_F_BODYLESS;
		htx->flags |= HTX_FL_EOM;
	}


	sl->flags |= sl_flags;

	if ((*msgf & (H2_MSGF_BODY|H2_MSGF_BODY_TUNNEL|H2_MSGF_BODY_CL)) == H2_MSGF_BODY) {


	}


	if (!htx_add_endof(htx, HTX_BLK_EOH))
		goto fail;

	ret = 1;
	return ret;

 fail:
	return -1;
}
