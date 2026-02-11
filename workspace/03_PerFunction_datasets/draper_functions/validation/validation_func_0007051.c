ddp_gl_map(struct pci_dev *pdev,
				    struct cxgbi_gather_list *gl)
{
	int i;

	for (i = 0; i < gl->nelem; i++) {
		gl->phys_addr[i] = dma_map_page(&pdev->dev, gl->pages[i], 0,
						PAGE_SIZE,
						PCI_DMA_FROMDEVICE);
		if (unlikely(dma_mapping_error(&pdev->dev, gl->phys_addr[i]))) {
			log_debug(1 << CXGBI_DBG_DDP,
				"page %d 0x%p, 0x%p dma mapping err.\n",
				i, gl->pages[i], pdev);
			goto unmap;
		}
	}
	return i;
unmap:
	if (i) {
		unsigned int nelem = gl->nelem;

		gl->nelem = i;
		ddp_gl_unmap(pdev, gl);
		gl->nelem = nelem;
	}
	return -EINVAL;
}
