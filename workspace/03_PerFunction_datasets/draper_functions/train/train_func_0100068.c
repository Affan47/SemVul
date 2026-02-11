unmap_partial_tx_skb(struct happy_meal *hp, u32 first_mapping,
				 u32 first_len, u32 first_entry, u32 entry)
{
	struct happy_meal_txd *txbase = &hp->happy_block->happy_meal_txd[0];

	dma_unmap_single(hp->dma_dev, first_mapping, first_len, DMA_TO_DEVICE);

	first_entry = NEXT_TX(first_entry);
	while (first_entry != entry) {
		struct happy_meal_txd *this = &txbase[first_entry];
		u32 addr, len;

		addr = hme_read_desc32(hp, &this->tx_addr);
		len = hme_read_desc32(hp, &this->tx_flags);
		len &= TXFLAG_SIZE;
		dma_unmap_page(hp->dma_dev, addr, len, DMA_TO_DEVICE);
	}
}
