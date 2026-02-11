wbsd_prepare_data(struct wbsd_host *host, struct mmc_data *data)
{
	u16 blksize;
	u8 setup;
	unsigned long dmaflags;
	unsigned int size;


	size = data->blocks * data->blksz;


	if (data->timeout_ns > 127000000)
		wbsd_write_index(host, WBSD_IDX_TAAC, 127);
	else {
		wbsd_write_index(host, WBSD_IDX_TAAC,
			data->timeout_ns / 1000000);
	}

	if (data->timeout_clks > 255)
		wbsd_write_index(host, WBSD_IDX_NSAC, 255);
	else
		wbsd_write_index(host, WBSD_IDX_NSAC, data->timeout_clks);


	if (host->bus_width == MMC_BUS_WIDTH_1) {
		blksize = data->blksz + 2;

		wbsd_write_index(host, WBSD_IDX_PBSMSB, (blksize >> 4) & 0xF0);
		wbsd_write_index(host, WBSD_IDX_PBSLSB, blksize & 0xFF);
	} else if (host->bus_width == MMC_BUS_WIDTH_4) {
		blksize = data->blksz + 2 * 4;

		wbsd_write_index(host, WBSD_IDX_PBSMSB,
			((blksize >> 4) & 0xF0) | WBSD_DATA_WIDTH);
		wbsd_write_index(host, WBSD_IDX_PBSLSB, blksize & 0xFF);
	} else {
		data->error = -EINVAL;
		return;
	}


	setup = wbsd_read_index(host, WBSD_IDX_SETUP);
	setup |= WBSD_FIFO_RESET;
	wbsd_write_index(host, WBSD_IDX_SETUP, setup);


	if (host->dma >= 0) {


		BUG_ON(size > 0x10000);
		if (size > 0x10000) {
			data->error = -EINVAL;
			return;
		}


		if (data->flags & MMC_DATA_WRITE)
			wbsd_sg_to_dma(host, data);


		dmaflags = claim_dma_lock();
		disable_dma(host->dma);
		clear_dma_ff(host->dma);
		if (data->flags & MMC_DATA_READ)
			set_dma_mode(host->dma, DMA_MODE_READ & ~0x40);
		else
			set_dma_mode(host->dma, DMA_MODE_WRITE & ~0x40);
		set_dma_addr(host->dma, host->dma_addr);
		set_dma_count(host->dma, size);

		enable_dma(host->dma);
		release_dma_lock(dmaflags);


		wbsd_write_index(host, WBSD_IDX_DMA, WBSD_DMA_ENABLE);
	} else {


		host->firsterr = 1;


		wbsd_init_sg(host, data);


		wbsd_write_index(host, WBSD_IDX_DMA, 0);


		if (data->flags & MMC_DATA_READ) {
			wbsd_write_index(host, WBSD_IDX_FIFOEN,
				WBSD_FIFOEN_FULL | 8);
		} else {
			wbsd_write_index(host, WBSD_IDX_FIFOEN,
				WBSD_FIFOEN_EMPTY | 8);
			wbsd_fill_fifo(host);
		}
	}

	data->error = 0;
}
