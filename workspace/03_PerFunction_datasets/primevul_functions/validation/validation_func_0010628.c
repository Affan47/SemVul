static bool fuse_writepage_need_send(struct fuse_conn *fc, struct page *page,
				     struct fuse_args_pages *ap,
				     struct fuse_fill_wb_data *data)
{
	WARN_ON(!ap->num_pages);


	if (fuse_page_is_writeback(data->inode, page->index))
		return true;


	if (ap->num_pages == fc->max_pages)
		return true;


	if ((ap->num_pages + 1) * PAGE_SIZE > fc->max_write)
		return true;


	if (data->orig_pages[ap->num_pages - 1]->index + 1 != page->index)
		return true;


	if (ap->num_pages == data->max_pages && !fuse_pages_realloc(data))
		return true;

	return false;
}
