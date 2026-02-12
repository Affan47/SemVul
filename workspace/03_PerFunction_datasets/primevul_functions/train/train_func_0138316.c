static void ql3xxx_tx_timeout(struct net_device *ndev)
{
	struct ql3_adapter *qdev = netdev_priv(ndev);

	netdev_err(ndev, "Resetting...\n");


	netif_stop_queue(ndev);


	queue_delayed_work(qdev->workqueue, &qdev->tx_timeout_work, 0);
}
