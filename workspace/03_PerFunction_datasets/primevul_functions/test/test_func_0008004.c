static void mctp_serial_setup(struct net_device *ndev)
{
	ndev->type = ARPHRD_MCTP;


	ndev->mtu = MCTP_SERIAL_MTU;
	ndev->max_mtu = MCTP_SERIAL_MTU;
	ndev->min_mtu = MCTP_SERIAL_MTU;

	ndev->hard_header_len = 0;
	ndev->addr_len = 0;
	ndev->tx_queue_len = DEFAULT_TX_QUEUE_LEN;
	ndev->flags = IFF_NOARP;
	ndev->netdev_ops = &mctp_serial_netdev_ops;
	ndev->needs_free_netdev = true;
}
