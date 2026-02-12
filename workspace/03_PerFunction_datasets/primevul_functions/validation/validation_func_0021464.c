isdn_net_open(struct net_device *dev)
{
	int i;
	struct net_device *p;
	struct in_device *in_dev;


	netif_start_queue(dev);

	isdn_net_reset(dev);

	for (i = 0; i < ETH_ALEN - sizeof(u32); i++)
		dev->dev_addr[i] = 0xfc;
	if ((in_dev = dev->ip_ptr) != NULL) {


		struct in_ifaddr *ifa = in_dev->ifa_list;
		if (ifa != NULL)
			memcpy(dev->dev_addr+2, &ifa->ifa_local, 4);
	}


	if ((p = (((isdn_net_local *) dev->priv)->slave))) {
		while (p) {
			isdn_net_reset(p);
			p = (((isdn_net_local *) p->priv)->slave);
		}
	}
	isdn_lock_drivers();
	return 0;
}
