i5100_init(void)
{
	int pci_rc;

	i5100_debugfs = edac_debugfs_create_dir_at("i5100_edac", NULL);

	pci_rc = pci_register_driver(&i5100_driver);
	return (pci_rc < 0) ? pci_rc : 0;
}
