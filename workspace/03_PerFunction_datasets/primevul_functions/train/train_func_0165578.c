static int ext4_dquot_drop(struct inode *inode)
{
	handle_t *handle;
	int ret, err;


	handle = ext4_journal_start(inode, 2*EXT4_QUOTA_DEL_BLOCKS(inode->i_sb));
	if (IS_ERR(handle)) {


		dquot_drop(inode);
		return PTR_ERR(handle);
	}
	ret = dquot_drop(inode);
	err = ext4_journal_stop(handle);
	if (!ret)
		ret = err;
	return ret;
}
