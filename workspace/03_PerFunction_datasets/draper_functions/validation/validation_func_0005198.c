rxq_process(struct net_device *dev, int budget)
{
	struct pxa168_eth_private *pep = netdev_priv(dev);
	struct net_device_stats *stats = &dev->stats;
	unsigned int received_packets = 0;
	struct sk_buff *skb;

	while (budget-- > 0) {
		int rx_next_curr_desc, rx_curr_desc, rx_used_desc;
		struct rx_desc *rx_desc;
		unsigned int cmd_sts;


		if (pep->rx_resource_err)
			break;
		rx_curr_desc = pep->rx_curr_desc_q;
		rx_used_desc = pep->rx_used_desc_q;
		rx_desc = &pep->p_rx_desc_area[rx_curr_desc];
		cmd_sts = rx_desc->cmd_sts;
		rmb();
		if (cmd_sts & (BUF_OWNED_BY_DMA))
			break;
		skb = pep->rx_skb[rx_curr_desc];
		pep->rx_skb[rx_curr_desc] = NULL;

		rx_next_curr_desc = (rx_curr_desc + 1) % pep->rx_ring_size;
		pep->rx_curr_desc_q = rx_next_curr_desc;


		if (rx_next_curr_desc == rx_used_desc)
			pep->rx_resource_err = 1;
		pep->rx_desc_count--;
		dma_unmap_single(NULL, rx_desc->buf_ptr,
				 rx_desc->buf_size,
				 DMA_FROM_DEVICE);
		received_packets++;


		stats->rx_packets++;
		stats->rx_bytes += rx_desc->byte_cnt;


		if (((cmd_sts & (RX_FIRST_DESC | RX_LAST_DESC)) !=
		     (RX_FIRST_DESC | RX_LAST_DESC))
		    || (cmd_sts & RX_ERROR)) {

			stats->rx_dropped++;
			if ((cmd_sts & (RX_FIRST_DESC | RX_LAST_DESC)) !=
			    (RX_FIRST_DESC | RX_LAST_DESC)) {
				if (net_ratelimit())
					netdev_err(dev,
						   "Rx pkt on multiple desc\n");
			}
			if (cmd_sts & RX_ERROR)
				stats->rx_errors++;
			dev_kfree_skb_irq(skb);
		} else {


			skb_put(skb, rx_desc->byte_cnt - 4);
			skb->protocol = eth_type_trans(skb, dev);
			netif_receive_skb(skb);
		}
	}

	rxq_refill(dev);
	return received_packets;
}
