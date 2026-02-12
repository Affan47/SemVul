int btrfs_search_slot(struct btrfs_trans_handle *trans, struct btrfs_root *root,
		      const struct btrfs_key *key, struct btrfs_path *p,
		      int ins_len, int cow)
{
	struct extent_buffer *b;
	int slot;
	int ret;
	int err;
	int level;
	int lowest_unlock = 1;

	int write_lock_level = 0;
	u8 lowest_level = 0;
	int min_write_lock_level;
	int prev_cmp;

	lowest_level = p->lowest_level;
	WARN_ON(lowest_level && ins_len > 0);
	WARN_ON(p->nodes[0] != NULL);
	BUG_ON(!cow && ins_len);

	if (ins_len < 0) {
		lowest_unlock = 2;


		write_lock_level = 2;
	} else if (ins_len > 0) {


		write_lock_level = 1;
	}

	if (!cow)
		write_lock_level = -1;

	if (cow && (p->keep_locks || p->lowest_level))
		write_lock_level = BTRFS_MAX_LEVEL;

	min_write_lock_level = write_lock_level;

again:
	prev_cmp = -1;
	b = btrfs_search_slot_get_root(root, p, write_lock_level);
	if (IS_ERR(b)) {
		ret = PTR_ERR(b);
		goto done;
	}

	while (b) {
		int dec = 0;

		level = btrfs_header_level(b);

		if (cow) {
			bool last_level = (level == (BTRFS_MAX_LEVEL - 1));


			if (!should_cow_block(trans, root, b)) {
				trans->dirty = true;
				goto cow_done;
			}


			if (level > write_lock_level ||
			    (level + 1 > write_lock_level &&
			    level + 1 < BTRFS_MAX_LEVEL &&
			    p->nodes[level + 1])) {
				write_lock_level = level + 1;
				btrfs_release_path(p);
				goto again;
			}

			if (last_level)
				err = btrfs_cow_block(trans, root, b, NULL, 0,
						      &b,
						      BTRFS_NESTING_COW);
			else
				err = btrfs_cow_block(trans, root, b,
						      p->nodes[level + 1],
						      p->slots[level + 1], &b,
						      BTRFS_NESTING_COW);
			if (err) {
				ret = err;
				goto done;
			}
		}
cow_done:
		p->nodes[level] = b;


		if (!ins_len && !p->keep_locks) {
			int u = level + 1;

			if (u < BTRFS_MAX_LEVEL && p->locks[u]) {
				btrfs_tree_unlock_rw(p->nodes[u], p->locks[u]);
				p->locks[u] = 0;
			}
		}


		if (prev_cmp == 0) {
			slot = 0;
			ret = 0;
		} else {
			ret = btrfs_bin_search(b, key, &slot);
			prev_cmp = ret;
			if (ret < 0)
				goto done;
		}

		if (level == 0) {
			p->slots[level] = slot;


			if (ret == 0 && ins_len > 0 && !p->search_for_extension) {
				ASSERT(ins_len >= sizeof(struct btrfs_item));
				ins_len -= sizeof(struct btrfs_item);
			}
			if (ins_len > 0 &&
			    btrfs_leaf_free_space(b) < ins_len) {
				if (write_lock_level < 1) {
					write_lock_level = 1;
					btrfs_release_path(p);
					goto again;
				}

				err = split_leaf(trans, root, key,
						 p, ins_len, ret == 0);

				BUG_ON(err > 0);
				if (err) {
					ret = err;
					goto done;
				}
			}
			if (!p->search_for_split)
				unlock_up(p, level, lowest_unlock,
					  min_write_lock_level, NULL);
			goto done;
		}
		if (ret && slot > 0) {
			dec = 1;
			slot--;
		}
		p->slots[level] = slot;
		err = setup_nodes_for_search(trans, root, p, b, level, ins_len,
					     &write_lock_level);
		if (err == -EAGAIN)
			goto again;
		if (err) {
			ret = err;
			goto done;
		}
		b = p->nodes[level];
		slot = p->slots[level];


		if (slot == 0 && ins_len && write_lock_level < level + 1) {
			write_lock_level = level + 1;
			btrfs_release_path(p);
			goto again;
		}

		unlock_up(p, level, lowest_unlock, min_write_lock_level,
			  &write_lock_level);

		if (level == lowest_level) {
			if (dec)
				p->slots[level]++;
			goto done;
		}

		err = read_block_for_search(root, p, &b, level, slot, key);
		if (err == -EAGAIN)
			goto again;
		if (err) {
			ret = err;
			goto done;
		}

		if (!p->skip_locking) {
			level = btrfs_header_level(b);
			if (level <= write_lock_level) {
				btrfs_tree_lock(b);
				p->locks[level] = BTRFS_WRITE_LOCK;
			} else {
				btrfs_tree_read_lock(b);
				p->locks[level] = BTRFS_READ_LOCK;
			}
			p->nodes[level] = b;
		}
	}
	ret = 1;
done:
	if (ret < 0 && !p->skip_release_on_error)
		btrfs_release_path(p);
	return ret;
}
