ahd_pci_config(struct ahd_softc *ahd, const struct ahd_pci_identity *entry)
{
	struct scb_data *shared_scb_data;
	u_int		 command;
	uint32_t	 devconfig;
	uint16_t	 subvendor;
	int		 error;

	shared_scb_data = NULL;
	ahd->description = entry->name;


	subvendor = ahd_pci_read_config(ahd->dev_softc,
					PCIR_SUBVEND_0, 2);
	if (subvendor == SUBID_HP)
		ahd->flags |= AHD_HP_BOARD;

	error = entry->setup(ahd);
	if (error != 0)
		return (error);

	devconfig = ahd_pci_read_config(ahd->dev_softc, DEVCONFIG, 4);
	if ((devconfig & PCIXINITPAT) == PCIXINIT_PCI33_66) {
		ahd->chip |= AHD_PCI;

		ahd->bugs &= ~AHD_PCIX_BUG_MASK;
	} else {
		ahd->chip |= AHD_PCIX;
	}
	ahd->bus_description = pci_bus_modes[PCI_BUS_MODES_INDEX(devconfig)];

	ahd_power_state_change(ahd, AHD_POWER_STATE_D0);

	error = ahd_pci_map_registers(ahd);
	if (error != 0)
		return (error);


	if ((ahd->flags & (AHD_39BIT_ADDRESSING|AHD_64BIT_ADDRESSING)) != 0) {
		if (bootverbose)
			printk("%s: Enabling 39Bit Addressing\n",
			       ahd_name(ahd));
		devconfig = ahd_pci_read_config(ahd->dev_softc,
						DEVCONFIG, 4);
		devconfig |= DACEN;
		ahd_pci_write_config(ahd->dev_softc, DEVCONFIG,
				     devconfig, 4);
	}


	command = ahd_pci_read_config(ahd->dev_softc, PCIR_COMMAND, 2);
	command |= PCIM_CMD_BUSMASTEREN;
	ahd_pci_write_config(ahd->dev_softc, PCIR_COMMAND, command, 2);

	error = ahd_softc_init(ahd);
	if (error != 0)
		return (error);

	ahd->bus_intr = ahd_pci_intr;

	error = ahd_reset(ahd, FALSE);
	if (error != 0)
		return (ENXIO);

	ahd->pci_cachesize =
	    ahd_pci_read_config(ahd->dev_softc, CSIZE_LATTIME,
				1) & CACHESIZE;
	ahd->pci_cachesize *= 4;

	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);

	error = ahd_check_extport(ahd);
	if (error != 0)
		return (error);


	error = ahd_init(ahd);
	if (error != 0)
		return (error);
	ahd->init_level++;


	return ahd_pci_map_int(ahd);
}
