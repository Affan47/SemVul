static int get_iovec_page_array(const struct iovec __user *iov,
				unsigned int nr_vecs, struct page **pages,
				struct partial_page *partial, int aligned)
{
	int buffers = 0, error = 0;

	down_read(&current->mm->mmap_sem);

	while (nr_vecs) {
		unsigned long off, npages;
		struct iovec entry;
		void __user *base;
		size_t len;
		int i;

		error = -EFAULT;
		if (copy_from_user_mmap_sem(&entry, iov, sizeof(entry)))
			break;

		base = entry.iov_base;
		len = entry.iov_len;


		error = 0;
		if (unlikely(!len))
			break;
		error = -EFAULT;
		if (unlikely(!base))
			break;


		off = (unsigned long) base & ~PAGE_MASK;


		error = -EINVAL;
		if (aligned && (off || len & ~PAGE_MASK))
			break;

		npages = (off + len + PAGE_SIZE - 1) >> PAGE_SHIFT;
		if (npages > PIPE_BUFFERS - buffers)
			npages = PIPE_BUFFERS - buffers;

		error = get_user_pages(current, current->mm,
				       (unsigned long) base, npages, 0, 0,
				       &pages[buffers], NULL);

		if (unlikely(error <= 0))
			break;


		for (i = 0; i < error; i++) {
			const int plen = min_t(size_t, len, PAGE_SIZE - off);

			partial[buffers].offset = off;
			partial[buffers].len = plen;

			off = 0;
			len -= plen;
			buffers++;
		}


		if (len)
			break;


		if (error < npages || buffers == PIPE_BUFFERS)
			break;

		nr_vecs--;
		iov++;
	}

	up_read(&current->mm->mmap_sem);

	if (buffers)
		return buffers;

	return error;
}
