static void __init hugetlb_init_hstates(void)
{
	struct hstate *h, *h2;

	for_each_hstate(h) {
		if (minimum_order > huge_page_order(h))
			minimum_order = huge_page_order(h);


		if (!hstate_is_gigantic(h))
			hugetlb_hstate_alloc_pages(h);


		if (hstate_is_gigantic(h) && !gigantic_page_runtime_supported())
			continue;
		if (hugetlb_cma_size && h->order <= HUGETLB_PAGE_ORDER)
			continue;
		for_each_hstate(h2) {
			if (h2 == h)
				continue;
			if (h2->order < h->order &&
			    h2->order > h->demote_order)
				h->demote_order = h2->order;
		}
	}
	VM_BUG_ON(minimum_order == UINT_MAX);
}
