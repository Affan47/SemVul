static ssize_t traffic_class_show(struct netdev_queue *queue,
				  char *buf)
{
	struct net_device *dev = queue->dev;
	int index;
	int tc;

	if (!netif_is_multiqueue(dev))
		return -ENOENT;

	index = get_netdev_queue_index(queue);


	dev = netdev_get_tx_queue(dev, index)->sb_dev ? : dev;

	tc = netdev_txq_to_tc(dev, index);
	if (tc < 0)
		return -EINVAL;


	return dev->num_tc < 0 ? sprintf(buf, "%u%d\n", tc, dev->num_tc) :
				 sprintf(buf, "%u\n", tc);
}
