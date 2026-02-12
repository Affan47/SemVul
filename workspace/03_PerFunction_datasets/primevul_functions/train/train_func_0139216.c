int scrub_enumerate_chunks(struct scrub_ctx *sctx,
			   struct btrfs_device *scrub_dev, u64 start, u64 end)
{
	struct btrfs_dev_extent *dev_extent = NULL;
	struct btrfs_path *path;
	struct btrfs_fs_info *fs_info = sctx->fs_info;
	struct btrfs_root *root = fs_info->dev_root;
	u64 length;
	u64 chunk_offset;
	int ret = 0;
	int ro_set;
	int slot;
	struct extent_buffer *l;
	struct btrfs_key key;
	struct btrfs_key found_key;
	struct btrfs_block_group_cache *cache;
	struct btrfs_dev_replace *dev_replace = &fs_info->dev_replace;

	path = btrfs_alloc_path();
	if (!path)
		return -ENOMEM;

	path->reada = READA_FORWARD;
	path->search_commit_root = 1;
	path->skip_locking = 1;

	key.objectid = scrub_dev->devid;
	key.offset = 0ull;
	key.type = BTRFS_DEV_EXTENT_KEY;

	while (1) {
		ret = btrfs_search_slot(NULL, root, &key, path, 0, 0);
		if (ret < 0)
			break;
		if (ret > 0) {
			if (path->slots[0] >=
			    btrfs_header_nritems(path->nodes[0])) {
				ret = btrfs_next_leaf(root, path);
				if (ret < 0)
					break;
				if (ret > 0) {
					ret = 0;
					break;
				}
			} else {
				ret = 0;
			}
		}

		l = path->nodes[0];
		slot = path->slots[0];

		btrfs_item_key_to_cpu(l, &found_key, slot);

		if (found_key.objectid != scrub_dev->devid)
			break;

		if (found_key.type != BTRFS_DEV_EXTENT_KEY)
			break;

		if (found_key.offset >= end)
			break;

		if (found_key.offset < key.offset)
			break;

		dev_extent = btrfs_item_ptr(l, slot, struct btrfs_dev_extent);
		length = btrfs_dev_extent_length(l, dev_extent);

		if (found_key.offset + length <= start)
			goto skip;

		chunk_offset = btrfs_dev_extent_chunk_offset(l, dev_extent);


		cache = btrfs_lookup_block_group(fs_info, chunk_offset);


		if (!cache)
			goto skip;


		scrub_pause_on(fs_info);
		ret = btrfs_inc_block_group_ro(cache);
		if (!ret && sctx->is_dev_replace) {


			btrfs_wait_block_group_reservations(cache);
			btrfs_wait_nocow_writers(cache);
			ret = btrfs_wait_ordered_roots(fs_info, U64_MAX,
						       cache->key.objectid,
						       cache->key.offset);
			if (ret > 0) {
				struct btrfs_trans_handle *trans;

				trans = btrfs_join_transaction(root);
				if (IS_ERR(trans))
					ret = PTR_ERR(trans);
				else
					ret = btrfs_commit_transaction(trans);
				if (ret) {
					scrub_pause_off(fs_info);
					btrfs_put_block_group(cache);
					break;
				}
			}
		}
		scrub_pause_off(fs_info);

		if (ret == 0) {
			ro_set = 1;
		} else if (ret == -ENOSPC) {


			ro_set = 0;
		} else {
			btrfs_warn(fs_info,
				   "failed setting block group ro: %d", ret);
			btrfs_put_block_group(cache);
			break;
		}

		down_write(&fs_info->dev_replace.rwsem);
		dev_replace->cursor_right = found_key.offset + length;
		dev_replace->cursor_left = found_key.offset;
		dev_replace->item_needs_writeback = 1;
		up_write(&dev_replace->rwsem);

		ret = scrub_chunk(sctx, scrub_dev, chunk_offset, length,
				  found_key.offset, cache);


		sctx->flush_all_writes = true;
		scrub_submit(sctx);
		mutex_lock(&sctx->wr_lock);
		scrub_wr_submit(sctx);
		mutex_unlock(&sctx->wr_lock);

		wait_event(sctx->list_wait,
			   atomic_read(&sctx->bios_in_flight) == 0);

		scrub_pause_on(fs_info);


		wait_event(sctx->list_wait,
			   atomic_read(&sctx->workers_pending) == 0);
		sctx->flush_all_writes = false;

		scrub_pause_off(fs_info);

		down_write(&fs_info->dev_replace.rwsem);
		dev_replace->cursor_left = dev_replace->cursor_right;
		dev_replace->item_needs_writeback = 1;
		up_write(&fs_info->dev_replace.rwsem);

		if (ro_set)
			btrfs_dec_block_group_ro(cache);


		spin_lock(&cache->lock);
		if (!cache->removed && !cache->ro && cache->reserved == 0 &&
		    btrfs_block_group_used(&cache->item) == 0) {
			spin_unlock(&cache->lock);
			btrfs_mark_bg_unused(cache);
		} else {
			spin_unlock(&cache->lock);
		}

		btrfs_put_block_group(cache);
		if (ret)
			break;
		if (sctx->is_dev_replace &&
		    atomic64_read(&dev_replace->num_write_errors) > 0) {
			ret = -EIO;
			break;
		}
		if (sctx->stat.malloc_errors > 0) {
			ret = -ENOMEM;
			break;
		}
skip:
		key.offset = found_key.offset + length;
		btrfs_release_path(path);
	}

	btrfs_free_path(path);

	return ret;
}
