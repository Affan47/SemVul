static int fuse_readdir_cached(struct file *file, struct dir_context *ctx)
{
	struct fuse_file *ff = file->private_data;
	struct inode *inode = file_inode(file);
	struct fuse_conn *fc = get_fuse_conn(inode);
	struct fuse_inode *fi = get_fuse_inode(inode);
	enum fuse_parse_result res;
	pgoff_t index;
	unsigned int size;
	struct page *page;
	void *addr;


	if (ff->readdir.pos != ctx->pos) {
		ff->readdir.pos = 0;
		ff->readdir.cache_off = 0;
	}


	if (!ctx->pos && fc->auto_inval_data) {
		int err = fuse_update_attributes(inode, file);

		if (err)
			return err;
	}

retry:
	spin_lock(&fi->rdc.lock);
retry_locked:
	if (!fi->rdc.cached) {

		if (!ctx->pos && !fi->rdc.size) {
			fi->rdc.mtime = inode->i_mtime;
			fi->rdc.iversion = inode_query_iversion(inode);
		}
		spin_unlock(&fi->rdc.lock);
		return UNCACHED;
	}


	if (!ctx->pos) {
		if (inode_peek_iversion(inode) != fi->rdc.iversion ||
		    !timespec64_equal(&fi->rdc.mtime, &inode->i_mtime)) {
			fuse_rdc_reset(inode);
			goto retry_locked;
		}
	}


	if (ff->readdir.version != fi->rdc.version) {
		ff->readdir.pos = 0;
		ff->readdir.cache_off = 0;
	}


	if (ff->readdir.pos == 0)
		ff->readdir.version = fi->rdc.version;

	WARN_ON(fi->rdc.size < ff->readdir.cache_off);

	index = ff->readdir.cache_off >> PAGE_SHIFT;

	if (index == (fi->rdc.size >> PAGE_SHIFT))
		size = fi->rdc.size & ~PAGE_MASK;
	else
		size = PAGE_SIZE;
	spin_unlock(&fi->rdc.lock);


	if ((ff->readdir.cache_off & ~PAGE_MASK) == size)
		return 0;

	page = find_get_page_flags(file->f_mapping, index,
				   FGP_ACCESSED | FGP_LOCK);
	spin_lock(&fi->rdc.lock);
	if (!page) {


		if (fi->rdc.version == ff->readdir.version)
			fuse_rdc_reset(inode);
		goto retry_locked;
	}


	if (ff->readdir.version != fi->rdc.version) {
		spin_unlock(&fi->rdc.lock);
		unlock_page(page);
		put_page(page);
		goto retry;
	}
	spin_unlock(&fi->rdc.lock);


	addr = kmap(page);
	res = fuse_parse_cache(ff, addr, size, ctx);
	kunmap(page);
	unlock_page(page);
	put_page(page);

	if (res == FOUND_ERR)
		return -EIO;

	if (res == FOUND_ALL)
		return 0;

	if (size == PAGE_SIZE) {

		ff->readdir.cache_off = ALIGN(ff->readdir.cache_off, PAGE_SIZE);
		goto retry;
	}


	return res == FOUND_SOME ? 0 : UNCACHED;
}
