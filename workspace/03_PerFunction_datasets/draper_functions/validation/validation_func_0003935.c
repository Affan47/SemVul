sd_set_power_mode(struct realtek_pci_sdmmc *host,
		unsigned char power_mode)
{
	int err;

	if (power_mode == MMC_POWER_OFF)
		err = sd_power_off(host);
	else
		err = sd_power_on(host);

	return err;
}
