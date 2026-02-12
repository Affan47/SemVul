static int bnx2x_get_num_non_def_sbs(struct pci_dev *pdev, int cnic_cnt)
{
	int index;
	u16 control = 0;


	if (!pdev->msix_cap) {
		dev_info(&pdev->dev, "no msix capability found\n");
		return 1 + cnic_cnt;
	}
	dev_info(&pdev->dev, "msix capability found\n");


	pci_read_config_word(pdev, pdev->msix_cap + PCI_MSIX_FLAGS, &control);

	index = control & PCI_MSIX_FLAGS_QSIZE;

	return index;
}
