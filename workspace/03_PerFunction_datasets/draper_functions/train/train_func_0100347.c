x25_asy_open(struct net_device *dev)
{
	struct x25_asy *sl = netdev_priv(dev);
	unsigned long len;
	int err;

	if (sl->tty == NULL)
		return -ENODEV;


	len = dev->mtu * 2;

	sl->rbuff = kmalloc(len + 4, GFP_KERNEL);
	if (sl->rbuff == NULL)
		goto norbuff;
	sl->xbuff = kmalloc(len + 4, GFP_KERNEL);
	if (sl->xbuff == NULL)
		goto noxbuff;

	sl->buffsize = len;
	sl->rcount   = 0;
	sl->xleft    = 0;
	sl->flags   &= (1 << SLF_INUSE);

	netif_start_queue(dev);


	err = lapb_register(dev, &x25_asy_callbacks);
	if (err == LAPB_OK)
		return 0;


	kfree(sl->xbuff);
noxbuff:
	kfree(sl->rbuff);
norbuff:
	return -ENOMEM;
}
