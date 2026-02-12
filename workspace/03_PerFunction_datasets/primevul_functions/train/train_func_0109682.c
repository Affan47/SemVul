int uprobe_register(struct inode *inode, loff_t offset, struct uprobe_consumer *uc)
{
	struct uprobe *uprobe;
	int ret;


	if (!uc->handler && !uc->ret_handler)
		return -EINVAL;


	if (!inode->i_mapping->a_ops->readpage && !shmem_mapping(inode->i_mapping))
		return -EIO;

	if (offset > i_size_read(inode))
		return -EINVAL;

 retry:
	uprobe = alloc_uprobe(inode, offset);
	if (!uprobe)
		return -ENOMEM;


	down_write(&uprobe->register_rwsem);
	ret = -EAGAIN;
	if (likely(uprobe_is_active(uprobe))) {
		ret = __uprobe_register(uprobe, uc);
		if (ret)
			__uprobe_unregister(uprobe, uc);
	}
	up_write(&uprobe->register_rwsem);
	put_uprobe(uprobe);

	if (unlikely(ret == -EAGAIN))
		goto retry;
	return ret;
}
