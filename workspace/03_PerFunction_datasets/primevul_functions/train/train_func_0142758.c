static bool __unpin_devmap_managed_user_page(struct page *page)
{
	int count, refs = 1;

	if (!page_is_devmap_managed(page))
		return false;

	if (hpage_pincount_available(page))
		hpage_pincount_sub(page, 1);
	else
		refs = GUP_PIN_COUNTING_BIAS;

	count = page_ref_sub_return(page, refs);

	mod_node_page_state(page_pgdat(page), NR_FOLL_PIN_RELEASED, 1);


	if (count == 1)
		free_devmap_managed_page(page);
	else if (!count)
		__put_page(page);

	return true;
}
