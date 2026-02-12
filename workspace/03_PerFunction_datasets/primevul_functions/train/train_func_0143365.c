read_block_for_search(struct btrfs_root *root, struct btrfs_path *p,
		      struct extent_buffer **eb_ret, int level, int slot,
		      const struct btrfs_key *key)
{
	struct btrfs_fs_info *fs_info = root->fs_info;
	u64 blocknr;
	u64 gen;
	struct extent_buffer *tmp;
	struct btrfs_key first_key;
	int ret;
	int parent_level;

	blocknr = btrfs_node_blockptr(*eb_ret, slot);
	gen = btrfs_node_ptr_generation(*eb_ret, slot);
	parent_level = btrfs_header_level(*eb_ret);
	btrfs_node_key_to_cpu(*eb_ret, &first_key, slot);

	tmp = find_extent_buffer(fs_info, blocknr);
	if (tmp) {

		if (btrfs_buffer_uptodate(tmp, gen, 1) > 0) {


			if (btrfs_verify_level_key(tmp,
					parent_level - 1, &first_key, gen)) {
				free_extent_buffer(tmp);
				return -EUCLEAN;
			}
			*eb_ret = tmp;
			return 0;
		}


		ret = btrfs_read_buffer(tmp, gen, parent_level - 1, &first_key);
		if (!ret) {
			*eb_ret = tmp;
			return 0;
		}
		free_extent_buffer(tmp);
		btrfs_release_path(p);
		return -EIO;
	}


	btrfs_unlock_up_safe(p, level + 1);

	if (p->reada != READA_NONE)
		reada_for_search(fs_info, p, level, slot, key->objectid);

	ret = -EAGAIN;
	tmp = read_tree_block(fs_info, blocknr, root->root_key.objectid,
			      gen, parent_level - 1, &first_key);
	if (!IS_ERR(tmp)) {


		if (!extent_buffer_uptodate(tmp))
			ret = -EIO;
		free_extent_buffer(tmp);
	} else {
		ret = PTR_ERR(tmp);
	}

	btrfs_release_path(p);
	return ret;
}
