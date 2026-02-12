static unsigned long intel_alloc_iova(struct device *dev,
				     struct dmar_domain *domain,
				     unsigned long nrpages, uint64_t dma_mask)
{
	unsigned long iova_pfn;


	dma_mask = min_t(uint64_t, DOMAIN_MAX_ADDR(domain->gaw), dma_mask);

	nrpages = __roundup_pow_of_two(nrpages);

	if (!dmar_forcedac && dma_mask > DMA_BIT_MASK(32)) {


		iova_pfn = alloc_iova_fast(&domain->iovad, nrpages,
					   IOVA_PFN(DMA_BIT_MASK(32)), false);
		if (iova_pfn)
			return iova_pfn;
	}
	iova_pfn = alloc_iova_fast(&domain->iovad, nrpages,
				   IOVA_PFN(dma_mask), true);
	if (unlikely(!iova_pfn)) {
		dev_err(dev, "Allocating %ld-page iova failed", nrpages);
		return 0;
	}

	return iova_pfn;
}
