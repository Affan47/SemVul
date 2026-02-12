generic_file_direct_write(struct kiocb *iocb, const struct iovec *iov,
		unsigned long *nr_segs, loff_t pos, loff_t *ppos,
		size_t count, size_t ocount)
{
	struct file	*file = iocb->ki_filp;
	struct address_space *mapping = file->f_mapping;
	struct inode	*inode = mapping->host;
	ssize_t		written;
	size_t		write_len;
	pgoff_t		end;

	if (count != ocount)
		*nr_segs = iov_shorten((struct iovec *)iov, *nr_segs, count);


	write_len = iov_length(iov, *nr_segs);
	end = (pos + write_len - 1) >> PAGE_CACHE_SHIFT;
	if (mapping_mapped(mapping))
		unmap_mapping_range(mapping, pos, write_len, 0);

	written = filemap_write_and_wait(mapping);
	if (written)
		goto out;


	if (mapping->nrpages) {
		written = invalidate_inode_pages2_range(mapping,
					pos >> PAGE_CACHE_SHIFT, end);
		if (written)
			goto out;
	}

	written = mapping->a_ops->direct_IO(WRITE, iocb, iov, pos, *nr_segs);


	if (mapping->nrpages) {
		invalidate_inode_pages2_range(mapping,
					      pos >> PAGE_CACHE_SHIFT, end);
	}

	if (written > 0) {
		loff_t end = pos + written;
		if (end > i_size_read(inode) && !S_ISBLK(inode->i_mode)) {
			i_size_write(inode,  end);
			mark_inode_dirty(inode);
		}
		*ppos = end;
	}


out:
	if ((written >= 0 || written == -EIOCBQUEUED) &&
	    ((file->f_flags & O_SYNC) || IS_SYNC(inode))) {
		int err = generic_osync_inode(inode, mapping, OSYNC_METADATA);
		if (err < 0)
			written = err;
	}
	return written;
}
