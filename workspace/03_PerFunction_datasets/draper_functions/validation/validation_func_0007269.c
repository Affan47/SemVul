bcm2835_spi_transfer_one(struct spi_master *master,
				    struct spi_device *spi,
				    struct spi_transfer *tfr)
{
	struct bcm2835_spi *bs = spi_master_get_devdata(master);
	unsigned long spi_hz, clk_hz, cdiv;
	unsigned long spi_used_hz;
	unsigned long long xfer_time_us;
	u32 cs = bcm2835_rd(bs, BCM2835_SPI_CS);


	spi_hz = tfr->speed_hz;
	clk_hz = clk_get_rate(bs->clk);

	if (spi_hz >= clk_hz / 2) {
		cdiv = 2;
	} else if (spi_hz) {

		cdiv = DIV_ROUND_UP(clk_hz, spi_hz);
		cdiv += (cdiv % 2);

		if (cdiv >= 65536)
			cdiv = 0;
	} else {
		cdiv = 0;
	}
	spi_used_hz = cdiv ? (clk_hz / cdiv) : (clk_hz / 65536);
	bcm2835_wr(bs, BCM2835_SPI_CLK, cdiv);


	if ((spi->mode & SPI_3WIRE) && (tfr->rx_buf))
		cs |= BCM2835_SPI_CS_REN;
	else
		cs &= ~BCM2835_SPI_CS_REN;


	if (gpio_is_valid(spi->cs_gpio) || (spi->mode & SPI_NO_CS))
		cs |= BCM2835_SPI_CS_CS_10 | BCM2835_SPI_CS_CS_01;


	bs->tx_buf = tfr->tx_buf;
	bs->rx_buf = tfr->rx_buf;
	bs->tx_len = tfr->len;
	bs->rx_len = tfr->len;


	xfer_time_us = (unsigned long long)tfr->len
		* 9
		* 1000000;
	do_div(xfer_time_us, spi_used_hz);


	if (xfer_time_us <= BCM2835_SPI_POLLING_LIMIT_US)
		return bcm2835_spi_transfer_one_poll(master, spi, tfr,
						     cs, xfer_time_us);


	if (master->can_dma && bcm2835_spi_can_dma(master, spi, tfr))
		return bcm2835_spi_transfer_one_dma(master, spi, tfr, cs);


	return bcm2835_spi_transfer_one_irq(master, spi, tfr, cs);
}
