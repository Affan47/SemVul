btrfs_have_ordered_extents_in_range(struct inode *inode,
					 u64 file_offset,
					 u64 len)
{
	struct btrfs_ordered_extent *oe;

	oe = btrfs_lookup_ordered_range(inode, file_offset, len);
	if (oe) {
		btrfs_put_ordered_extent(oe);
		return true;
	}
	return false;
}
