vortex_get_ethtool_stats(struct net_device *dev,
	struct ethtool_stats *stats, u64 *data)
{
	struct vortex_private *vp = netdev_priv(dev);
	void __iomem *ioaddr = vp->ioaddr;
	unsigned long flags;

	spin_lock_irqsave(&vp->lock, flags);
	update_stats(ioaddr, dev);
	spin_unlock_irqrestore(&vp->lock, flags);

	data[0] = vp->xstats.tx_deferred;
	data[1] = vp->xstats.tx_max_collisions;
	data[2] = vp->xstats.tx_multiple_collisions;
	data[3] = vp->xstats.tx_single_collisions;
	data[4] = vp->xstats.rx_bad_ssd;
}
