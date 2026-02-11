pxa2xx_spi_txfifo_full(const struct driver_data *drv_data)
{
	u32 mask;

	switch (drv_data->ssp_type) {
	case QUARK_X1000_SSP:
		mask = QUARK_X1000_SSSR_TFL_MASK;
		break;
	default:
		mask = SSSR_TFL_MASK;
		break;
	}

	return (pxa2xx_spi_read(drv_data, SSSR) & mask) == mask;
}
