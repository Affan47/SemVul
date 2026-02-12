static irqreturn_t skfp_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	struct s_smc *smc;
	skfddi_priv *bp;

	smc = netdev_priv(dev);
	bp = &smc->os;


	if (inpd(ADDR(B0_IMSK)) == 0) {

		return IRQ_NONE;
	}

	if ((inpd(ISR_A) & smc->hw.is_imask) == 0) {

		return IRQ_NONE;
	}
	CLI_FBI();
	spin_lock(&bp->DriverLock);


	fddi_isr(smc);

	if (smc->os.ResetRequested) {
		ResetAdapter(smc);
		smc->os.ResetRequested = FALSE;
	}
	spin_unlock(&bp->DriverLock);
	STI_FBI();

	return IRQ_HANDLED;
}
