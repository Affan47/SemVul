qlcnic_alloc_rx_skb(struct qlcnic_adapter *adapter,
			       struct qlcnic_host_rds_ring *rds_ring,
			       struct qlcnic_rx_buffer *buffer)
{
	struct sk_buff *skb;
	dma_addr_t dma;
	struct pci_dev *pdev = adapter->pdev;

	skb = netdev_alloc_skb(adapter->netdev, rds_ring->skb_size);
	if (!skb) {
		adapter->stats.skb_alloc_failure++;
		return -ENOMEM;
	}

	skb_reserve(skb, NET_IP_ALIGN);
	dma = pci_map_single(pdev, skb->data,
			     rds_ring->dma_size, PCI_DMA_FROMDEVICE);

	if (pci_dma_mapping_error(pdev, dma)) {
		adapter->stats.rx_dma_map_error++;
		dev_kfree_skb_any(skb);
		return -ENOMEM;
	}

	buffer->skb = skb;
	buffer->dma = dma;

	return 0;
}
