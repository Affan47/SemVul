int ext4_get_inode_loc(struct inode *inode, struct ext4_iloc *iloc)
{

	return __ext4_get_inode_loc(inode, iloc,
		!(EXT4_I(inode)->i_state & EXT4_STATE_XATTR));
}
