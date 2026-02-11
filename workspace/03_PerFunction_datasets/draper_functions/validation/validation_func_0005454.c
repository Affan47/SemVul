xgene_chan_xfer_request(struct xgene_dma_chan *chan,
				    struct xgene_dma_desc_sw *desc_sw)
{
	struct xgene_dma_ring *ring = &chan->tx_ring;
	struct xgene_dma_desc_hw *desc_hw;


	desc_hw = &ring->desc_hw[ring->head];


	if (++ring->head == ring->slots)
		ring->head = 0;


	memcpy(desc_hw, &desc_sw->desc1, sizeof(*desc_hw));


	if (desc_sw->flags & XGENE_DMA_FLAG_64B_DESC) {
		desc_hw = &ring->desc_hw[ring->head];

		if (++ring->head == ring->slots)
			ring->head = 0;

		memcpy(desc_hw, &desc_sw->desc2, sizeof(*desc_hw));
	}


	chan->pending += ((desc_sw->flags &
			  XGENE_DMA_FLAG_64B_DESC) ? 2 : 1);


	iowrite32((desc_sw->flags & XGENE_DMA_FLAG_64B_DESC) ?
		  2 : 1, ring->cmd);
}
