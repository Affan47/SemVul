static void *snd_dma_hack_alloc_coherent(struct device *dev, size_t size,
					 dma_addr_t *dma_handle,
					 gfp_t flags)
{
	void *ret;
	u64 dma_mask, coherent_dma_mask;

	if (dev == NULL || !dev->dma_mask)
		return dma_alloc_coherent(dev, size, dma_handle, flags);
	dma_mask = *dev->dma_mask;
	coherent_dma_mask = dev->coherent_dma_mask;
	*dev->dma_mask = 0xffffffff;
	dev->coherent_dma_mask = 0xffffffff;
	ret = dma_alloc_coherent(dev, size, dma_handle, flags);
	*dev->dma_mask = dma_mask;
	dev->coherent_dma_mask = coherent_dma_mask;
	if (ret) {

		if (((unsigned long)*dma_handle + size - 1) & ~dma_mask) {

			dma_free_coherent(dev, size, ret, *dma_handle);
			ret = dma_alloc_coherent(dev, size, dma_handle, flags);
		}
	} else {

		if (dma_mask != 0xffffffffUL) {

			flags &= ~GFP_KERNEL;
			flags |= GFP_ATOMIC;
			ret = dma_alloc_coherent(dev, size, dma_handle, flags);
		}
	}
	return ret;
}
