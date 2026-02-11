_base_check_enable_msix(struct MPT3SAS_ADAPTER *ioc)
{
	int base;
	u16 message_control;


	if (ioc->pdev->device == MPI2_MFGPAGE_DEVID_SAS2008 &&
	    ioc->pdev->revision == SAS2_PCI_DEVICE_B0_REVISION) {
		return -EINVAL;
	}

	base = pci_find_capability(ioc->pdev, PCI_CAP_ID_MSIX);
	if (!base) {
		dfailprintk(ioc, pr_info(MPT3SAS_FMT "msix not supported\n",
			ioc->name));
		return -EINVAL;
	}


	if (ioc->pdev->device == MPI2_MFGPAGE_DEVID_SAS2004 ||
	    ioc->pdev->device == MPI2_MFGPAGE_DEVID_SAS2008 ||
	    ioc->pdev->device == MPI2_MFGPAGE_DEVID_SAS2108_1 ||
	    ioc->pdev->device == MPI2_MFGPAGE_DEVID_SAS2108_2 ||
	    ioc->pdev->device == MPI2_MFGPAGE_DEVID_SAS2108_3 ||
	    ioc->pdev->device == MPI2_MFGPAGE_DEVID_SAS2116_1 ||
	    ioc->pdev->device == MPI2_MFGPAGE_DEVID_SAS2116_2)
		ioc->msix_vector_count = 1;
	else {
		pci_read_config_word(ioc->pdev, base + 2, &message_control);
		ioc->msix_vector_count = (message_control & 0x3FF) + 1;
	}
	dinitprintk(ioc, pr_info(MPT3SAS_FMT
		"msix is supported, vector_count(%d)\n",
		ioc->name, ioc->msix_vector_count));
	return 0;
}
