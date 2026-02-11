cavan_ext4_traversal_indirect(struct cavan_ext4_walker *walker, u32 *blocks, size_t count, int level)
{
	u32 *block_end;

	for (block_end = blocks + count; blocks < block_end && *blocks; blocks++)
	{
		int ret;
		ssize_t rdlen;
		char buff[walker->fs->block_size];

		rdlen = cavan_ext4_read_block(walker->fs, *blocks, buff, 1);
		if (rdlen < 0)
		{
			pr_red_info("cavan_ext4_read_block");
			return rdlen;
		}

		if (level > 0)
		{
			ret = cavan_ext4_traversal_indirect(walker, (u32 *) buff, walker->fs->block_size >> 2, level - 1);
		}
		else
		{
			ret = cavan_ext4_walker_write_block(walker, buff, 1);
		}

		if (ret != WALKER_ACTION_CONTINUE)
		{
			return ret;
		}
	}

	return WALKER_ACTION_CONTINUE;
}
