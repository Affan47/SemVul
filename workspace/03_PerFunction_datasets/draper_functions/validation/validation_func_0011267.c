fjes_hw_alloc_shared_status_region(struct fjes_hw *hw)
{
	size_t size;

	size = sizeof(struct fjes_device_shared_info) +
	    (sizeof(u8) * hw->max_epid);
	hw->hw_info.share = kzalloc(size, GFP_KERNEL);
	if (!hw->hw_info.share)
		return -ENOMEM;

	hw->hw_info.share->epnum = hw->max_epid;

	return 0;
}
