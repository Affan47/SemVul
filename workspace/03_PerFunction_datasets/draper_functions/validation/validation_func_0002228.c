nilfs_begin_page_io(struct page *page)
{
	if (!page || PageWriteback(page))


		return;

	lock_page(page);
	clear_page_dirty_for_io(page);
	set_page_writeback(page);
	unlock_page(page);
}
