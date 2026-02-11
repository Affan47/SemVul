dmaengine_pcm_prepare_and_submit(struct snd_pcm_substream *substream)
{
	struct dmaengine_pcm_runtime_data *prtd = substream_to_prtd(substream);
	struct dma_chan *chan = prtd->dma_chan;
	struct dma_async_tx_descriptor *desc;
	enum dma_transfer_direction direction;
	unsigned long flags = DMA_CTRL_ACK;

	direction = snd_pcm_substream_to_dma_direction(substream);

	if (!substream->runtime->no_period_wakeup)
		flags |= DMA_PREP_INTERRUPT;

	prtd->pos = 0;
	desc = dmaengine_prep_dma_cyclic(chan,
		substream->runtime->dma_addr,
		snd_pcm_lib_buffer_bytes(substream),
		snd_pcm_lib_period_bytes(substream), direction, flags);

	if (!desc)
		return -ENOMEM;

	desc->callback = dmaengine_pcm_dma_complete;
	desc->callback_param = substream;
	prtd->cookie = dmaengine_submit(desc);

	return 0;
}
