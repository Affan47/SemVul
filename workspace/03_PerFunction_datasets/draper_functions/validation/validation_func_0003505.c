interrupt_transfer(struct driver_data *drv_data)
{
	u32 irq_mask = (pxa2xx_spi_read(drv_data, SSCR1) & SSCR1_TIE) ?
		       drv_data->mask_sr : drv_data->mask_sr & ~SSSR_TFS;

	u32 irq_status = pxa2xx_spi_read(drv_data, SSSR) & irq_mask;

	if (irq_status & SSSR_ROR) {
		int_error_stop(drv_data, "interrupt_transfer: fifo overrun");
		return IRQ_HANDLED;
	}

	if (irq_status & SSSR_TINT) {
		pxa2xx_spi_write(drv_data, SSSR, SSSR_TINT);
		if (drv_data->read(drv_data)) {
			int_transfer_complete(drv_data);
			return IRQ_HANDLED;
		}
	}


	do {
		if (drv_data->read(drv_data)) {
			int_transfer_complete(drv_data);
			return IRQ_HANDLED;
		}
	} while (drv_data->write(drv_data));

	if (drv_data->read(drv_data)) {
		int_transfer_complete(drv_data);
		return IRQ_HANDLED;
	}

	if (drv_data->tx == drv_data->tx_end) {
		u32 bytes_left;
		u32 sccr1_reg;

		sccr1_reg = pxa2xx_spi_read(drv_data, SSCR1);
		sccr1_reg &= ~SSCR1_TIE;


		if (pxa25x_ssp_comp(drv_data)) {
			u32 rx_thre;

			pxa2xx_spi_clear_rx_thre(drv_data, &sccr1_reg);

			bytes_left = drv_data->rx_end - drv_data->rx;
			switch (drv_data->n_bytes) {
			case 4:
				bytes_left >>= 1;
			case 2:
				bytes_left >>= 1;
			}

			rx_thre = pxa2xx_spi_get_rx_default_thre(drv_data);
			if (rx_thre > bytes_left)
				rx_thre = bytes_left;

			pxa2xx_spi_set_rx_thre(drv_data, &sccr1_reg, rx_thre);
		}
		pxa2xx_spi_write(drv_data, SSCR1, sccr1_reg);
	}


	return IRQ_HANDLED;
}
