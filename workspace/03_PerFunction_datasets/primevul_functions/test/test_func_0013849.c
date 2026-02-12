static int ax_open(struct net_device *dev)
{
	struct mkiss *ax = netdev_priv(dev);
	unsigned long len;

	if (ax->tty == NULL)
		return -ENODEV;


	len = dev->mtu * 2;


	if (len < 576 * 2)
		len = 576 * 2;

	if ((ax->rbuff = kmalloc(len + 4, GFP_KERNEL)) == NULL)
		goto norbuff;

	if ((ax->xbuff = kmalloc(len + 4, GFP_KERNEL)) == NULL)
		goto noxbuff;

	ax->mtu	     = dev->mtu + 73;
	ax->buffsize = len;
	ax->rcount   = 0;
	ax->xleft    = 0;

	ax->flags   &= (1 << AXF_INUSE);

	spin_lock_init(&ax->buflock);

	return 0;

noxbuff:
	kfree(ax->rbuff);

norbuff:
	return -ENOMEM;
}
