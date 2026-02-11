gem_setup_multicast(struct gem *gp)
{
	u32 rxcfg = 0;
	int i;

	if ((gp->dev->flags & IFF_ALLMULTI) ||
	    (netdev_mc_count(gp->dev) > 256)) {
	    	for (i=0; i<16; i++)
			writel(0xffff, gp->regs + MAC_HASH0 + (i << 2));
		rxcfg |= MAC_RXCFG_HFE;
	} else if (gp->dev->flags & IFF_PROMISC) {
		rxcfg |= MAC_RXCFG_PROM;
	} else {
		u16 hash_table[16];
		u32 crc;
		struct netdev_hw_addr *ha;
		int i;

		memset(hash_table, 0, sizeof(hash_table));
		netdev_for_each_mc_addr(ha, gp->dev) {
			crc = ether_crc_le(6, ha->addr);
			crc >>= 24;
			hash_table[crc >> 4] |= 1 << (15 - (crc & 0xf));
		}
	    	for (i=0; i<16; i++)
			writel(hash_table[i], gp->regs + MAC_HASH0 + (i << 2));
		rxcfg |= MAC_RXCFG_HFE;
	}

	return rxcfg;
}
