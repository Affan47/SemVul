mmc_hs200_tuning(struct mmc_card *card)
{
	struct mmc_host *host = card->host;


	if (card->mmc_avail_type & EXT_CSD_CARD_TYPE_HS400 &&
	    host->ios.bus_width == MMC_BUS_WIDTH_8)
		if (host->ops->prepare_hs400_tuning)
			host->ops->prepare_hs400_tuning(host, &host->ios);

	return mmc_execute_tuning(card);
}
