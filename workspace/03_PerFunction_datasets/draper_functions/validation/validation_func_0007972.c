find_group_dir(struct super_block *sb, struct inode *parent)
{
	int ngroups = EXT2_SB(sb)->s_groups_count;
	int avefreei = ext2_count_free_inodes(sb) / ngroups;
	struct ext2_group_desc *desc, *best_desc = NULL;
	int group, best_group = -1;

	for (group = 0; group < ngroups; group++) {
		desc = ext2_get_group_desc (sb, group, NULL);
		if (!desc || !desc->bg_free_inodes_count)
			continue;
		if (le16_to_cpu(desc->bg_free_inodes_count) < avefreei)
			continue;
		if (!best_desc ||
		    (le16_to_cpu(desc->bg_free_blocks_count) >
		     le16_to_cpu(best_desc->bg_free_blocks_count))) {
			best_group = group;
			best_desc = desc;
		}
	}
	if (!best_desc)
		return -1;

	return best_group;
}
