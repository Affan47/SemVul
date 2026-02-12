static void ll_temac_recv(struct net_device *ndev)
{
	struct temac_local *lp = netdev_priv(ndev);
	unsigned long flags;
	int rx_bd;
	bool update_tail = false;

	spin_lock_irqsave(&lp->rx_lock, flags);


	do {
		struct cdmac_bd *bd = &lp->rx_bd_v[lp->rx_bd_ci];
		struct sk_buff *skb = lp->rx_skb[lp->rx_bd_ci];
		unsigned int bdstat = be32_to_cpu(bd->app0);
		int length;


		if (!skb)
			break;


		if (!(bdstat & STS_CTRL_APP0_CMPLT))
			break;

		dma_unmap_single(ndev->dev.parent, be32_to_cpu(bd->phys),
				 XTE_MAX_JUMBO_FRAME_SIZE, DMA_FROM_DEVICE);

		bd->phys = 0;
		bd->len = 0;

		length = be32_to_cpu(bd->app4) & 0x3FFF;
		skb_put(skb, length);
		skb->protocol = eth_type_trans(skb, ndev);
		skb_checksum_none_assert(skb);


		if (((lp->temac_features & TEMAC_FEATURE_RX_CSUM) != 0) &&
		    (skb->protocol == htons(ETH_P_IP)) &&
		    (skb->len > 64)) {


			skb->csum = htons(be32_to_cpu(bd->app3) & 0xFFFF);
			skb->ip_summed = CHECKSUM_COMPLETE;
		}

		if (!skb_defer_rx_timestamp(skb))
			netif_rx(skb);

		lp->rx_skb[lp->rx_bd_ci] = NULL;

		ndev->stats.rx_packets++;
		ndev->stats.rx_bytes += length;

		rx_bd = lp->rx_bd_ci;
		if (++lp->rx_bd_ci >= lp->rx_bd_num)
			lp->rx_bd_ci = 0;
	} while (rx_bd != lp->rx_bd_tail);


	if (ll_temac_recv_buffers_available(lp) < lp->coalesce_count_rx)
		schedule_delayed_work(&lp->restart_work, HZ / 1000);


	while (1) {
		struct sk_buff *skb;
		struct cdmac_bd *bd;
		dma_addr_t skb_dma_addr;

		rx_bd = lp->rx_bd_tail + 1;
		if (rx_bd >= lp->rx_bd_num)
			rx_bd = 0;
		bd = &lp->rx_bd_v[rx_bd];

		if (bd->phys)
			break;

		skb = netdev_alloc_skb_ip_align(ndev, XTE_MAX_JUMBO_FRAME_SIZE);
		if (!skb) {
			dev_warn(&ndev->dev, "skb alloc failed\n");
			break;
		}

		skb_dma_addr = dma_map_single(ndev->dev.parent, skb->data,
					      XTE_MAX_JUMBO_FRAME_SIZE,
					      DMA_FROM_DEVICE);
		if (WARN_ON_ONCE(dma_mapping_error(ndev->dev.parent,
						   skb_dma_addr))) {
			dev_kfree_skb_any(skb);
			break;
		}

		bd->phys = cpu_to_be32(skb_dma_addr);
		bd->len = cpu_to_be32(XTE_MAX_JUMBO_FRAME_SIZE);
		bd->app0 = cpu_to_be32(STS_CTRL_APP0_IRQONEND);
		lp->rx_skb[rx_bd] = skb;

		lp->rx_bd_tail = rx_bd;
		update_tail = true;
	}


	if (update_tail) {
		lp->dma_out(lp, RX_TAILDESC_PTR,
			lp->rx_bd_p + sizeof(*lp->rx_bd_v) * lp->rx_bd_tail);
	}

	spin_unlock_irqrestore(&lp->rx_lock, flags);
}
