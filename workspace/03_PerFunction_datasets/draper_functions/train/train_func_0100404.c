xgene_dma_alloc_chan_resources(struct dma_chan *dchan)
{
	struct xgene_dma_chan *chan = to_dma_chan(dchan);


	if (chan->desc_pool)
		return 1;

	chan->desc_pool = dma_pool_create(chan->name, chan->dev,
					  sizeof(struct xgene_dma_desc_sw),
					  0, 0);
	if (!chan->desc_pool) {
		chan_err(chan, "Failed to allocate descriptor pool\n");
		return -ENOMEM;
	}

	chan_dbg(chan, "Allocate descripto pool\n");

	return 1;
}
