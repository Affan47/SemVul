t1_change_mtu(struct net_device *dev, int new_mtu)
{
	int ret;
	struct adapter *adapter = dev->ml_priv;
	struct cmac *mac = adapter->port[dev->if_port].mac;

	if (!mac->ops->set_mtu)
		return -EOPNOTSUPP;
	if (new_mtu < 68)
		return -EINVAL;
	if ((ret = mac->ops->set_mtu(mac, new_mtu)))
		return ret;
	dev->mtu = new_mtu;
	return 0;
}
