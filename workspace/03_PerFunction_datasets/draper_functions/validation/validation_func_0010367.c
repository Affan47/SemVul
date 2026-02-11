tifm_sd_remove(struct tifm_dev *sock)
{
	struct mmc_host *mmc = tifm_get_drvdata(sock);
	struct tifm_sd *host = mmc_priv(mmc);
	unsigned long flags;

	spin_lock_irqsave(&sock->lock, flags);
	host->eject = 1;
	writel(0, sock->addr + SOCK_MMCSD_INT_ENABLE);
	mmiowb();
	spin_unlock_irqrestore(&sock->lock, flags);

	tasklet_kill(&host->finish_tasklet);

	spin_lock_irqsave(&sock->lock, flags);
	if (host->req) {
		writel(TIFM_FIFO_INT_SETALL,
		       sock->addr + SOCK_DMA_FIFO_INT_ENABLE_CLEAR);
		writel(0, sock->addr + SOCK_DMA_FIFO_INT_ENABLE_SET);
		host->req->cmd->error = -ENOMEDIUM;
		if (host->req->stop)
			host->req->stop->error = -ENOMEDIUM;
		tasklet_schedule(&host->finish_tasklet);
	}
	spin_unlock_irqrestore(&sock->lock, flags);
	mmc_remove_host(mmc);
	dev_dbg(&sock->dev, "after remove\n");

	mmc_free_host(mmc);
}
