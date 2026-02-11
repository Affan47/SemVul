bcm63xx_txrx_bufs(struct spi_device *spi, struct spi_transfer *first,
				unsigned int num_transfers)
{
	struct bcm63xx_spi *bs = spi_master_get_devdata(spi->master);
	u16 msg_ctl;
	u16 cmd;
	unsigned int i, timeout = 0, prepend_len = 0, len = 0;
	struct spi_transfer *t = first;
	bool do_rx = false;
	bool do_tx = false;


	bcm_spi_writeb(bs, 0, SPI_INT_MASK);

	dev_dbg(&spi->dev, "txrx: tx %p, rx %p, len %d\n",
		t->tx_buf, t->rx_buf, t->len);

	if (num_transfers > 1 && t->tx_buf && t->len <= BCM63XX_SPI_MAX_PREPEND)
		prepend_len = t->len;


	for (i = 0; i < num_transfers; i++) {
		if (t->tx_buf) {
			do_tx = true;
			memcpy_toio(bs->tx_io + len, t->tx_buf, t->len);


			if (t != first)
				prepend_len = 0;
		}

		if (t->rx_buf) {
			do_rx = true;

			if (t == first)
				prepend_len = 0;
		}

		len += t->len;

		t = list_entry(t->transfer_list.next, struct spi_transfer,
			       transfer_list);
	}

	reinit_completion(&bs->done);


	msg_ctl = (len << SPI_BYTE_CNT_SHIFT);

	if (do_rx && do_tx && prepend_len == 0)
		msg_ctl |= (SPI_FD_RW << bs->msg_type_shift);
	else if (do_rx)
		msg_ctl |= (SPI_HD_R << bs->msg_type_shift);
	else if (do_tx)
		msg_ctl |= (SPI_HD_W << bs->msg_type_shift);

	switch (bs->msg_ctl_width) {
	case 8:
		bcm_spi_writeb(bs, msg_ctl, SPI_MSG_CTL);
		break;
	case 16:
		bcm_spi_writew(bs, msg_ctl, SPI_MSG_CTL);
		break;
	}


	cmd = SPI_CMD_START_IMMEDIATE;
	cmd |= (prepend_len << SPI_CMD_PREPEND_BYTE_CNT_SHIFT);
	cmd |= (spi->chip_select << SPI_CMD_DEVICE_ID_SHIFT);
	bcm_spi_writew(bs, cmd, SPI_CMD);


	bcm_spi_writeb(bs, SPI_INTR_CMD_DONE, SPI_INT_MASK);

	timeout = wait_for_completion_timeout(&bs->done, HZ);
	if (!timeout)
		return -ETIMEDOUT;

	if (!do_rx)
		return 0;

	len = 0;
	t = first;

	for (i = 0; i < num_transfers; i++) {
		if (t->rx_buf)
			memcpy_fromio(t->rx_buf, bs->rx_io + len, t->len);

		if (t != first || prepend_len == 0)
			len += t->len;

		t = list_entry(t->transfer_list.next, struct spi_transfer,
			       transfer_list);
	}

	return 0;
}
