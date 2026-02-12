static bool path_connected(const struct path *path)
{
	struct vfsmount *mnt = path->mnt;
	struct super_block *sb = mnt->mnt_sb;


	if (!(sb->s_iflags & SB_I_MULTIROOT) && (mnt->mnt_root == sb->s_root))
		return true;

	return is_subdir(path->dentry, mnt->mnt_root);
}
