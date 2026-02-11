cb710_mmc_request(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct cb710_slot *slot = cb710_mmc_to_slot(mmc);
	struct cb710_mmc_reader *reader = mmc_priv(mmc);

	WARN_ON(reader->mrq != NULL);

	reader->mrq = mrq;
	cb710_mmc_enable_irq(slot, CB710_MMC_IE_TEST_MASK, 0);

	if (!cb710_mmc_command(mmc, mrq->cmd) && mrq->stop)
		cb710_mmc_command(mmc, mrq->stop);

	tasklet_schedule(&reader->finish_req_tasklet);
}
