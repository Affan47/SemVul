static int serial_ir_suspend(struct platform_device *dev,
			     pm_message_t state)
{

	soutp(UART_LCR, sinp(UART_LCR) & (~UART_LCR_DLAB));


	soutp(UART_IER, sinp(UART_IER) &
	      (~(UART_IER_MSI | UART_IER_RLSI | UART_IER_THRI | UART_IER_RDI)));


	sinp(UART_LSR);
	sinp(UART_RX);
	sinp(UART_IIR);
	sinp(UART_MSR);

	return 0;
}
