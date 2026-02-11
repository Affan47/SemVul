check_extent_flags(u64 flags)
{
	if ((flags & BTRFS_EXTENT_FLAG_DATA) &&
	    (flags & BTRFS_EXTENT_FLAG_TREE_BLOCK))
		return 1;
	if (!(flags & BTRFS_EXTENT_FLAG_DATA) &&
	    !(flags & BTRFS_EXTENT_FLAG_TREE_BLOCK))
		return 1;
	if ((flags & BTRFS_EXTENT_FLAG_DATA) &&
	    (flags & BTRFS_BLOCK_FLAG_FULL_BACKREF))
		return 1;
	return 0;
}
