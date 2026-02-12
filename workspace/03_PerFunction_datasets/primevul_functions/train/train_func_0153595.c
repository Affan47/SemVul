static void temac_device_reset(struct net_device *ndev)
{
	struct temac_local *lp = netdev_priv(ndev);
	u32 timeout;
	u32 val;
	unsigned long flags;


	dev_dbg(&ndev->dev, "%s()\n", __func__);


	temac_indirect_out32(lp, XTE_RXC1_OFFSET, XTE_RXC1_RXRST_MASK);
	timeout = 1000;
	while (temac_indirect_in32(lp, XTE_RXC1_OFFSET) & XTE_RXC1_RXRST_MASK) {
		udelay(1);
		if (--timeout == 0) {
			dev_err(&ndev->dev,
				"temac_device_reset RX reset timeout!!\n");
			break;
		}
	}


	temac_indirect_out32(lp, XTE_TXC_OFFSET, XTE_TXC_TXRST_MASK);
	timeout = 1000;
	while (temac_indirect_in32(lp, XTE_TXC_OFFSET) & XTE_TXC_TXRST_MASK) {
		udelay(1);
		if (--timeout == 0) {
			dev_err(&ndev->dev,
				"temac_device_reset TX reset timeout!!\n");
			break;
		}
	}


	spin_lock_irqsave(lp->indirect_lock, flags);
	val = temac_indirect_in32_locked(lp, XTE_RXC1_OFFSET);
	temac_indirect_out32_locked(lp, XTE_RXC1_OFFSET,
				    val & ~XTE_RXC1_RXEN_MASK);
	spin_unlock_irqrestore(lp->indirect_lock, flags);


	lp->dma_out(lp, DMA_CONTROL_REG, DMA_CONTROL_RST);
	timeout = 1000;
	while (lp->dma_in(lp, DMA_CONTROL_REG) & DMA_CONTROL_RST) {
		udelay(1);
		if (--timeout == 0) {
			dev_err(&ndev->dev,
				"temac_device_reset DMA reset timeout!!\n");
			break;
		}
	}
	lp->dma_out(lp, DMA_CONTROL_REG, DMA_TAIL_ENABLE);

	if (temac_dma_bd_init(ndev)) {
		dev_err(&ndev->dev,
				"temac_device_reset descriptor allocation failed\n");
	}

	spin_lock_irqsave(lp->indirect_lock, flags);
	temac_indirect_out32_locked(lp, XTE_RXC0_OFFSET, 0);
	temac_indirect_out32_locked(lp, XTE_RXC1_OFFSET, 0);
	temac_indirect_out32_locked(lp, XTE_TXC_OFFSET, 0);
	temac_indirect_out32_locked(lp, XTE_FCC_OFFSET, XTE_FCC_RXFLO_MASK);
	spin_unlock_irqrestore(lp->indirect_lock, flags);


	temac_setoptions(ndev,
			 lp->options & ~(XTE_OPTION_TXEN | XTE_OPTION_RXEN));

	temac_do_set_mac_address(ndev);


	temac_set_multicast_list(ndev);
	if (temac_setoptions(ndev, lp->options))
		dev_err(&ndev->dev, "Error setting TEMAC options\n");


	netif_trans_update(ndev);
}
