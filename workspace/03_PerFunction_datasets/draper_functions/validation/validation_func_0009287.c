fjn_open(struct net_device *dev)
{
    struct local_info *lp = netdev_priv(dev);
    struct pcmcia_device *link = lp->p_dev;

    pr_debug("fjn_open('%s').\n", dev->name);

    if (!pcmcia_dev_present(link))
	return -ENODEV;

    link->open++;

    fjn_reset(dev);

    lp->tx_started = 0;
    lp->tx_queue = 0;
    lp->tx_queue_len = 0;
    lp->open_time = jiffies;
    netif_start_queue(dev);

    return 0;
}
