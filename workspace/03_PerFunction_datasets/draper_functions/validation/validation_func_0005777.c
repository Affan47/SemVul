reiserfs_write_unlock_nested(struct super_block *s)
{
	struct reiserfs_sb_info *sb_i = REISERFS_SB(s);
	int depth;


	if (sb_i->lock_owner != current)
		return -1;

	depth = sb_i->lock_depth;

	sb_i->lock_depth = -1;
	sb_i->lock_owner = NULL;
	mutex_unlock(&sb_i->lock);

	return depth;
}
