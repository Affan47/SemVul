int btrfs_block_can_be_shared(struct btrfs_root *root,
			      struct extent_buffer *buf)
{


	if (test_bit(BTRFS_ROOT_SHAREABLE, &root->state) &&
	    buf != root->node && buf != root->commit_root &&
	    (btrfs_header_generation(buf) <=
	     btrfs_root_last_snapshot(&root->root_item) ||
	     btrfs_header_flag(buf, BTRFS_HEADER_FLAG_RELOC)))
		return 1;

	return 0;
}
