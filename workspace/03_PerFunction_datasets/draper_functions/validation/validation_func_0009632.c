pxa2xx_spi_dma_prepare(struct driver_data *drv_data, u32 dma_burst)
{
	struct dma_async_tx_descriptor *tx_desc, *rx_desc;

	tx_desc = pxa2xx_spi_dma_prepare_one(drv_data, DMA_MEM_TO_DEV);
	if (!tx_desc) {
		dev_err(&drv_data->pdev->dev,
			"failed to get DMA TX descriptor\n");
		return -EBUSY;
	}

	rx_desc = pxa2xx_spi_dma_prepare_one(drv_data, DMA_DEV_TO_MEM);
	if (!rx_desc) {
		dev_err(&drv_data->pdev->dev,
			"failed to get DMA RX descriptor\n");
		return -EBUSY;
	}


	rx_desc->callback = pxa2xx_spi_dma_callback;
	rx_desc->callback_param = drv_data;

	dmaengine_submit(rx_desc);
	dmaengine_submit(tx_desc);
	return 0;
}
