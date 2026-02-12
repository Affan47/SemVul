static int arc_emac_open(struct net_device *ndev)
{
	struct arc_emac_priv *priv = netdev_priv(ndev);
	struct phy_device *phy_dev = priv->phy_dev;
	int i;

	phy_dev->autoneg = AUTONEG_ENABLE;
	phy_dev->speed = 0;
	phy_dev->duplex = 0;
	phy_dev->advertising &= phy_dev->supported;

	priv->last_rx_bd = 0;


	for (i = 0; i < RX_BD_NUM; i++) {
		dma_addr_t addr;
		unsigned int *last_rx_bd = &priv->last_rx_bd;
		struct arc_emac_bd *rxbd = &priv->rxbd[*last_rx_bd];
		struct buffer_state *rx_buff = &priv->rx_buff[*last_rx_bd];

		rx_buff->skb = netdev_alloc_skb_ip_align(ndev,
							 EMAC_BUFFER_SIZE);
		if (unlikely(!rx_buff->skb))
			return -ENOMEM;

		addr = dma_map_single(&ndev->dev, (void *)rx_buff->skb->data,
				      EMAC_BUFFER_SIZE, DMA_FROM_DEVICE);
		if (dma_mapping_error(&ndev->dev, addr)) {
			netdev_err(ndev, "cannot dma map\n");
			dev_kfree_skb(rx_buff->skb);
			return -ENOMEM;
		}
		dma_unmap_addr_set(rx_buff, addr, addr);
		dma_unmap_len_set(rx_buff, len, EMAC_BUFFER_SIZE);

		rxbd->data = cpu_to_le32(addr);


		wmb();


		rxbd->info = cpu_to_le32(FOR_EMAC | EMAC_BUFFER_SIZE);

		*last_rx_bd = (*last_rx_bd + 1) % RX_BD_NUM;
	}


	memset(priv->txbd, 0, TX_RING_SZ);


	arc_reg_set(priv, R_LAFL, 0);
	arc_reg_set(priv, R_LAFH, 0);


	arc_reg_set(priv, R_RX_RING, (unsigned int)priv->rxbd_dma);
	arc_reg_set(priv, R_TX_RING, (unsigned int)priv->txbd_dma);


	arc_reg_set(priv, R_ENABLE, RXINT_MASK | TXINT_MASK | ERR_MASK);


	arc_reg_set(priv, R_CTRL,
		     (RX_BD_NUM << 24) |
		     (TX_BD_NUM << 16) |
		     TXRN_MASK | RXRN_MASK);

	napi_enable(&priv->napi);


	arc_reg_or(priv, R_CTRL, EN_MASK);

	phy_start_aneg(priv->phy_dev);

	netif_start_queue(ndev);

	return 0;
}
