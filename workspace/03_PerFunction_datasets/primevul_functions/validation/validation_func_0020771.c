static void spi_hw_init(struct device *dev, struct dw_spi *dws)
{
	spi_reset_chip(dws);


	if (!dws->fifo_len) {
		u32 fifo;

		for (fifo = 1; fifo < 256; fifo++) {
			dw_writel(dws, DW_SPI_TXFLTR, fifo);
			if (fifo != dw_readl(dws, DW_SPI_TXFLTR))
				break;
		}
		dw_writel(dws, DW_SPI_TXFLTR, 0);

		dws->fifo_len = (fifo == 1) ? 0 : fifo;
		dev_dbg(dev, "Detected FIFO size: %u bytes\n", dws->fifo_len);
	}


	if (dws->cs_override)
		dw_writel(dws, DW_SPI_CS_OVERRIDE, 0xF);
}
