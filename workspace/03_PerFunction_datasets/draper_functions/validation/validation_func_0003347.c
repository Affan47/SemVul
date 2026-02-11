sdio_set_bus_speed_mode(struct mmc_card *card)
{
	unsigned int bus_speed, timing;
	int err;
	unsigned char speed;


	if (!mmc_host_uhs(card->host))
		return 0;

	bus_speed = SDIO_SPEED_SDR12;
	timing = MMC_TIMING_UHS_SDR12;
	if ((card->host->caps & MMC_CAP_UHS_SDR104) &&
	    (card->sw_caps.sd3_bus_mode & SD_MODE_UHS_SDR104)) {
			bus_speed = SDIO_SPEED_SDR104;
			timing = MMC_TIMING_UHS_SDR104;
			card->sw_caps.uhs_max_dtr = UHS_SDR104_MAX_DTR;
			card->sd_bus_speed = UHS_SDR104_BUS_SPEED;
	} else if ((card->host->caps & MMC_CAP_UHS_DDR50) &&
		   (card->sw_caps.sd3_bus_mode & SD_MODE_UHS_DDR50)) {
			bus_speed = SDIO_SPEED_DDR50;
			timing = MMC_TIMING_UHS_DDR50;
			card->sw_caps.uhs_max_dtr = UHS_DDR50_MAX_DTR;
			card->sd_bus_speed = UHS_DDR50_BUS_SPEED;
	} else if ((card->host->caps & (MMC_CAP_UHS_SDR104 |
		    MMC_CAP_UHS_SDR50)) && (card->sw_caps.sd3_bus_mode &
		    SD_MODE_UHS_SDR50)) {
			bus_speed = SDIO_SPEED_SDR50;
			timing = MMC_TIMING_UHS_SDR50;
			card->sw_caps.uhs_max_dtr = UHS_SDR50_MAX_DTR;
			card->sd_bus_speed = UHS_SDR50_BUS_SPEED;
	} else if ((card->host->caps & (MMC_CAP_UHS_SDR104 |
		    MMC_CAP_UHS_SDR50 | MMC_CAP_UHS_SDR25)) &&
		   (card->sw_caps.sd3_bus_mode & SD_MODE_UHS_SDR25)) {
			bus_speed = SDIO_SPEED_SDR25;
			timing = MMC_TIMING_UHS_SDR25;
			card->sw_caps.uhs_max_dtr = UHS_SDR25_MAX_DTR;
			card->sd_bus_speed = UHS_SDR25_BUS_SPEED;
	} else if ((card->host->caps & (MMC_CAP_UHS_SDR104 |
		    MMC_CAP_UHS_SDR50 | MMC_CAP_UHS_SDR25 |
		    MMC_CAP_UHS_SDR12)) && (card->sw_caps.sd3_bus_mode &
		    SD_MODE_UHS_SDR12)) {
			bus_speed = SDIO_SPEED_SDR12;
			timing = MMC_TIMING_UHS_SDR12;
			card->sw_caps.uhs_max_dtr = UHS_SDR12_MAX_DTR;
			card->sd_bus_speed = UHS_SDR12_BUS_SPEED;
	}

	err = mmc_io_rw_direct(card, 0, 0, SDIO_CCCR_SPEED, 0, &speed);
	if (err)
		return err;

	speed &= ~SDIO_SPEED_BSS_MASK;
	speed |= bus_speed;
	err = mmc_io_rw_direct(card, 1, 0, SDIO_CCCR_SPEED, speed, NULL);
	if (err)
		return err;

	if (bus_speed) {
		mmc_set_timing(card->host, timing);
		mmc_set_clock(card->host, card->sw_caps.uhs_max_dtr);
	}

	return 0;
}
