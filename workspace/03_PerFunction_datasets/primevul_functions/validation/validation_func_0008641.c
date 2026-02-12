static struct htx_sl *h2_prepare_htx_reqline(uint32_t fields, struct ist *phdr, struct htx *htx, unsigned int *msgf)
{
	struct ist uri, meth_sl;
	unsigned int flags = HTX_SL_F_NONE;
	struct htx_sl *sl;
	size_t i;

	if ((fields & H2_PHDR_FND_METH) && isteq(phdr[H2_PHDR_IDX_METH], ist("CONNECT"))) {
		if (fields & H2_PHDR_FND_PROT) {


			if (!(fields & H2_PHDR_FND_SCHM)) {

				goto fail;
			}
			else if (!(fields & H2_PHDR_FND_PATH)) {

				goto fail;
			}
			else if (!(fields & H2_PHDR_FND_AUTH)) {

				goto fail;
			}

			flags |= HTX_SL_F_HAS_SCHM;
			if (isteqi(phdr[H2_PHDR_IDX_SCHM], ist("http")))
				flags |= HTX_SL_F_SCHM_HTTP;
			else if (isteqi(phdr[H2_PHDR_IDX_SCHM], ist("https")))
				flags |= HTX_SL_F_SCHM_HTTPS;
			else if (!http_validate_scheme(phdr[H2_PHDR_IDX_SCHM]))
				htx->flags |= HTX_FL_PARSING_ERROR;

			meth_sl = ist("GET");

			*msgf |= H2_MSGF_EXT_CONNECT;


			*msgf &= ~H2_MSGF_BODY;
		}
		else {


			if (fields & H2_PHDR_FND_SCHM) {

				goto fail;
			}
			else if (fields & H2_PHDR_FND_PATH) {

				goto fail;
			}
			else if (!(fields & H2_PHDR_FND_AUTH)) {

				goto fail;
			}

			meth_sl = phdr[H2_PHDR_IDX_METH];
		}

		*msgf |= H2_MSGF_BODY_TUNNEL;
	}
	else if ((fields & (H2_PHDR_FND_METH|H2_PHDR_FND_SCHM|H2_PHDR_FND_PATH)) !=
	         (H2_PHDR_FND_METH|H2_PHDR_FND_SCHM|H2_PHDR_FND_PATH)) {


		if (!(fields & H2_PHDR_FND_METH)) {

			goto fail;
		}
		else if (!(fields & H2_PHDR_FND_SCHM)) {

			goto fail;
		}
		else {

			goto fail;
		}
	}
	else {


		flags |= HTX_SL_F_HAS_SCHM;
		if (isteqi(phdr[H2_PHDR_IDX_SCHM], ist("http")))
			flags |= HTX_SL_F_SCHM_HTTP;
		else if (isteqi(phdr[H2_PHDR_IDX_SCHM], ist("https")))
			flags |= HTX_SL_F_SCHM_HTTPS;
		else if (!http_validate_scheme(phdr[H2_PHDR_IDX_SCHM]))
			htx->flags |= HTX_FL_PARSING_ERROR;

		meth_sl = phdr[H2_PHDR_IDX_METH];
	}

	if (fields & H2_PHDR_FND_PATH) {


		if (unlikely(!phdr[H2_PHDR_IDX_PATH].len))
			goto fail;
		else if (unlikely(phdr[H2_PHDR_IDX_PATH].ptr[0] != '/')) {
			if (!isteq(phdr[H2_PHDR_IDX_PATH], ist("*")))
				goto fail;
		}
		else if (phdr[H2_PHDR_IDX_PATH].len > 1 &&
			 phdr[H2_PHDR_IDX_PATH].ptr[1] == '/')
			goto fail;
	}

	if (!(flags & HTX_SL_F_HAS_SCHM)) {

		uri = phdr[H2_PHDR_IDX_AUTH];
		flags |= HTX_SL_F_HAS_AUTHORITY;
	}
	else if (fields & H2_PHDR_FND_AUTH) {


		uri = ist2bin(trash.area, phdr[H2_PHDR_IDX_SCHM]);
		istcat(&uri, ist("://"), trash.size);
		istcat(&uri, phdr[H2_PHDR_IDX_AUTH], trash.size);
		if (!isteq(phdr[H2_PHDR_IDX_PATH], ist("*")))
			istcat(&uri, phdr[H2_PHDR_IDX_PATH], trash.size);
		flags |= HTX_SL_F_HAS_AUTHORITY;

		if (flags & (HTX_SL_F_SCHM_HTTP|HTX_SL_F_SCHM_HTTPS)) {


			flags |= HTX_SL_F_NORMALIZED_URI;
		}
	}
	else {

		uri = phdr[H2_PHDR_IDX_PATH];
		if (fields & H2_PHDR_FND_AUTH)
			flags |= HTX_SL_F_HAS_AUTHORITY;
	}


	if (!meth_sl.len)
		goto fail;
	for (i = 0; i < meth_sl.len; i++) {
		if (!HTTP_IS_TOKEN(meth_sl.ptr[i]))
			htx->flags |= HTX_FL_PARSING_ERROR;
	}


	if (!uri.len)
		goto fail;


	for (i = 0; i < uri.len; i++) {
		unsigned char c = uri.ptr[i];
		if (HTTP_IS_LWS(c) || HTTP_IS_CTL(c))
			htx->flags |= HTX_FL_PARSING_ERROR;
	}


	flags |= HTX_SL_F_VER_11;
	flags |= HTX_SL_F_XFER_LEN;

	sl = htx_add_stline(htx, HTX_BLK_REQ_SL, flags, meth_sl, uri, ist("HTTP/2.0"));
	if (!sl)
		goto fail;

	sl->info.req.meth = find_http_meth(meth_sl.ptr, meth_sl.len);
	if (sl->info.req.meth == HTTP_METH_HEAD)
		*msgf |= H2_MSGF_BODYLESS_RSP;
	return sl;
 fail:
	return NULL;
}
