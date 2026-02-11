ixgbe_rss_indir_tbl_entries(struct ixgbe_adapter *adapter)
{
	if (adapter->hw.mac.type < ixgbe_mac_X550)
		return 128;
	else if (adapter->flags & IXGBE_FLAG_SRIOV_ENABLED)
		return 64;
	else
		return 512;
}
