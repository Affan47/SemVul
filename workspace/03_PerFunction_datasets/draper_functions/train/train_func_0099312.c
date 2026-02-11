sis_scr_cfg_read(struct ata_link *link,
			    unsigned int sc_reg, u32 *val)
{
	struct pci_dev *pdev = to_pci_dev(link->ap->host->dev);
	unsigned int cfg_addr = get_scr_cfg_addr(link, sc_reg);

	if (sc_reg == SCR_ERROR)
		return -EINVAL;

	pci_read_config_dword(pdev, cfg_addr, val);
	return 0;
}
