dma_ringalloc(struct dma_info *di, u32 boundary, uint size,
			   u16 *alignbits, uint *alloced,
			   dma_addr_t *descpa)
{
	void *va;
	u32 desc_strtaddr;
	u32 alignbytes = 1 << *alignbits;

	va = dma_alloc_consistent(di, size, *alignbits, alloced, descpa);

	if (NULL == va)
		return NULL;

	desc_strtaddr = (u32) roundup((unsigned long)va, alignbytes);
	if (((desc_strtaddr + size - 1) & boundary) != (desc_strtaddr
							& boundary)) {
		*alignbits = dma_align_sizetobits(size);
		dma_free_coherent(di->dmadev, size, va, *descpa);
		va = dma_alloc_consistent(di, size, *alignbits,
			alloced, descpa);
	}
	return va;
}
