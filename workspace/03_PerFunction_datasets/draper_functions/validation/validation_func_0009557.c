dma_tx_callback(void *param)
{
	struct mxs_auart_port *s = param;
	struct circ_buf *xmit = &s->port.state->xmit;

	dma_unmap_sg(s->dev, &s->tx_sgl, 1, DMA_TO_DEVICE);


	clear_bit(MXS_AUART_DMA_TX_SYNC, &s->flags);
	smp_mb__after_atomic();


	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(&s->port);

	mxs_auart_tx_chars(s);
}
