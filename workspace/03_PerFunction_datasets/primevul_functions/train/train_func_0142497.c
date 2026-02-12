static int f2fs_drop_inode(struct inode *inode)
{


	if (!inode_unhashed(inode) && inode->i_state & I_SYNC) {
		if (!inode->i_nlink && !is_bad_inode(inode)) {

			atomic_inc(&inode->i_count);
			spin_unlock(&inode->i_lock);


			if (f2fs_is_atomic_file(inode))
				commit_inmem_pages(inode, true);


			f2fs_destroy_extent_node(inode);

			sb_start_intwrite(inode->i_sb);
			i_size_write(inode, 0);

			if (F2FS_HAS_BLOCKS(inode))
				f2fs_truncate(inode, true);

			sb_end_intwrite(inode->i_sb);

#ifdef CONFIG_F2FS_FS_ENCRYPTION
			if (F2FS_I(inode)->i_crypt_info)
				f2fs_free_encryption_info(inode,
					F2FS_I(inode)->i_crypt_info);
#endif
			spin_lock(&inode->i_lock);
			atomic_dec(&inode->i_count);
		}
		return 0;
	}
	return generic_drop_inode(inode);
}
