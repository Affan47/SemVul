logfs_new_meta_inode(struct super_block *sb, u64 ino)
{
	struct inode *inode;

	inode = new_inode(sb);
	if (!inode)
		return ERR_PTR(-ENOMEM);

	inode->i_mode = S_IFREG;
	inode->i_ino = ino;
	inode->i_data.a_ops = &logfs_reg_aops;
	mapping_set_gfp_mask(&inode->i_data, GFP_NOFS);

	return inode;
}
