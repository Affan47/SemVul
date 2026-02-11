calc_memmap_size(unsigned long spanned_pages,
						   unsigned long present_pages)
{
	unsigned long pages = spanned_pages;


	if (spanned_pages > present_pages + (present_pages >> 4) &&
	    IS_ENABLED(CONFIG_SPARSEMEM))
		pages = present_pages;

	return PAGE_ALIGN(pages * sizeof(struct page)) >> PAGE_SHIFT;
}
