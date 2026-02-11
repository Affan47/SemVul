fsl_spi_qe_cpu_set_shifts(u32 *rx_shift, u32 *tx_shift,
				      int bits_per_word, int msb_first)
{
	*rx_shift = 0;
	*tx_shift = 0;
	if (msb_first) {
		if (bits_per_word <= 8) {
			*rx_shift = 16;
			*tx_shift = 24;
		} else if (bits_per_word <= 16) {
			*rx_shift = 16;
			*tx_shift = 16;
		}
	} else {
		if (bits_per_word <= 8)
			*rx_shift = 8;
	}
}
