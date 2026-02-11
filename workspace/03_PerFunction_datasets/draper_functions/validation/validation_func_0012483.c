via_config_find(struct pci_dev **isa)
{
	struct via_isa_bridge *via_config;

	for (via_config = via_isa_bridges;
	     via_config->id != PCI_DEVICE_ID_VIA_ANON; via_config++)
		if ((*isa = pci_get_device(PCI_VENDOR_ID_VIA +
			!!(via_config->flags & VIA_BAD_ID),
			via_config->id, NULL))) {

			if ((*isa)->revision >= via_config->rev_min &&
			    (*isa)->revision <= via_config->rev_max)
				break;
			pci_dev_put(*isa);
		}

	return via_config;
}
