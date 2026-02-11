hfi1_pcie_ddinit(struct hfi1_devdata *dd, struct pci_dev *pdev,
		     const struct pci_device_id *ent)
{
	unsigned long len;
	resource_size_t addr;

	dd->pcidev = pdev;
	pci_set_drvdata(pdev, dd);

	addr = pci_resource_start(pdev, 0);
	len = pci_resource_len(pdev, 0);


	if (len != TXE_PIO_SEND + TXE_PIO_SIZE) {
		dd_dev_err(dd, "chip PIO range does not match\n");
		return -EINVAL;
	}

	dd->kregbase = ioremap_nocache(addr, TXE_PIO_SEND);
	if (!dd->kregbase)
		return -ENOMEM;

	dd->piobase = ioremap_wc(addr + TXE_PIO_SEND, TXE_PIO_SIZE);
	if (!dd->piobase) {
		iounmap(dd->kregbase);
		return -ENOMEM;
	}

	dd->flags |= HFI1_PRESENT;

	dd->kregend = dd->kregbase + TXE_PIO_SEND;
	dd->physaddr = addr;


	dd->chip_rcv_array_count = read_csr(dd, RCV_ARRAY_CNT);
	dd->rcvarray_wc = ioremap_wc(addr + RCV_ARRAY,
				     dd->chip_rcv_array_count * 8);
	dd_dev_info(dd, "WC Remapped RcvArray: %p\n", dd->rcvarray_wc);


	dd->pcibar0 = addr;
	dd->pcibar1 = addr >> 32;
	pci_read_config_dword(dd->pcidev, PCI_ROM_ADDRESS, &dd->pci_rom);
	pci_read_config_word(dd->pcidev, PCI_COMMAND, &dd->pci_command);
	pcie_capability_read_word(dd->pcidev, PCI_EXP_DEVCTL, &dd->pcie_devctl);
	pcie_capability_read_word(dd->pcidev, PCI_EXP_LNKCTL, &dd->pcie_lnkctl);
	pcie_capability_read_word(dd->pcidev, PCI_EXP_DEVCTL2,
							&dd->pcie_devctl2);
	pci_read_config_dword(dd->pcidev, PCI_CFG_MSIX0, &dd->pci_msix0);
	pci_read_config_dword(dd->pcidev, PCIE_CFG_SPCIE1,
							&dd->pci_lnkctl3);
	pci_read_config_dword(dd->pcidev, PCIE_CFG_TPH2, &dd->pci_tph2);

	return 0;
}
