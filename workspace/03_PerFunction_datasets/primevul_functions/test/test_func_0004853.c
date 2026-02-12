int btrfs_get_io_geometry(struct btrfs_fs_info *fs_info, struct extent_map *em,
			  enum btrfs_map_op op, u64 logical,
			  struct btrfs_io_geometry *io_geom)
{
	struct map_lookup *map;
	u64 len;
	u64 offset;
	u64 stripe_offset;
	u64 stripe_nr;
	u64 stripe_len;
	u64 raid56_full_stripe_start = (u64)-1;
	int data_stripes;

	ASSERT(op != BTRFS_MAP_DISCARD);

	map = em->map_lookup;

	offset = logical - em->start;

	stripe_len = map->stripe_len;

	stripe_nr = div64_u64(offset, stripe_len);

	stripe_offset = stripe_nr * stripe_len;
	if (offset < stripe_offset) {
		btrfs_crit(fs_info,
"stripe math has gone wrong, stripe_offset=%llu offset=%llu start=%llu logical=%llu stripe_len=%llu",
			stripe_offset, offset, em->start, logical, stripe_len);
		return -EINVAL;
	}


	stripe_offset = offset - stripe_offset;
	data_stripes = nr_data_stripes(map);

	if (map->type & BTRFS_BLOCK_GROUP_PROFILE_MASK) {
		u64 max_len = stripe_len - stripe_offset;


		if (map->type & BTRFS_BLOCK_GROUP_RAID56_MASK) {
			unsigned long full_stripe_len = stripe_len * data_stripes;
			raid56_full_stripe_start = offset;


			raid56_full_stripe_start = div64_u64(raid56_full_stripe_start,
					full_stripe_len);
			raid56_full_stripe_start *= full_stripe_len;


			if (op == BTRFS_MAP_WRITE) {
				max_len = stripe_len * data_stripes -
					  (offset - raid56_full_stripe_start);
			}
		}
		len = min_t(u64, em->len - offset, max_len);
	} else {
		len = em->len - offset;
	}

	io_geom->len = len;
	io_geom->offset = offset;
	io_geom->stripe_len = stripe_len;
	io_geom->stripe_nr = stripe_nr;
	io_geom->stripe_offset = stripe_offset;
	io_geom->raid56_stripe_offset = raid56_full_stripe_start;

	return 0;
}
