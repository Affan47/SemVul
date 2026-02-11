netup_spi_interrupt(struct netup_spi *spi)
{
	u16 reg;
	unsigned long flags;

	if (!spi)
		return IRQ_NONE;

	spin_lock_irqsave(&spi->lock, flags);
	reg = readw(&spi->regs->control_stat);
	if (!(reg & NETUP_SPI_CTRL_IRQ)) {
		spin_unlock_irqrestore(&spi->lock, flags);
		dev_dbg(&spi->master->dev,
			"%s(): not mine interrupt\n", __func__);
		return IRQ_NONE;
	}
	writew(reg | NETUP_SPI_CTRL_IRQ, &spi->regs->control_stat);
	reg = readw(&spi->regs->control_stat);
	writew(reg & ~NETUP_SPI_CTRL_IMASK, &spi->regs->control_stat);
	spi->state = SPI_STATE_DONE;
	wake_up(&spi->waitq);
	spin_unlock_irqrestore(&spi->lock, flags);
	dev_dbg(&spi->master->dev,
		"%s(): SPI interrupt handled\n", __func__);
	return IRQ_HANDLED;
}
