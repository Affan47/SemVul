void unpin_user_page(struct page *page)
{
	int refs = 1;

	page = compound_head(page);


	if (__unpin_devmap_managed_user_page(page))
		return;

	if (hpage_pincount_available(page))
		hpage_pincount_sub(page, 1);
	else
		refs = GUP_PIN_COUNTING_BIAS;

	if (page_ref_sub_and_test(page, refs))
		__put_page(page);

	mod_node_page_state(page_pgdat(page), NR_FOLL_PIN_RELEASED, 1);
}
