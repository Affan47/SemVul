ddp_adjust_page_table(void)
{
	int i;
	unsigned int base_order, order;

	if (PAGE_SIZE < (1UL << ddp_page_shift[0])) {
		pr_info("PAGE_SIZE 0x%lx too small, min 0x%lx\n",
			PAGE_SIZE, 1UL << ddp_page_shift[0]);
		return -EINVAL;
	}

	base_order = get_order(1UL << ddp_page_shift[0]);
	order = get_order(1UL << PAGE_SHIFT);

	for (i = 0; i < DDP_PGIDX_MAX; i++) {

		ddp_page_order[i] = order - base_order + i;
		ddp_page_shift[i] = PAGE_SHIFT + i;
	}
	return 0;
}
