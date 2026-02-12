static u64 get_full_stripe_logical(struct btrfs_block_group_cache *cache,
				   u64 bytenr)
{
	u64 ret;


	WARN_ON_ONCE(cache->full_stripe_len >= U32_MAX);


	ret = div64_u64(bytenr - cache->key.objectid, cache->full_stripe_len) *
		cache->full_stripe_len + cache->key.objectid;
	return ret;
}
