netxen_nic_enable_mcast_filter(struct netxen_adapter *adapter)
{
	u32	val = 0;
	u16 port = adapter->physical_port;
	u8 *addr = adapter->mac_addr;

	if (adapter->mc_enabled)
		return 0;

	val = NXRD32(adapter, NETXEN_MAC_ADDR_CNTL_REG);
	val |= (1UL << (28+port));
	NXWR32(adapter, NETXEN_MAC_ADDR_CNTL_REG, val);


	val = 0xffffff;
	NXWR32(adapter, NETXEN_UNICAST_ADDR(port, 0), val);
	NXWR32(adapter, NETXEN_UNICAST_ADDR(port, 0)+4, val);


	val = MAC_HI(addr);
	NXWR32(adapter, NETXEN_UNICAST_ADDR(port, 1), val);
	val = MAC_LO(addr);
	NXWR32(adapter, NETXEN_UNICAST_ADDR(port, 1)+4, val);

	adapter->mc_enabled = 1;
	return 0;
}
