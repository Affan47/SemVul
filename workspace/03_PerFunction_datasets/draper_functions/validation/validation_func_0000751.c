pcol_free(struct page_collect *pcol)
{
	kfree(pcol->pages);
	pcol->pages = NULL;

	if (pcol->ios) {
		ore_put_io_state(pcol->ios);
		pcol->ios = NULL;
	}
}
