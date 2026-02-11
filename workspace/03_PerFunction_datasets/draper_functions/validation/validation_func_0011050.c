dma_alloc_consistent(struct dma_info *di, uint size,
				  u16 align_bits, uint *alloced,
				  dma_addr_t *pap)
{
	if (align_bits) {
		u16 align = (1 << align_bits);
		if (!IS_ALIGNED(PAGE_SIZE, align))
			size += align;
		*alloced = size;
	}
	return dma_alloc_coherent(di->dmadev, size, pap, GFP_ATOMIC);
}
