int vmtruncate(struct inode * inode, loff_t offset)
{
	if (inode->i_size < offset) {
		unsigned long limit;

		limit = current->signal->rlim[RLIMIT_FSIZE].rlim_cur;
		if (limit != RLIM_INFINITY && offset > limit)
			goto out_sig;
		if (offset > inode->i_sb->s_maxbytes)
			goto out_big;
		i_size_write(inode, offset);
	} else {
		struct address_space *mapping = inode->i_mapping;


		if (IS_SWAPFILE(inode))
			return -ETXTBSY;
		i_size_write(inode, offset);


		unmap_mapping_range(mapping, offset + PAGE_SIZE - 1, 0, 1);
		truncate_inode_pages(mapping, offset);
		unmap_mapping_range(mapping, offset + PAGE_SIZE - 1, 0, 1);
	}

	if (inode->i_op && inode->i_op->truncate)
		inode->i_op->truncate(inode);
	return 0;

out_sig:
	send_sig(SIGXFSZ, current, 0);
out_big:
	return -EFBIG;
}
