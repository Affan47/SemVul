shmem_file_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
	struct inode	*inode = file->f_path.dentry->d_inode;
	loff_t		pos;
	unsigned long	written;
	ssize_t		err;

	if ((ssize_t) count < 0)
		return -EINVAL;

	if (!access_ok(VERIFY_READ, buf, count))
		return -EFAULT;

	mutex_lock(&inode->i_mutex);

	pos = *ppos;
	written = 0;

	err = generic_write_checks(file, &pos, &count, 0);
	if (err || !count)
		goto out;

	err = remove_suid(file->f_path.dentry);
	if (err)
		goto out;

	inode->i_ctime = inode->i_mtime = CURRENT_TIME;

	do {
		struct page *page = NULL;
		unsigned long bytes, index, offset;
		char *kaddr;
		int left;

		offset = (pos & (PAGE_CACHE_SIZE -1));
		index = pos >> PAGE_CACHE_SHIFT;
		bytes = PAGE_CACHE_SIZE - offset;
		if (bytes > count)
			bytes = count;


		err = shmem_getpage(inode, index, &page, SGP_WRITE, NULL);
		if (err)
			break;

		left = bytes;
		if (PageHighMem(page)) {
			volatile unsigned char dummy;
			__get_user(dummy, buf);
			__get_user(dummy, buf + bytes - 1);

			kaddr = kmap_atomic(page, KM_USER0);
			left = __copy_from_user_inatomic(kaddr + offset,
							buf, bytes);
			kunmap_atomic(kaddr, KM_USER0);
		}
		if (left) {
			kaddr = kmap(page);
			left = __copy_from_user(kaddr + offset, buf, bytes);
			kunmap(page);
		}

		written += bytes;
		count -= bytes;
		pos += bytes;
		buf += bytes;
		if (pos > inode->i_size)
			i_size_write(inode, pos);

		flush_dcache_page(page);
		set_page_dirty(page);
		mark_page_accessed(page);
		page_cache_release(page);

		if (left) {
			pos -= left;
			written -= left;
			err = -EFAULT;
			break;
		}


		cond_resched();
	} while (count);

	*ppos = pos;
	if (written)
		err = written;
out:
	mutex_unlock(&inode->i_mutex);
	return err;
}
