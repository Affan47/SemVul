static struct htx_sl *h2_prepare_htx_stsline(uint32_t fields, struct ist *phdr, struct htx *htx, unsigned int *msgf)
{
	unsigned int status, flags = HTX_SL_F_NONE;
	struct htx_sl *sl;
	struct ist stat;


	if (!(fields & H2_PHDR_FND_STAT))
		goto fail;

	if (phdr[H2_PHDR_IDX_STAT].len != 3)
		goto fail;


	if (unlikely(*msgf & H2_MSGF_EXT_CONNECT) &&
	    isteq(phdr[H2_PHDR_IDX_STAT], ist("200"))) {
		stat = ist("101");
		status = 101;
	}
	else {
		unsigned char h, t, u;

		stat = phdr[H2_PHDR_IDX_STAT];

		h = stat.ptr[0] - '0';
		t = stat.ptr[1] - '0';
		u = stat.ptr[2] - '0';
		if (h > 9 || t > 9 || u > 9)
			goto fail;
		status = h * 100 + t * 10 + u;
	}


	if (status == 101) {
		if (!(*msgf & H2_MSGF_EXT_CONNECT))
			goto fail;
	}
	else if (status < 200) {
		*msgf |= H2_MSGF_RSP_1XX;
		*msgf &= ~H2_MSGF_BODY;
	}
	else if (status == 204 || status == 304) {
		*msgf &= ~H2_MSGF_BODY;
		*msgf |= H2_MSGF_BODYLESS_RSP;
	}


	flags |= HTX_SL_F_VER_11;
	flags |= HTX_SL_F_XFER_LEN;

	sl = htx_add_stline(htx, HTX_BLK_RES_SL, flags, ist("HTTP/2.0"), stat, ist(""));
	if (!sl)
		goto fail;
	sl->info.res.status = status;
	return sl;
 fail:
	return NULL;
}
