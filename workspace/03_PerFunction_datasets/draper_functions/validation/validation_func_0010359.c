sync_fs_one_sb(struct super_block *sb, void *arg)
{
	if (!(sb->s_flags & MS_RDONLY) && sb->s_op->sync_fs)
		sb->s_op->sync_fs(sb, *(int *)arg);
}
