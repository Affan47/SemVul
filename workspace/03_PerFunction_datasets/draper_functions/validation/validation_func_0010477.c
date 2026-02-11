xd_init_l2p_tbl(struct rtsx_chip *chip)
{
	struct xd_info *xd_card = &(chip->xd_card);
	int size, i;

	dev_dbg(rtsx_dev(chip), "xd_init_l2p_tbl: zone_cnt = %d\n",
		xd_card->zone_cnt);

	if (xd_card->zone_cnt < 1) {
		rtsx_trace(chip);
		return STATUS_FAIL;
	}

	size = xd_card->zone_cnt * sizeof(struct zone_entry);
	dev_dbg(rtsx_dev(chip), "Buffer size for l2p table is %d\n", size);

	xd_card->zone = vmalloc(size);
	if (!xd_card->zone) {
		rtsx_trace(chip);
		return STATUS_ERROR;
	}

	for (i = 0; i < xd_card->zone_cnt; i++) {
		xd_card->zone[i].build_flag = 0;
		xd_card->zone[i].l2p_table = NULL;
		xd_card->zone[i].free_table = NULL;
		xd_card->zone[i].get_index = 0;
		xd_card->zone[i].set_index = 0;
		xd_card->zone[i].unused_blk_cnt = 0;
	}

	return STATUS_SUCCESS;
}
