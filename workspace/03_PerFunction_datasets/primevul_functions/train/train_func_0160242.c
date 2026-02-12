static void ext4_update_super(struct super_block *sb,
			     struct ext4_new_flex_group_data *flex_gd)
{
	ext4_fsblk_t blocks_count = 0;
	ext4_fsblk_t free_blocks = 0;
	ext4_fsblk_t reserved_blocks = 0;
	struct ext4_new_group_data *group_data = flex_gd->groups;
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	struct ext4_super_block *es = sbi->s_es;
	int i, ret;

	BUG_ON(flex_gd->count == 0 || group_data == NULL);


	for (i = 0; i < flex_gd->count; i++) {
		blocks_count += group_data[i].blocks_count;
		free_blocks += group_data[i].free_blocks_count;
	}

	reserved_blocks = ext4_r_blocks_count(es) * 100;
	do_div(reserved_blocks, ext4_blocks_count(es));
	reserved_blocks *= blocks_count;
	do_div(reserved_blocks, 100);

	ext4_blocks_count_set(es, ext4_blocks_count(es) + blocks_count);
	ext4_free_blocks_count_set(es, ext4_free_blocks_count(es) + free_blocks);
	le32_add_cpu(&es->s_inodes_count, EXT4_INODES_PER_GROUP(sb) *
		     flex_gd->count);
	le32_add_cpu(&es->s_free_inodes_count, EXT4_INODES_PER_GROUP(sb) *
		     flex_gd->count);


	smp_wmb();


	sbi->s_groups_count += flex_gd->count;


	ext4_r_blocks_count_set(es, ext4_r_blocks_count(es) +
				reserved_blocks);


	percpu_counter_add(&sbi->s_freeclusters_counter,
			   EXT4_B2C(sbi, free_blocks));
	percpu_counter_add(&sbi->s_freeinodes_counter,
			   EXT4_INODES_PER_GROUP(sb) * flex_gd->count);

	if (EXT4_HAS_INCOMPAT_FEATURE(sb,
				      EXT4_FEATURE_INCOMPAT_FLEX_BG) &&
	    sbi->s_log_groups_per_flex) {
		ext4_group_t flex_group;
		flex_group = ext4_flex_group(sbi, group_data[0].group);
		atomic_add(EXT4_B2C(sbi, free_blocks),
			   &sbi->s_flex_groups[flex_group].free_clusters);
		atomic_add(EXT4_INODES_PER_GROUP(sb) * flex_gd->count,
			   &sbi->s_flex_groups[flex_group].free_inodes);
	}


	ext4_calculate_overhead(sb);

	if (test_opt(sb, DEBUG))
		printk(KERN_DEBUG "EXT4-fs: added group %u:"
		       "%llu blocks(%llu free %llu reserved)\n", flex_gd->count,
		       blocks_count, free_blocks, reserved_blocks);
}
