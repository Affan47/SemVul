fintek_8250_rs485_config(struct uart_port *port,
			      struct serial_rs485 *rs485)
{
	uint8_t config = 0;
	struct fintek_8250 *pdata = port->private_data;

	if (!pdata)
		return -EINVAL;

	if (rs485->flags & SER_RS485_ENABLED)
		memset(rs485->padding, 0, sizeof(rs485->padding));
	else
		memset(rs485, 0, sizeof(*rs485));

	rs485->flags &= SER_RS485_ENABLED | SER_RS485_RTS_ON_SEND |
			SER_RS485_RTS_AFTER_SEND;

	if (rs485->delay_rts_before_send) {
		rs485->delay_rts_before_send = 1;
		config |= TXW4C_IRA;
	}

	if (rs485->delay_rts_after_send) {
		rs485->delay_rts_after_send = 1;
		config |= RXW4C_IRA;
	}

	if ((!!(rs485->flags & SER_RS485_RTS_ON_SEND)) ==
			(!!(rs485->flags & SER_RS485_RTS_AFTER_SEND)))
		rs485->flags &= ~SER_RS485_ENABLED;
	else
		config |= RS485_URA;

	if (rs485->flags & SER_RS485_RTS_ON_SEND)
		config |= RTS_INVERT;

	if (fintek_8250_enter_key(pdata->base_port, pdata->key))
		return -EBUSY;

	outb(LDN, pdata->base_port + ADDR_PORT);
	outb(pdata->index, pdata->base_port + DATA_PORT);
	outb(RS485, pdata->base_port + ADDR_PORT);
	outb(config, pdata->base_port + DATA_PORT);
	fintek_8250_exit_key(pdata->base_port);

	port->rs485 = *rs485;

	return 0;
}
