int netdev_bind_sb_channel_queue(struct net_device *dev,
				 struct net_device *sb_dev,
				 u8 tc, u16 count, u16 offset)
{

	if (sb_dev->num_tc >= 0 || tc >= dev->num_tc)
		return -EINVAL;


	if ((offset + count) > dev->real_num_tx_queues)
		return -EINVAL;


	sb_dev->tc_to_txq[tc].count = count;
	sb_dev->tc_to_txq[tc].offset = offset;


	while (count--)
		netdev_get_tx_queue(dev, count + offset)->sb_dev = sb_dev;

	return 0;
}
