wait_for_link(struct net_device *dev)
{
    struct de4x5_private *lp = netdev_priv(dev);

    if (lp->timeout < 0) {
	lp->timeout = 1;
    }

    if (lp->timeout--) {
	return TIMER_CB;
    } else {
	lp->timeout = -1;
    }

    return 0;
}
