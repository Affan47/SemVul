msb_cache_discard(struct msb_data *msb)
{
	if (msb->cache_block_lba == MS_BLOCK_INVALID)
		return;

	del_timer_sync(&msb->cache_flush_timer);

	dbg_verbose("Discarding the write cache");
	msb->cache_block_lba = MS_BLOCK_INVALID;
	bitmap_zero(&msb->valid_cache_bitmap, msb->pages_in_block);
}
