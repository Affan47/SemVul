ns83820_reset(struct nic *nic)
{
	unsigned i;
	DBG("ns83820_reset\n");

	writel(0, ns->base + PQCR);

	ns83820_setup_rx(nic);

	for (i = 0; i < NR_TX_DESC; i++) {
		tx_ring[i].link = 0;
		tx_ring[i].bufptr = 0;
		tx_ring[i].cmdsts = cpu_to_le32(0);
		tx_ring[i].extsts = cpu_to_le32(0);
	}

	ns->tx_idx = 0;
	ns->tx_done_idx = 0;
	writel(0, ns->base + TXDP_HI);
	return;
}
