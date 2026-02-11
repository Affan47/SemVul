do_set_multicast_list(struct net_device *dev)
{
	long e8390_base = dev->base_addr;
	int i;
	struct ei_device *ei_local = netdev_priv(dev);

	if (!(dev->flags&(IFF_PROMISC|IFF_ALLMULTI))) {
		memset(ei_local->mcfilter, 0, 8);
		if (!netdev_mc_empty(dev))
			make_mc_bits(ei_local->mcfilter, dev);
	} else {

		memset(ei_local->mcfilter, 0xFF, 8);
	}

	outb_p(E8390_NODMA + E8390_PAGE1, e8390_base + E8390_CMD);
	for(i = 0; i < 8; i++)
	{
		outb_p(ei_local->mcfilter[i], e8390_base + EN1_MULT_SHIFT(i));
	}
	outb_p(E8390_NODMA + E8390_PAGE0, e8390_base + E8390_CMD);

  	if(dev->flags&IFF_PROMISC)
  		outb_p(E8390_RXCONFIG | 0x58, e8390_base + EN0_RXCR);
	else if (dev->flags & IFF_ALLMULTI || !netdev_mc_empty(dev))
  		outb_p(E8390_RXCONFIG | 0x48, e8390_base + EN0_RXCR);
  	else
  		outb_p(E8390_RXCONFIG | 0x40, e8390_base + EN0_RXCR);

	outb_p(E8390_NODMA+E8390_PAGE0+E8390_START, e8390_base+E8390_CMD);
}
