dspi_eoq_write(struct fsl_dspi *dspi)
{
	int tx_count = 0;
	int tx_word;
	u32 dspi_pushr = 0;

	tx_word = is_double_byte_mode(dspi);

	while (dspi->len && (tx_count < DSPI_FIFO_SIZE)) {


		if (tx_word && (dspi->len == 1)) {
			dspi->dataflags |= TRAN_STATE_WORD_ODD_NUM;
			regmap_update_bits(dspi->regmap, SPI_CTAR(0),
					SPI_FRAME_BITS_MASK, SPI_FRAME_BITS(8));
			tx_word = 0;
		}

		dspi_pushr = dspi_data_to_pushr(dspi, tx_word);

		if (dspi->len == 0 || tx_count == DSPI_FIFO_SIZE - 1) {

			dspi_pushr |= SPI_PUSHR_EOQ;
			if ((dspi->cs_change) && (!dspi->len))
				dspi_pushr &= ~SPI_PUSHR_CONT;
		} else if (tx_word && (dspi->len == 1))
			dspi_pushr |= SPI_PUSHR_EOQ;

		regmap_write(dspi->regmap, SPI_PUSHR, dspi_pushr);

		tx_count++;
	}

	return tx_count * (tx_word + 1);
}
