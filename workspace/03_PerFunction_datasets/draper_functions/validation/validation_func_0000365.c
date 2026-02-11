iwl_pcie_rx_free_rba(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	struct iwl_rb_allocator *rba = &trans_pcie->rba;
	int i;

	lockdep_assert_held(&rba->lock);

	for (i = 0; i < RX_POOL_SIZE; i++) {
		if (!rba->pool[i].page)
			continue;
		dma_unmap_page(trans->dev, rba->pool[i].page_dma,
			       PAGE_SIZE << trans_pcie->rx_page_order,
			       DMA_FROM_DEVICE);
		__free_pages(rba->pool[i].page, trans_pcie->rx_page_order);
		rba->pool[i].page = NULL;
	}
}
