output_sleep(int dev, int dontblock)
{
	struct audio_operations *adev = audio_devs[dev];
	int err = 0;
	struct dma_buffparms *dmap = adev->dmap_out;
	long timeout;
	long timeout_value;

	if (dontblock)
		return -EAGAIN;
	if (!(adev->enable_bits & PCM_ENABLE_OUTPUT))
		return -EAGAIN;


	if (signal_pending(current))
		return -EINTR;
	timeout = (adev->go && !(dmap->flags & DMA_NOTIMEOUT));
	if (timeout)
		timeout_value = dmabuf_timeout(dmap);
	else
		timeout_value = MAX_SCHEDULE_TIMEOUT;
	timeout_value = oss_broken_sleep_on(&adev->out_sleeper, timeout_value);
	if (timeout != MAX_SCHEDULE_TIMEOUT && !timeout_value) {
		printk(KERN_WARNING "Sound: DMA (output) timed out - IRQ/DRQ config error?\n");
		dma_reset_output(dev);
	} else {
		if (signal_pending(current))
			err = -EINTR;
	}
	return err;
}
