sb1000_close(struct net_device *dev)
{
	int i;
	int ioaddr[2];
	struct sb1000_private *lp = netdev_priv(dev);

	if (sb1000_debug > 2)
		printk(KERN_DEBUG "%s: Shutting down sb1000.\n", dev->name);

	netif_stop_queue(dev);

	ioaddr[0] = dev->base_addr;

	ioaddr[1] = dev->mem_start;

	free_irq(dev->irq, dev);

	release_region(ioaddr[1], SB1000_IO_EXTENT);
	release_region(ioaddr[0], SB1000_IO_EXTENT);


	for (i=0; i<4; i++) {
		if (lp->rx_skb[i]) {
			dev_kfree_skb(lp->rx_skb[i]);
		}
	}
	return 0;
}
