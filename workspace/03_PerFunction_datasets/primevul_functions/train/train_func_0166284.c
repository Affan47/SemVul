static struct inet6_dev *addrconf_add_dev(struct net_device *dev)
{
	struct inet6_dev *idev;

	ASSERT_RTNL();

	if ((idev = ipv6_find_idev(dev)) == NULL)
		return NULL;


	addrconf_add_mroute(dev);


	addrconf_add_lroute(dev);
	return idev;
}
