static int pipe_to_file(struct pipe_inode_info *pipe, struct pipe_buffer *buf,
			struct splice_desc *sd)
{
	struct file *file = sd->file;
	struct address_space *mapping = file->f_mapping;
	gfp_t gfp_mask = mapping_gfp_mask(mapping);
	unsigned int offset, this_len;
	struct page *page;
	pgoff_t index;
	int ret;


	ret = buf->ops->pin(pipe, buf);
	if (unlikely(ret))
		return ret;

	index = sd->pos >> PAGE_CACHE_SHIFT;
	offset = sd->pos & ~PAGE_CACHE_MASK;

	this_len = sd->len;
	if (this_len + offset > PAGE_CACHE_SIZE)
		this_len = PAGE_CACHE_SIZE - offset;


	if ((sd->flags & SPLICE_F_MOVE) && this_len == PAGE_CACHE_SIZE) {


		if (buf->ops->steal(pipe, buf))
			goto find_page;

		page = buf->page;
		if (add_to_page_cache(page, mapping, index, gfp_mask)) {
			unlock_page(page);
			goto find_page;
		}

		page_cache_get(page);

		if (!(buf->flags & PIPE_BUF_FLAG_LRU))
			lru_cache_add(page);
	} else {
find_page:
		page = find_lock_page(mapping, index);
		if (!page) {
			ret = -ENOMEM;
			page = page_cache_alloc_cold(mapping);
			if (unlikely(!page))
				goto out_ret;


			ret = add_to_page_cache_lru(page, mapping, index,
						    gfp_mask);
			if (unlikely(ret))
				goto out;
		}


		if (!PageUptodate(page)) {
			if (this_len < PAGE_CACHE_SIZE) {
				ret = mapping->a_ops->readpage(file, page);
				if (unlikely(ret))
					goto out;

				lock_page(page);

				if (!PageUptodate(page)) {


					if (!page->mapping) {
						unlock_page(page);
						page_cache_release(page);
						goto find_page;
					}
					ret = -EIO;
					goto out;
				}
			} else
				SetPageUptodate(page);
		}
	}

	ret = mapping->a_ops->prepare_write(file, page, offset, offset+this_len);
	if (unlikely(ret)) {
		loff_t isize = i_size_read(mapping->host);

		if (ret != AOP_TRUNCATED_PAGE)
			unlock_page(page);
		page_cache_release(page);
		if (ret == AOP_TRUNCATED_PAGE)
			goto find_page;


		if (sd->pos + this_len > isize)
			vmtruncate(mapping->host, isize);

		goto out_ret;
	}

	if (buf->page != page) {


		char *src = buf->ops->map(pipe, buf, 1);
		char *dst = kmap_atomic(page, KM_USER1);

		memcpy(dst + offset, src + buf->offset, this_len);
		flush_dcache_page(page);
		kunmap_atomic(dst, KM_USER1);
		buf->ops->unmap(pipe, buf, src);
	}

	ret = mapping->a_ops->commit_write(file, page, offset, offset+this_len);
	if (!ret) {


		ret = this_len;
		mark_page_accessed(page);
		balance_dirty_pages_ratelimited(mapping);
	} else if (ret == AOP_TRUNCATED_PAGE) {
		page_cache_release(page);
		goto find_page;
	}
out:
	page_cache_release(page);
	unlock_page(page);
out_ret:
	return ret;
}
