stuffed_readpage(struct gfs2_inode *ip, struct page *page)
{
	struct buffer_head *dibh;
	u64 dsize = i_size_read(&ip->i_inode);
	void *kaddr;
	int error;


	if (unlikely(page->index)) {
		zero_user(page, 0, PAGE_CACHE_SIZE);
		SetPageUptodate(page);
		return 0;
	}

	error = gfs2_meta_inode_buffer(ip, &dibh);
	if (error)
		return error;

	kaddr = kmap_atomic(page);
	if (dsize > (dibh->b_size - sizeof(struct gfs2_dinode)))
		dsize = (dibh->b_size - sizeof(struct gfs2_dinode));
	memcpy(kaddr, dibh->b_data + sizeof(struct gfs2_dinode), dsize);
	memset(kaddr + dsize, 0, PAGE_CACHE_SIZE - dsize);
	kunmap_atomic(kaddr);
	flush_dcache_page(page);
	brelse(dibh);
	SetPageUptodate(page);

	return 0;
}
