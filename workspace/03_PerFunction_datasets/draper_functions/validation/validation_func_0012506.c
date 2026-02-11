brcmf_proto_bcdc_hdrpull(struct brcmf_pub *drvr, bool do_fws,
			 struct sk_buff *pktbuf, struct brcmf_if **ifp)
{
	struct brcmf_proto_bcdc_header *h;
	struct brcmf_if *tmp_if;

	brcmf_dbg(BCDC, "Enter\n");


	if (pktbuf->len <= BCDC_HEADER_LEN) {
		brcmf_dbg(INFO, "rx data too short (%d <= %d)\n",
			  pktbuf->len, BCDC_HEADER_LEN);
		return -EBADE;
	}

	trace_brcmf_bcdchdr(pktbuf->data);
	h = (struct brcmf_proto_bcdc_header *)(pktbuf->data);

	tmp_if = brcmf_get_ifp(drvr, BCDC_GET_IF_IDX(h));
	if (!tmp_if) {
		brcmf_dbg(INFO, "no matching ifp found\n");
		return -EBADE;
	}
	if (((h->flags & BCDC_FLAG_VER_MASK) >> BCDC_FLAG_VER_SHIFT) !=
	    BCDC_PROTO_VER) {
		brcmf_err("%s: non-BCDC packet received, flags 0x%x\n",
			  brcmf_ifname(drvr, tmp_if->ifidx), h->flags);
		return -EBADE;
	}

	if (h->flags & BCDC_FLAG_SUM_GOOD) {
		brcmf_dbg(BCDC, "%s: BDC rcv, good checksum, flags 0x%x\n",
			  brcmf_ifname(drvr, tmp_if->ifidx), h->flags);
		pktbuf->ip_summed = CHECKSUM_UNNECESSARY;
	}

	pktbuf->priority = h->priority & BCDC_PRIORITY_MASK;

	skb_pull(pktbuf, BCDC_HEADER_LEN);
	if (do_fws)
		brcmf_fws_hdrpull(tmp_if, h->data_offset << 2, pktbuf);
	else
		skb_pull(pktbuf, h->data_offset << 2);

	if (pktbuf->len == 0)
		return -ENODATA;

	*ifp = tmp_if;
	return 0;
}
