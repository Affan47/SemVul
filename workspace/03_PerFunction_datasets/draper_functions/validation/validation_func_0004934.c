diva_free_dma_map(void *hdev, struct _diva_dma_map_entry *pmap)
{
	struct pci_dev *pdev = (struct pci_dev *) hdev;
	int i;
	dword phys_addr;
	void *cpu_addr;
	dma_addr_t dma_handle;
	void *addr_handle;

	for (i = 0; (pmap != NULL); i++) {
		diva_get_dma_map_entry(pmap, i, &cpu_addr, &phys_addr);
		if (!cpu_addr) {
			break;
		}
		addr_handle = diva_get_entry_handle(pmap, i);
		dma_handle = (dma_addr_t) phys_addr;
		pci_free_consistent(pdev, PAGE_SIZE, addr_handle,
				    dma_handle);
		DBG_TRC(("dma map free [%d]=(%08lx:%08x:%08lx)", i,
			 (unsigned long) cpu_addr, (dword) dma_handle,
			 (unsigned long) addr_handle))
			}

	diva_free_dma_mapping(pmap);
}
