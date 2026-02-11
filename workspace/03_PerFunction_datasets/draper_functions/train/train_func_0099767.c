process_vm_rw_pages(struct page **pages,
			       unsigned offset,
			       size_t len,
			       struct iov_iter *iter,
			       int vm_write)
{

	while (len && iov_iter_count(iter)) {
		struct page *page = *pages++;
		size_t copy = PAGE_SIZE - offset;
		size_t copied;

		if (copy > len)
			copy = len;

		if (vm_write) {
			copied = copy_page_from_iter(page, offset, copy, iter);
			set_page_dirty_lock(page);
		} else {
			copied = copy_page_to_iter(page, offset, copy, iter);
		}
		len -= copied;
		if (copied < copy && iov_iter_count(iter))
			return -EFAULT;
		offset = 0;
	}
	return 0;
}
