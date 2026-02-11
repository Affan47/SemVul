qspi_transfer_out_in(struct rspi_data *rspi,
				struct spi_transfer *xfer)
{
	int ret;

	qspi_receive_init(rspi);

	ret = rspi_dma_check_then_transfer(rspi, xfer);
	if (ret != -EAGAIN)
		return ret;

	return qspi_trigger_transfer_out_in(rspi, xfer->tx_buf,
					    xfer->rx_buf, xfer->len);
}
