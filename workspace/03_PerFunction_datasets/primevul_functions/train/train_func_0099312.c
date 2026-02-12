*/
static void netdev_release(struct device *d)
{
	struct net_device *dev = to_net_dev(d);

	BUG_ON(dev->reg_state != NETREG_RELEASED);


	kfree(rcu_access_pointer(dev->ifalias));
	netdev_freemem(dev);
}
