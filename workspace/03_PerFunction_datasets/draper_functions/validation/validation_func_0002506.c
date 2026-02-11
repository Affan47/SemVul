ks8842_update_rx_counters(struct net_device *netdev, u32 status,
	int len)
{
	netdev_dbg(netdev, "RX packet, len: %d\n", len);

	netdev->stats.rx_packets++;
	netdev->stats.rx_bytes += len;
	if (status & RXSR_MULTICAST)
		netdev->stats.multicast++;
}
