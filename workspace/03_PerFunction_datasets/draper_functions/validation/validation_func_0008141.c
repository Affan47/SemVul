hscx_fill_fifo(struct hscx_hw *hscx)
{
	int count, more;
	u8 *p;

	if (!hscx->bch.tx_skb) {
		if (!test_bit(FLG_TX_EMPTY, &hscx->bch.Flags))
			return;
		count = hscx->fifo_size;
		more = 1;
		p = hscx->log;
		memset(p, hscx->bch.fill[0], count);
	} else {
		count = hscx->bch.tx_skb->len - hscx->bch.tx_idx;
		if (count <= 0)
			return;
		p = hscx->bch.tx_skb->data + hscx->bch.tx_idx;

		more = test_bit(FLG_TRANSPARENT, &hscx->bch.Flags) ? 1 : 0;
		if (count > hscx->fifo_size) {
			count = hscx->fifo_size;
			more = 1;
		}
		pr_debug("%s: B%1d %d/%d/%d\n", hscx->ip->name, hscx->bch.nr,
			 count, hscx->bch.tx_idx, hscx->bch.tx_skb->len);
		hscx->bch.tx_idx += count;
	}
	if (hscx->ip->type & IPAC_TYPE_IPACX)
		hscx->ip->write_fifo(hscx->ip->hw,
				     hscx->off + IPACX_XFIFOB, p, count);
	else {
		waitforXFW(hscx);
		hscx->ip->write_fifo(hscx->ip->hw,
				     hscx->off, p, count);
	}
	hscx_cmdr(hscx, more ? 0x08 : 0x0a);

	if (hscx->bch.tx_skb && (hscx->bch.debug & DEBUG_HW_BFIFO)) {
		snprintf(hscx->log, 64, "B%1d-send %s %d ",
			 hscx->bch.nr, hscx->ip->name, count);
		print_hex_dump_bytes(hscx->log, DUMP_PREFIX_OFFSET, p, count);
	}
}
