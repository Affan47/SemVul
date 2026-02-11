vfio_cap_len(struct vfio_pci_device *vdev, u8 cap, u8 pos)
{
	struct pci_dev *pdev = vdev->pdev;
	u32 dword;
	u16 word;
	u8 byte;
	int ret;

	switch (cap) {
	case PCI_CAP_ID_MSI:
		return vfio_msi_cap_len(vdev, pos);
	case PCI_CAP_ID_PCIX:
		ret = pci_read_config_word(pdev, pos + PCI_X_CMD, &word);
		if (ret)
			return pcibios_err_to_errno(ret);

		if (PCI_X_CMD_VERSION(word)) {

			pci_read_config_dword(pdev, PCI_CFG_SPACE_SIZE, &dword);
			vdev->extended_caps = (dword != 0);
			return PCI_CAP_PCIX_SIZEOF_V2;
		} else
			return PCI_CAP_PCIX_SIZEOF_V0;
	case PCI_CAP_ID_VNDR:

		ret = pci_read_config_byte(pdev, pos + PCI_CAP_FLAGS, &byte);
		if (ret)
			return pcibios_err_to_errno(ret);

		return byte;
	case PCI_CAP_ID_EXP:

		pci_read_config_dword(pdev, PCI_CFG_SPACE_SIZE, &dword);
		vdev->extended_caps = (dword != 0);


		if ((pcie_caps_reg(pdev) & PCI_EXP_FLAGS_VERS) == 1)
			return PCI_CAP_EXP_ENDPOINT_SIZEOF_V1;
		else
			return PCI_CAP_EXP_ENDPOINT_SIZEOF_V2;
	case PCI_CAP_ID_HT:
		ret = pci_read_config_byte(pdev, pos + 3, &byte);
		if (ret)
			return pcibios_err_to_errno(ret);

		return (byte & HT_3BIT_CAP_MASK) ?
			HT_CAP_SIZEOF_SHORT : HT_CAP_SIZEOF_LONG;
	case PCI_CAP_ID_SATA:
		ret = pci_read_config_byte(pdev, pos + PCI_SATA_REGS, &byte);
		if (ret)
			return pcibios_err_to_errno(ret);

		byte &= PCI_SATA_REGS_MASK;
		if (byte == PCI_SATA_REGS_INLINE)
			return PCI_SATA_SIZEOF_LONG;
		else
			return PCI_SATA_SIZEOF_SHORT;
	default:
		pr_warn("%s: %s unknown length for pci cap 0x%x@0x%x\n",
			dev_name(&pdev->dev), __func__, cap, pos);
	}

	return 0;
}
