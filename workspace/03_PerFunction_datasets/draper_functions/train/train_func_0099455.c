most_nd_stop(struct net_device *dev)
{
	struct net_dev_context *nd = dev->ml_priv;

	netdev_info(dev, "stop net device\n");

	BUG_ON(nd->dev != dev);
	netif_stop_queue(dev);

	if (nd->channels_opened) {
		most_stop_channel(nd->iface, nd->rx.ch_id, &aim);
		most_stop_channel(nd->iface, nd->tx.ch_id, &aim);
		nd->channels_opened = false;
	}

	return 0;
}
