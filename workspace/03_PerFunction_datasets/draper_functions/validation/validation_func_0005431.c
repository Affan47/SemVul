serial8250_rx_dma(struct uart_8250_port *p, unsigned int iir)
{
	struct uart_8250_dma		*dma = p->dma;
	struct dma_async_tx_descriptor	*desc;

	switch (iir & 0x3f) {
	case UART_IIR_RLSI:

		return -EIO;
	case UART_IIR_RX_TIMEOUT:


		if (dma->rx_running) {
			dmaengine_pause(dma->rxchan);
			__dma_rx_complete(p);
			dmaengine_terminate_all(dma->rxchan);
		}
		return -ETIMEDOUT;
	default:
		break;
	}

	if (dma->rx_running)
		return 0;

	desc = dmaengine_prep_slave_single(dma->rxchan, dma->rx_addr,
					   dma->rx_size, DMA_DEV_TO_MEM,
					   DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	if (!desc)
		return -EBUSY;

	dma->rx_running = 1;
	desc->callback = __dma_rx_complete;
	desc->callback_param = p;

	dma->rx_cookie = dmaengine_submit(desc);

	dma_async_issue_pending(dma->rxchan);

	return 0;
}
