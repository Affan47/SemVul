i40e_get_ts_info(struct net_device *dev,
			    struct ethtool_ts_info *info)
{
	struct i40e_pf *pf = i40e_netdev_to_pf(dev);


	if (!(pf->flags & I40E_FLAG_PTP))
		return ethtool_op_get_ts_info(dev, info);

	info->so_timestamping = SOF_TIMESTAMPING_TX_SOFTWARE |
				SOF_TIMESTAMPING_RX_SOFTWARE |
				SOF_TIMESTAMPING_SOFTWARE |
				SOF_TIMESTAMPING_TX_HARDWARE |
				SOF_TIMESTAMPING_RX_HARDWARE |
				SOF_TIMESTAMPING_RAW_HARDWARE;

	if (pf->ptp_clock)
		info->phc_index = ptp_clock_index(pf->ptp_clock);
	else
		info->phc_index = -1;

	info->tx_types = BIT(HWTSTAMP_TX_OFF) | BIT(HWTSTAMP_TX_ON);

	info->rx_filters = BIT(HWTSTAMP_FILTER_NONE) |
			   BIT(HWTSTAMP_FILTER_PTP_V1_L4_EVENT) |
			   BIT(HWTSTAMP_FILTER_PTP_V2_EVENT);

	return 0;
}
