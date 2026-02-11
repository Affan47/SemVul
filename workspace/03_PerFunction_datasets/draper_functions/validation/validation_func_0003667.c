qlcnic_setup_pci_map(struct pci_dev *pdev,
				struct qlcnic_hardware_context *ahw)
{
	u32 offset;
	void __iomem *mem_ptr0 = NULL;
	unsigned long mem_len, pci_len0 = 0, bar0_len;


	mem_len = pci_resource_len(pdev, 0);

	qlcnic_get_bar_length(pdev->device, &bar0_len);
	if (mem_len >= bar0_len) {

		mem_ptr0 = pci_ioremap_bar(pdev, 0);
		if (mem_ptr0 == NULL) {
			dev_err(&pdev->dev, "failed to map PCI bar 0\n");
			return -EIO;
		}
		pci_len0 = mem_len;
	} else {
		return -EIO;
	}

	dev_info(&pdev->dev, "%dKB memory map\n", (int)(mem_len >> 10));

	ahw->pci_base0 = mem_ptr0;
	ahw->pci_len0 = pci_len0;
	offset = QLCNIC_PCIX_PS_REG(PCIX_OCM_WINDOW_REG(ahw->pci_func));
	qlcnic_get_ioaddr(ahw, offset);

	return 0;
}
