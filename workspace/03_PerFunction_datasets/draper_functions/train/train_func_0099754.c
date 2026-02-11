b44_get_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	struct b44 *bp = netdev_priv(dev);

	wol->supported = WAKE_MAGIC;
	if (bp->flags & B44_FLAG_WOL_ENABLE)
		wol->wolopts = WAKE_MAGIC;
	else
		wol->wolopts = 0;
	memset(&wol->sopass, 0, sizeof(wol->sopass));
}
