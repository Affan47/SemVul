ql_set_coalesce(struct net_device *ndev, struct ethtool_coalesce *c)
{
	struct ql_adapter *qdev = netdev_priv(ndev);


	if (c->rx_coalesce_usecs > qdev->rx_ring_size / 2)
		return -EINVAL;

	if (c->rx_max_coalesced_frames > MAX_INTER_FRAME_WAIT)
		return -EINVAL;
	if (c->tx_coalesce_usecs > qdev->tx_ring_size / 2)
		return -EINVAL;
	if (c->tx_max_coalesced_frames > MAX_INTER_FRAME_WAIT)
		return -EINVAL;


	if (qdev->rx_coalesce_usecs == c->rx_coalesce_usecs &&
	    qdev->tx_coalesce_usecs == c->tx_coalesce_usecs &&
	    qdev->rx_max_coalesced_frames == c->rx_max_coalesced_frames &&
	    qdev->tx_max_coalesced_frames == c->tx_max_coalesced_frames)
		return 0;

	qdev->rx_coalesce_usecs = c->rx_coalesce_usecs;
	qdev->tx_coalesce_usecs = c->tx_coalesce_usecs;
	qdev->rx_max_coalesced_frames = c->rx_max_coalesced_frames;
	qdev->tx_max_coalesced_frames = c->tx_max_coalesced_frames;

	return ql_update_ring_coalescing(qdev);
}
