void __paginginit set_pageblock_order(void)
{
	unsigned int order;


	if (pageblock_order)
		return;

	if (HPAGE_SHIFT > PAGE_SHIFT)
		order = HUGETLB_PAGE_ORDER;
	else
		order = MAX_ORDER - 1;


	pageblock_order = order;
}
