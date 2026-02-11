ath5k_hw_stop_rx_dma(struct ath5k_hw *ah)
{
	unsigned int i;

	ath5k_hw_reg_write(ah, AR5K_CR_RXD, AR5K_CR);


	for (i = 1000; i > 0 &&
			(ath5k_hw_reg_read(ah, AR5K_CR) & AR5K_CR_RXE) != 0;
			i--)
		udelay(100);

	if (!i)
		ATH5K_DBG(ah, ATH5K_DEBUG_DMA,
				"failed to stop RX DMA !\n");

	return i ? 0 : -EBUSY;
}
