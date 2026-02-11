cp_get_ethtool_stats (struct net_device *dev,
				  struct ethtool_stats *estats, u64 *tmp_stats)
{
	struct cp_private *cp = netdev_priv(dev);
	struct cp_dma_stats *nic_stats;
	dma_addr_t dma;
	int i;

	nic_stats = dma_alloc_coherent(&cp->pdev->dev, sizeof(*nic_stats),
				       &dma, GFP_KERNEL);
	if (!nic_stats)
		return;


	cpw32(StatsAddr + 4, (u64)dma >> 32);
	cpw32(StatsAddr, ((u64)dma & DMA_BIT_MASK(32)) | DumpStats);
	cpr32(StatsAddr);

	for (i = 0; i < 1000; i++) {
		if ((cpr32(StatsAddr) & DumpStats) == 0)
			break;
		udelay(10);
	}
	cpw32(StatsAddr, 0);
	cpw32(StatsAddr + 4, 0);
	cpr32(StatsAddr);

	i = 0;
	tmp_stats[i++] = le64_to_cpu(nic_stats->tx_ok);
	tmp_stats[i++] = le64_to_cpu(nic_stats->rx_ok);
	tmp_stats[i++] = le64_to_cpu(nic_stats->tx_err);
	tmp_stats[i++] = le32_to_cpu(nic_stats->rx_err);
	tmp_stats[i++] = le16_to_cpu(nic_stats->rx_fifo);
	tmp_stats[i++] = le16_to_cpu(nic_stats->frame_align);
	tmp_stats[i++] = le32_to_cpu(nic_stats->tx_ok_1col);
	tmp_stats[i++] = le32_to_cpu(nic_stats->tx_ok_mcol);
	tmp_stats[i++] = le64_to_cpu(nic_stats->rx_ok_phys);
	tmp_stats[i++] = le64_to_cpu(nic_stats->rx_ok_bcast);
	tmp_stats[i++] = le32_to_cpu(nic_stats->rx_ok_mcast);
	tmp_stats[i++] = le16_to_cpu(nic_stats->tx_abort);
	tmp_stats[i++] = le16_to_cpu(nic_stats->tx_underrun);
	tmp_stats[i++] = cp->cp_stats.rx_frags;
	BUG_ON(i != CP_NUM_STATS);

	dma_free_coherent(&cp->pdev->dev, sizeof(*nic_stats), nic_stats, dma);
}
