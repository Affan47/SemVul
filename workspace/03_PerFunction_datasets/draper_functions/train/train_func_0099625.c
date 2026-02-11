send_tiger_bc(struct tiger_hw *card, struct tiger_ch *bc)
{
	int ret;

	bc->free += card->send.size / 2;
	if (bc->free >= card->send.size) {
		if (!(bc->txstate & (TX_UNDERRUN | TX_INIT))) {
			pr_info("%s: B%1d TX underrun state %x\n", card->name,
				bc->bch.nr, bc->txstate);
			bc->txstate |= TX_UNDERRUN;
		}
		bc->free = card->send.size;
	}
	ret = bc_next_frame(bc);
	if (!ret) {
		if (test_bit(FLG_HDLC, &bc->bch.Flags)) {
			fill_hdlc_flag(bc);
			return;
		}
		pr_debug("%s: B%1d TX no data free %d idx %d/%d\n", card->name,
			 bc->bch.nr, bc->free, bc->idx, card->send.idx);
		if (!(bc->txstate & (TX_IDLE | TX_INIT))) {
			fill_mem(bc, bc->idx, bc->free, 0xff);
			if (bc->free == card->send.size)
				bc->txstate |= TX_IDLE;
		}
	}
}
