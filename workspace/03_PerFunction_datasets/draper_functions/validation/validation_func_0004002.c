xgene_dma_async_register(struct xgene_dma *pdma, int id)
{
	struct xgene_dma_chan *chan = &pdma->chan[id];
	struct dma_device *dma_dev = &pdma->dma_dev[id];
	int ret;

	chan->dma_chan.device = dma_dev;

	spin_lock_init(&chan->lock);
	INIT_LIST_HEAD(&chan->ld_pending);
	INIT_LIST_HEAD(&chan->ld_running);
	INIT_LIST_HEAD(&chan->ld_completed);
	tasklet_init(&chan->tasklet, xgene_dma_tasklet_cb,
		     (unsigned long)chan);

	chan->pending = 0;
	chan->desc_pool = NULL;
	dma_cookie_init(&chan->dma_chan);


	xgene_dma_set_caps(chan, dma_dev);


	INIT_LIST_HEAD(&dma_dev->channels);
	list_add_tail(&chan->dma_chan.device_node, &dma_dev->channels);


	ret = dma_async_device_register(dma_dev);
	if (ret) {
		chan_err(chan, "Failed to register async device %d", ret);
		tasklet_kill(&chan->tasklet);

		return ret;
	}


	dev_info(pdma->dev,
		 "%s: CAPABILITY ( %s%s%s)\n", dma_chan_name(&chan->dma_chan),
		 dma_has_cap(DMA_SG, dma_dev->cap_mask) ? "SGCPY " : "",
		 dma_has_cap(DMA_XOR, dma_dev->cap_mask) ? "XOR " : "",
		 dma_has_cap(DMA_PQ, dma_dev->cap_mask) ? "PQ " : "");

	return 0;
}
