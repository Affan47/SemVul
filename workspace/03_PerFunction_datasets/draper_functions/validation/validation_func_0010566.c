au_test_ibusy(struct inode *inode, aufs_bindex_t bstart,
			 aufs_bindex_t bend)
{
	return (inode && !S_ISDIR(inode->i_mode)) || bstart == bend;
}
