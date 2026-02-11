set_multicast(struct nic *nic)
{

	u8 *base = (u8 *) BASE;
	u32 addr[2];
	u32 mask[2];
	u32 pff;
	u32 alwaysOff[2];
	u32 alwaysOn[2];

	memset(addr, 0, sizeof(addr));
	memset(mask, 0, sizeof(mask));

	pff = NVREG_PFF_MYADDR;

	alwaysOn[0] = alwaysOn[1] = alwaysOff[0] = alwaysOff[1] = 0;

	addr[0] = alwaysOn[0];
	addr[1] = alwaysOn[1];
	mask[0] = alwaysOn[0] | alwaysOff[0];
	mask[1] = alwaysOn[1] | alwaysOff[1];

	addr[0] |= NVREG_MCASTADDRA_FORCE;
	pff |= NVREG_PFF_ALWAYS;
	stop_rx();
	writel(addr[0], base + NvRegMulticastAddrA);
	writel(addr[1], base + NvRegMulticastAddrB);
	writel(mask[0], base + NvRegMulticastMaskA);
	writel(mask[1], base + NvRegMulticastMaskB);
	writel(pff, base + NvRegPacketFilterFlags);
	start_rx(nic);
}
