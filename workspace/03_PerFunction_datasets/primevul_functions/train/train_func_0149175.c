static dma_addr_t __intel_map_single(struct device *dev, phys_addr_t paddr,
				     size_t size, int dir, u64 dma_mask)
{
	struct dmar_domain *domain;
	phys_addr_t start_paddr;
	unsigned long iova_pfn;
	int prot = 0;
	int ret;
	struct intel_iommu *iommu;
	unsigned long paddr_pfn = paddr >> PAGE_SHIFT;

	BUG_ON(dir == DMA_NONE);

	if (iommu_no_mapping(dev))
		return paddr;

	domain = get_valid_domain_for_dev(dev);
	if (!domain)
		return DMA_MAPPING_ERROR;

	iommu = domain_get_iommu(domain);
	size = aligned_nrpages(paddr, size);

	iova_pfn = intel_alloc_iova(dev, domain, dma_to_mm_pfn(size), dma_mask);
	if (!iova_pfn)
		goto error;


	if (dir == DMA_TO_DEVICE || dir == DMA_BIDIRECTIONAL || \
			!cap_zlr(iommu->cap))
		prot |= DMA_PTE_READ;
	if (dir == DMA_FROM_DEVICE || dir == DMA_BIDIRECTIONAL)
		prot |= DMA_PTE_WRITE;


	ret = domain_pfn_mapping(domain, mm_to_dma_pfn(iova_pfn),
				 mm_to_dma_pfn(paddr_pfn), size, prot);
	if (ret)
		goto error;

	start_paddr = (phys_addr_t)iova_pfn << PAGE_SHIFT;
	start_paddr += paddr & ~PAGE_MASK;
	return start_paddr;

error:
	if (iova_pfn)
		free_iova_fast(&domain->iovad, iova_pfn, dma_to_mm_pfn(size));
	dev_err(dev, "Device request: %zx@%llx dir %d --- failed\n",
		size, (unsigned long long)paddr, dir);
	return DMA_MAPPING_ERROR;
}
