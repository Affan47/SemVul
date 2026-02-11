logfs_del_transaction(struct inode *inode, struct logfs_transaction *ta)
{
	struct logfs_block *block = logfs_inode(inode)->li_block;

	if (block && block->ta)
		block->ta = NULL;
}
