int ext4_da_write_inline_data_end(struct inode *inode, loff_t pos,
				  unsigned len, unsigned copied,
				  struct page *page)
{
	int i_size_changed = 0;
	int ret;

	ret = ext4_write_inline_data_end(inode, pos, len, copied, page);
	if (ret < 0) {
		unlock_page(page);
		put_page(page);
		return ret;
	}
	copied = ret;


	if (pos+copied > inode->i_size) {
		i_size_write(inode, pos+copied);
		i_size_changed = 1;
	}
	unlock_page(page);
	put_page(page);


	if (i_size_changed)
		mark_inode_dirty(inode);

	return copied;
}
