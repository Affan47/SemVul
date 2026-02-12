static void free_gigantic_page(struct page *page, unsigned int order)
{


#ifdef CONFIG_CMA
	if (cma_release(hugetlb_cma[page_to_nid(page)], page, 1 << order))
		return;
#endif

	free_contig_range(page_to_pfn(page), 1 << order);
}
