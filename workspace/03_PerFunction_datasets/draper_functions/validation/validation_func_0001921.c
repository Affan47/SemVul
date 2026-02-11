serial8250_break_ctl(struct uart_port *port, int break_state)
{
	struct uart_8250_port *up = up_to_u8250p(port);
	unsigned long flags;

	serial8250_rpm_get(up);
	spin_lock_irqsave(&port->lock, flags);
	if (break_state == -1)
		up->lcr |= UART_LCR_SBC;
	else
		up->lcr &= ~UART_LCR_SBC;
	serial_port_out(port, UART_LCR, up->lcr);
	spin_unlock_irqrestore(&port->lock, flags);
	serial8250_rpm_put(up);
}
