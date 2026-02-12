int netdev_set_sb_channel(struct net_device *dev, u16 channel)
{

	if (netif_is_multiqueue(dev))
		return -ENODEV;


	if (channel > S16_MAX)
		return -EINVAL;

	dev->num_tc = -channel;

	return 0;
}
