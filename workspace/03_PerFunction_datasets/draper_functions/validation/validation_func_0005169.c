linda_remove ( struct pci_device *pci ) {
	struct ib_device *ibdev = pci_get_drvdata ( pci );
	struct linda *linda = ib_get_drvdata ( ibdev );

	unregister_ibdev ( ibdev );
	linda_fini_recv ( linda );
	linda_fini_send ( linda );
	ibdev_put ( ibdev );
}
