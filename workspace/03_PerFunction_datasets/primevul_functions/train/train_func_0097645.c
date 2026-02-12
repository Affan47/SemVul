static bool __prep_compound_gigantic_page(struct page *page, unsigned int order,
								bool demote)
{
	int i, j;
	int nr_pages = 1 << order;
	struct page *p = page + 1;


	set_compound_order(page, order);
	__ClearPageReserved(page);
	__SetPageHead(page);
	for (i = 1; i < nr_pages; i++, p = mem_map_next(p, page, i)) {


		__ClearPageReserved(p);


		if (!demote) {
			if (!page_ref_freeze(p, 1)) {
				pr_warn("HugeTLB page can not be used due to unexpected inflated ref count\n");
				goto out_error;
			}
		} else {
			VM_BUG_ON_PAGE(page_count(p), p);
		}
		set_compound_head(p, page);
	}
	atomic_set(compound_mapcount_ptr(page), -1);
	atomic_set(compound_pincount_ptr(page), 0);
	return true;

out_error:

	p = page + 1;
	for (j = 1; j < i; j++, p = mem_map_next(p, page, j)) {
		clear_compound_head(p);
		set_page_refcounted(p);
	}

	for (; j < nr_pages; j++, p = mem_map_next(p, page, j))
		__ClearPageReserved(p);
	set_compound_order(page, 0);
	page[1].compound_nr = 0;
	__ClearPageHead(page);
	return false;
}
