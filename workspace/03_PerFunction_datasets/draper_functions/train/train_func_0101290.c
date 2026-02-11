ixgb_set_settings(struct net_device *netdev, struct ethtool_cmd *ecmd)
{
	struct ixgb_adapter *adapter = netdev_priv(netdev);
	u32 speed = ethtool_cmd_speed(ecmd);

	if (ecmd->autoneg == AUTONEG_ENABLE ||
	    (speed + ecmd->duplex != SPEED_10000 + DUPLEX_FULL))
		return -EINVAL;

	if (netif_running(adapter->netdev)) {
		ixgb_down(adapter, true);
		ixgb_reset(adapter);
		ixgb_up(adapter);
		ixgb_set_speed_duplex(netdev);
	} else
		ixgb_reset(adapter);

	return 0;
}
