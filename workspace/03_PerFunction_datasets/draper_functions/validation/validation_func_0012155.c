sil680_reinit_one(struct pci_dev *pdev)
{
	struct ata_host *host = pci_get_drvdata(pdev);
	int try_mmio, rc;

	rc = ata_pci_device_do_resume(pdev);
	if (rc)
		return rc;
	sil680_init_chip(pdev, &try_mmio);
	ata_host_resume(host);
	return 0;
}
