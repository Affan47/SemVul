mtdswap_check_counts(struct mtdswap_dev *d)
{
	struct rb_root hist_root = RB_ROOT;
	struct rb_node *medrb;
	struct swap_eb *eb;
	unsigned int i, cnt, median;

	cnt = 0;
	for (i = 0; i < d->eblks; i++) {
		eb = d->eb_data + i;

		if (eb->flags & (EBLOCK_NOMAGIC | EBLOCK_BAD | EBLOCK_READERR))
			continue;

		__mtdswap_rb_add(&hist_root, eb);
		cnt++;
	}

	if (cnt == 0)
		return;

	medrb = mtdswap_rb_index(&hist_root, cnt / 2);
	median = rb_entry(medrb, struct swap_eb, rb)->erase_count;

	d->max_erase_count = MTDSWAP_ECNT_MAX(&hist_root);

	for (i = 0; i < d->eblks; i++) {
		eb = d->eb_data + i;

		if (eb->flags & (EBLOCK_NOMAGIC | EBLOCK_READERR))
			eb->erase_count = median;

		if (eb->flags & (EBLOCK_NOMAGIC | EBLOCK_BAD | EBLOCK_READERR))
			continue;

		rb_erase(&eb->rb, &hist_root);
	}
}
