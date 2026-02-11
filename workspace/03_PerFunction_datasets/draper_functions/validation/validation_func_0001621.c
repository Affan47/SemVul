netdev_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	struct hamachi_private *np = netdev_priv(dev);
	struct mii_ioctl_data *data = if_mii(rq);
	int rc;

	if (!netif_running(dev))
		return -EINVAL;

	if (cmd == (SIOCDEVPRIVATE+3)) {
		u32 *d = (u32 *)&rq->ifr_ifru;


		if (!capable(CAP_NET_ADMIN))
			return -EPERM;
		writel(d[0], np->base + TxIntrCtrl);
		writel(d[1], np->base + RxIntrCtrl);
		printk(KERN_NOTICE "%s: tx %08x, rx %08x intr\n", dev->name,
		  (u32) readl(np->base + TxIntrCtrl),
		  (u32) readl(np->base + RxIntrCtrl));
		rc = 0;
	}

	else {
		spin_lock_irq(&np->lock);
		rc = generic_mii_ioctl(&np->mii_if, data, cmd, NULL);
		spin_unlock_irq(&np->lock);
	}

	return rc;
}
