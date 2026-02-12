static u64 dev_extent_search_start(struct btrfs_device *device, u64 start)
{
	switch (device->fs_devices->chunk_alloc_policy) {
	case BTRFS_CHUNK_ALLOC_REGULAR:


		return max_t(u64, start, SZ_1M);
	case BTRFS_CHUNK_ALLOC_ZONED:


		return ALIGN(start, device->zone_info->zone_size);
	default:
		BUG();
	}
}
