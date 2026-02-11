omap_hsmmc_regs_show(struct seq_file *s, void *data)
{
	struct mmc_host *mmc = s->private;
	struct omap_hsmmc_host *host = mmc_priv(mmc);

	seq_printf(s, "mmc%d:\n", mmc->index);
	seq_printf(s, "sdio irq mode\t%s\n",
		   (mmc->caps & MMC_CAP_SDIO_IRQ) ? "interrupt" : "polling");

	if (mmc->caps & MMC_CAP_SDIO_IRQ) {
		seq_printf(s, "sdio irq \t%s\n",
			   (host->flags & HSMMC_SDIO_IRQ_ENABLED) ?  "enabled"
			   : "disabled");
	}
	seq_printf(s, "ctx_loss:\t%d\n", host->context_loss);

	pm_runtime_get_sync(host->dev);
	seq_puts(s, "\nregs:\n");
	seq_printf(s, "CON:\t\t0x%08x\n",
			OMAP_HSMMC_READ(host->base, CON));
	seq_printf(s, "PSTATE:\t\t0x%08x\n",
		   OMAP_HSMMC_READ(host->base, PSTATE));
	seq_printf(s, "HCTL:\t\t0x%08x\n",
			OMAP_HSMMC_READ(host->base, HCTL));
	seq_printf(s, "SYSCTL:\t\t0x%08x\n",
			OMAP_HSMMC_READ(host->base, SYSCTL));
	seq_printf(s, "IE:\t\t0x%08x\n",
			OMAP_HSMMC_READ(host->base, IE));
	seq_printf(s, "ISE:\t\t0x%08x\n",
			OMAP_HSMMC_READ(host->base, ISE));
	seq_printf(s, "CAPA:\t\t0x%08x\n",
			OMAP_HSMMC_READ(host->base, CAPA));

	pm_runtime_mark_last_busy(host->dev);
	pm_runtime_put_autosuspend(host->dev);

	return 0;
}
