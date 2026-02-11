DMAbuf_launch_output(int dev, struct dma_buffparms *dmap)
{
	struct audio_operations *adev = audio_devs[dev];

	if (!((adev->enable_bits * adev->go) & PCM_ENABLE_OUTPUT))
		return;
	dmap->dma_mode = DMODE_OUTPUT;

	if (!(dmap->flags & DMA_ACTIVE) || !(adev->flags & DMA_AUTOMODE) || (dmap->flags & DMA_NODMA)) {
		if (!(dmap->flags & DMA_STARTED)) {
			reorganize_buffers(dev, dmap, 0);
			if (adev->d->prepare_for_output(dev, dmap->fragment_size, dmap->nbufs))
				return;
			if (!(dmap->flags & DMA_NODMA))
				local_start_dma(adev, dmap->raw_buf_phys, dmap->bytes_in_use,DMA_MODE_WRITE);
			dmap->flags |= DMA_STARTED;
		}
		if (dmap->counts[dmap->qhead] == 0)
			dmap->counts[dmap->qhead] = dmap->fragment_size;
		dmap->dma_mode = DMODE_OUTPUT;
		adev->d->output_block(dev, dmap->raw_buf_phys + dmap->qhead * dmap->fragment_size,
				      dmap->counts[dmap->qhead], 1);
		if (adev->d->trigger)
			adev->d->trigger(dev,adev->enable_bits * adev->go);
	}
	dmap->flags |= DMA_ACTIVE;
}
