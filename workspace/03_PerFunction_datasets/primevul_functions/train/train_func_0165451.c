static int ext4_da_writepage(struct page *page,
				struct writeback_control *wbc)
{
	int ret = 0;
	loff_t size;
	unsigned int len;
	struct buffer_head *page_bufs;
	struct inode *inode = page->mapping->host;

	trace_mark(ext4_da_writepage,
		   "dev %s ino %lu page_index %lu",
		   inode->i_sb->s_id, inode->i_ino, page->index);
	size = i_size_read(inode);
	if (page->index == size >> PAGE_CACHE_SHIFT)
		len = size & ~PAGE_CACHE_MASK;
	else
		len = PAGE_CACHE_SIZE;

	if (page_has_buffers(page)) {
		page_bufs = page_buffers(page);
		if (walk_page_buffers(NULL, page_bufs, 0, len, NULL,
					ext4_bh_unmapped_or_delay)) {


			redirty_page_for_writepage(wbc, page);
			unlock_page(page);
			return 0;
		}
	} else {


		ret = block_prepare_write(page, 0, PAGE_CACHE_SIZE,
						ext4_normal_get_block_write);
		if (!ret) {
			page_bufs = page_buffers(page);

			if (walk_page_buffers(NULL, page_bufs, 0, len, NULL,
						ext4_bh_unmapped_or_delay)) {
				redirty_page_for_writepage(wbc, page);
				unlock_page(page);
				return 0;
			}
		} else {


			redirty_page_for_writepage(wbc, page);
			unlock_page(page);
			return 0;
		}

		block_commit_write(page, 0, PAGE_CACHE_SIZE);
	}

	if (test_opt(inode->i_sb, NOBH) && ext4_should_writeback_data(inode))
		ret = nobh_writepage(page, ext4_normal_get_block_write, wbc);
	else
		ret = block_write_full_page(page,
						ext4_normal_get_block_write,
						wbc);

	return ret;
}
