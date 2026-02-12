static int i40e_addr_unsync(struct net_device *netdev, const u8 *addr)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_vsi *vsi = np->vsi;


	if (ether_addr_equal(addr, netdev->dev_addr))
		return 0;

	i40e_del_mac_filter(vsi, addr);

	return 0;
}
