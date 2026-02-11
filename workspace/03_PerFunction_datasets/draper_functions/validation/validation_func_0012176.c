qlcnic_inetaddr_event(struct notifier_block *this,
		unsigned long event, void *ptr)
{
	struct qlcnic_adapter *adapter;
	struct net_device *dev;

	struct in_ifaddr *ifa = (struct in_ifaddr *)ptr;

	dev = ifa->ifa_dev ? ifa->ifa_dev->dev : NULL;

recheck:
	if (dev == NULL)
		goto done;

	if (dev->priv_flags & IFF_802_1Q_VLAN) {
		dev = vlan_dev_real_dev(dev);
		goto recheck;
	}

	if (!is_qlcnic_netdev(dev))
		goto done;

	adapter = netdev_priv(dev);

	if (!adapter)
		goto done;

	if (!test_bit(__QLCNIC_DEV_UP, &adapter->state))
		goto done;

	switch (event) {
	case NETDEV_UP:
		qlcnic_config_ipaddr(adapter, ifa->ifa_address, QLCNIC_IP_UP);

		break;
	case NETDEV_DOWN:
		qlcnic_config_ipaddr(adapter, ifa->ifa_address, QLCNIC_IP_DOWN);

		break;
	default:
		break;
	}

done:
	return NOTIFY_DONE;
}
