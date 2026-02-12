static void serial_ir_close(struct rc_dev *rcdev)
{
	unsigned long flags;

	spin_lock_irqsave(&hardware[type].lock, flags);


	soutp(UART_LCR, sinp(UART_LCR) & (~UART_LCR_DLAB));


	soutp(UART_IER, sinp(UART_IER) &
	      (~(UART_IER_MSI | UART_IER_RLSI | UART_IER_THRI | UART_IER_RDI)));
	spin_unlock_irqrestore(&hardware[type].lock, flags);
}
