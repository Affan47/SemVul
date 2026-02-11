__mmc_start_request(struct mmc_host *host, struct mmc_request *mrq)
{
	int err;


	err = mmc_retune(host);
	if (err) {
		mrq->cmd->error = err;
		mmc_request_done(host, mrq);
		return;
	}


	if (mmc_is_io_op(mrq->cmd->opcode) && host->ops->card_busy) {
		int tries = 500;

		while (host->ops->card_busy(host) && --tries)
			mmc_delay(1);

		if (tries == 0) {
			mrq->cmd->error = -EBUSY;
			mmc_request_done(host, mrq);
			return;
		}
	}

	host->ops->request(host, mrq);
}
