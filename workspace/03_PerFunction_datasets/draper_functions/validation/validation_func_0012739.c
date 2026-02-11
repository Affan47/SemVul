ext2_release_inode(struct super_block *sb, int group, int dir)
{
	struct ext2_group_desc * desc;
	struct buffer_head *bh;

	desc = ext2_get_group_desc(sb, group, &bh);
	if (!desc) {
		ext2_error(sb, "ext2_release_inode",
			"can't get descriptor for group %d", group);
		return;
	}

	spin_lock(sb_bgl_lock(EXT2_SB(sb), group));
	le16_add_cpu(&desc->bg_free_inodes_count, 1);
	if (dir)
		le16_add_cpu(&desc->bg_used_dirs_count, -1);
	spin_unlock(sb_bgl_lock(EXT2_SB(sb), group));
	if (dir)
		percpu_counter_dec(&EXT2_SB(sb)->s_dirs_counter);
	mark_buffer_dirty(bh);
}
