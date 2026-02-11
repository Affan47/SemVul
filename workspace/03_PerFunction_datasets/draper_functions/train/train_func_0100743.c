dm_btree_lookup_next(struct dm_btree_info *info, dm_block_t root,
			 uint64_t *keys, uint64_t *rkey, void *value_le)
{
	unsigned level;
	int r = -ENODATA;
	__le64 internal_value_le;
	struct ro_spine spine;

	init_ro_spine(&spine, info);
	for (level = 0; level < info->levels - 1u; level++) {
		r = btree_lookup_raw(&spine, root, keys[level],
				     lower_bound, rkey,
				     &internal_value_le, sizeof(uint64_t));
		if (r)
			goto out;

		if (*rkey != keys[level]) {
			r = -ENODATA;
			goto out;
		}

		root = le64_to_cpu(internal_value_le);
	}

	r = dm_btree_lookup_next_single(info, root, keys[level], rkey, value_le);
out:
	exit_ro_spine(&spine);
	return r;
}
