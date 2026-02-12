static int remove_chunk_item(struct btrfs_trans_handle *trans,
			     struct map_lookup *map, u64 chunk_offset)
{
	int i;


	lockdep_assert_held(&trans->fs_info->chunk_mutex);

	for (i = 0; i < map->num_stripes; i++) {
		int ret;

		ret = btrfs_update_device(trans, map->stripes[i].dev);
		if (ret)
			return ret;
	}

	return btrfs_free_chunk(trans, chunk_offset);
}
