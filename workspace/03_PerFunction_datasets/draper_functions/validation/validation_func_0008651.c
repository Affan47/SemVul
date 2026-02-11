atl1c_configure(struct atl1c_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	int num;

	atl1c_init_ring_ptrs(adapter);
	atl1c_set_multi(netdev);
	atl1c_restore_vlan(adapter);

	num = atl1c_alloc_rx_buffer(adapter);
	if (unlikely(num == 0))
		return -ENOMEM;

	if (atl1c_configure_mac(adapter))
		return -EIO;

	return 0;
}
