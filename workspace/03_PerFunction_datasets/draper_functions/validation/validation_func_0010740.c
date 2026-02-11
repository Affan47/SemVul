parseadd(aim_session_t *sess, aim_module_t *mod, aim_frame_t *rx,
	aim_modsnac_t *snac, aim_bstream_t *bs)
{
	int ret = 0;
	aim_rxcallback_t userfunc;
	char *name;
	fu16_t len, gid, bid, type;
	aim_tlvlist_t *data;

	while (aim_bstream_empty(bs)) {
		if ((len = aimbs_get16(bs)))
			name = aimbs_getstr(bs, len);
		else
			name = NULL;
		gid = aimbs_get16(bs);
		bid = aimbs_get16(bs);
		type = aimbs_get16(bs);
		if ((len = aimbs_get16(bs)))
			data = aim_readtlvchain_len(bs, len);
		else
			data = NULL;

		aim_ssi_itemlist_add(&sess->ssi.local, name, gid, bid, type,
			data);
		aim_ssi_itemlist_add(&sess->ssi.official, name, gid, bid, type,
			data);
		free(name);
		aim_freetlvchain(&data);

		if ((userfunc = aim_callhandler(sess, rx->conn, snac->family,
					snac->subtype)))
			ret = userfunc(sess, rx);

		free(name);
	}

	return ret;
}
