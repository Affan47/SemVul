static void ip6_tnl_add_linklocal(struct inet6_dev *idev)
{
	struct net_device *link_dev;
	struct net *net = dev_net(idev->dev);


	if (idev->dev->iflink &&
	    (link_dev = __dev_get_by_index(net, idev->dev->iflink))) {
		if (!ipv6_inherit_linklocal(idev, link_dev))
			return;
	}

	for_each_netdev(net, link_dev) {
		if (!ipv6_inherit_linklocal(idev, link_dev))
			return;
	}
	pr_debug("init ip6-ip6: add_linklocal failed\n");
}
