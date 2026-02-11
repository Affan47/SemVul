he_init_tx_lbfp(struct he_dev *he_dev)
{
	unsigned i, lbm_offset, lbufd_index, lbuf_addr, lbuf_count;
	unsigned lbufs_per_row = he_dev->cells_per_row / he_dev->cells_per_lbuf;
	unsigned lbuf_bufsize = he_dev->cells_per_lbuf * ATM_CELL_PAYLOAD;
	unsigned row_offset = he_dev->tx_startrow * he_dev->bytes_per_row;

	lbufd_index = he_dev->r0_numbuffs + he_dev->r1_numbuffs;
	lbm_offset = he_readl(he_dev, RCMLBM_BA) + (2 * lbufd_index);

	he_writel(he_dev, lbufd_index, TLBF_H);

	for (i = 0, lbuf_count = 0; i < he_dev->tx_numbuffs; ++i) {
		lbufd_index += 1;
		lbuf_addr = (row_offset + (lbuf_count * lbuf_bufsize)) / 32;

		he_writel_rcm(he_dev, lbuf_addr, lbm_offset);
		he_writel_rcm(he_dev, lbufd_index, lbm_offset + 1);

		if (++lbuf_count == lbufs_per_row) {
			lbuf_count = 0;
			row_offset += he_dev->bytes_per_row;
		}
		lbm_offset += 2;
	}

	he_writel(he_dev, lbufd_index - 1, TLBF_T);
}
