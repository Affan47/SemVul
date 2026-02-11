btrfs_remove_chunk(struct btrfs_trans_handle *trans,
		       struct btrfs_root *root, u64 chunk_offset)
{
	struct extent_map_tree *em_tree;
	struct extent_map *em;
	struct btrfs_root *extent_root = root->fs_info->extent_root;
	struct map_lookup *map;
	u64 dev_extent_len = 0;
	u64 chunk_objectid = BTRFS_FIRST_CHUNK_TREE_OBJECTID;
	int i, ret = 0;


	root = root->fs_info->chunk_root;
	em_tree = &root->fs_info->mapping_tree.map_tree;

	read_lock(&em_tree->lock);
	em = lookup_extent_mapping(em_tree, chunk_offset, 1);
	read_unlock(&em_tree->lock);

	if (!em || em->start > chunk_offset ||
	    em->start + em->len < chunk_offset) {


		ASSERT(0);
		if (em)
			free_extent_map(em);
		return -EINVAL;
	}
	map = (struct map_lookup *)em->bdev;
	lock_chunks(root->fs_info->chunk_root);
	check_system_chunk(trans, extent_root, map->type);
	unlock_chunks(root->fs_info->chunk_root);

	for (i = 0; i < map->num_stripes; i++) {
		struct btrfs_device *device = map->stripes[i].dev;
		ret = btrfs_free_dev_extent(trans, device,
					    map->stripes[i].physical,
					    &dev_extent_len);
		if (ret) {
			btrfs_abort_transaction(trans, root, ret);
			goto out;
		}

		if (device->bytes_used > 0) {
			lock_chunks(root);
			btrfs_device_set_bytes_used(device,
					device->bytes_used - dev_extent_len);
			spin_lock(&root->fs_info->free_chunk_lock);
			root->fs_info->free_chunk_space += dev_extent_len;
			spin_unlock(&root->fs_info->free_chunk_lock);
			btrfs_clear_space_info_full(root->fs_info);
			unlock_chunks(root);
		}

		if (map->stripes[i].dev) {
			ret = btrfs_update_device(trans, map->stripes[i].dev);
			if (ret) {
				btrfs_abort_transaction(trans, root, ret);
				goto out;
			}
		}
	}
	ret = btrfs_free_chunk(trans, root, chunk_objectid, chunk_offset);
	if (ret) {
		btrfs_abort_transaction(trans, root, ret);
		goto out;
	}

	trace_btrfs_chunk_free(root, map, chunk_offset, em->len);

	if (map->type & BTRFS_BLOCK_GROUP_SYSTEM) {
		ret = btrfs_del_sys_chunk(root, chunk_objectid, chunk_offset);
		if (ret) {
			btrfs_abort_transaction(trans, root, ret);
			goto out;
		}
	}

	ret = btrfs_remove_block_group(trans, extent_root, chunk_offset, em);
	if (ret) {
		btrfs_abort_transaction(trans, extent_root, ret);
		goto out;
	}

out:

	free_extent_map(em);
	return ret;
}
