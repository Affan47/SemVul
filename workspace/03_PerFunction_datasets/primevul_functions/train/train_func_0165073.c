__generic_file_splice_read(struct file *in, loff_t *ppos,
			   struct pipe_inode_info *pipe, size_t len,
			   unsigned int flags)
{
	struct address_space *mapping = in->f_mapping;
	unsigned int loff, nr_pages;
	struct page *pages[PIPE_BUFFERS];
	struct partial_page partial[PIPE_BUFFERS];
	struct page *page;
	pgoff_t index, end_index;
	loff_t isize;
	size_t total_len;
	int error, page_nr;
	struct splice_pipe_desc spd = {
		.pages = pages,
		.partial = partial,
		.flags = flags,
		.ops = &page_cache_pipe_buf_ops,
	};

	index = *ppos >> PAGE_CACHE_SHIFT;
	loff = *ppos & ~PAGE_CACHE_MASK;
	nr_pages = (len + loff + PAGE_CACHE_SIZE - 1) >> PAGE_CACHE_SHIFT;

	if (nr_pages > PIPE_BUFFERS)
		nr_pages = PIPE_BUFFERS;


	if (!loff || nr_pages > 1)
		page_cache_readahead(mapping, &in->f_ra, in, index, nr_pages);


	error = 0;
	total_len = 0;


	spd.nr_pages = find_get_pages_contig(mapping, index, nr_pages, pages);


	index += spd.nr_pages;
	while (spd.nr_pages < nr_pages) {


		page = find_get_page(mapping, index);
		if (!page) {


			handle_ra_miss(mapping, &in->f_ra, index);


			page = page_cache_alloc_cold(mapping);
			if (!page)
				break;

			error = add_to_page_cache_lru(page, mapping, index,
					      mapping_gfp_mask(mapping));
			if (unlikely(error)) {
				page_cache_release(page);
				if (error == -EEXIST)
					continue;
				break;
			}


			unlock_page(page);
		}

		pages[spd.nr_pages++] = page;
		index++;
	}


	index = *ppos >> PAGE_CACHE_SHIFT;
	nr_pages = spd.nr_pages;
	spd.nr_pages = 0;
	for (page_nr = 0; page_nr < nr_pages; page_nr++) {
		unsigned int this_len;

		if (!len)
			break;


		this_len = min_t(unsigned long, len, PAGE_CACHE_SIZE - loff);
		page = pages[page_nr];


		if (!PageUptodate(page)) {


			if (flags & SPLICE_F_NONBLOCK)
				break;

			lock_page(page);


			if (!page->mapping) {
				unlock_page(page);
				break;
			}


			if (PageUptodate(page)) {
				unlock_page(page);
				goto fill_it;
			}


			error = mapping->a_ops->readpage(in, page);
			if (unlikely(error)) {


				if (error == AOP_TRUNCATED_PAGE)
					error = 0;

				break;
			}


			isize = i_size_read(mapping->host);
			end_index = (isize - 1) >> PAGE_CACHE_SHIFT;
			if (unlikely(!isize || index > end_index))
				break;


			if (end_index == index) {
				loff = PAGE_CACHE_SIZE - (isize & ~PAGE_CACHE_MASK);
				if (total_len + loff > isize)
					break;


				len = this_len;
				this_len = min(this_len, loff);
				loff = 0;
			}
		}
fill_it:
		partial[page_nr].offset = loff;
		partial[page_nr].len = this_len;
		len -= this_len;
		total_len += this_len;
		loff = 0;
		spd.nr_pages++;
		index++;
	}


	while (page_nr < nr_pages)
		page_cache_release(pages[page_nr++]);

	if (spd.nr_pages)
		return splice_to_pipe(pipe, &spd);

	return error;
}
