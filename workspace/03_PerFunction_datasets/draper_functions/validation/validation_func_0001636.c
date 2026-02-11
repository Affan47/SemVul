uart_line_info(struct seq_file *m, struct uart_driver *drv, int i)
{
	struct uart_state *state = drv->state + i;
	struct tty_port *port = &state->port;
	enum uart_pm_state pm_state;
	struct uart_port *uport = state->uart_port;
	char stat_buf[32];
	unsigned int status;
	int mmio;

	if (!uport)
		return;

	mmio = uport->iotype >= UPIO_MEM;
	seq_printf(m, "%d: uart:%s %s%08llX irq:%d",
			uport->line, uart_type(uport),
			mmio ? "mmio:0x" : "port:",
			mmio ? (unsigned long long)uport->mapbase
			     : (unsigned long long)uport->iobase,
			uport->irq);

	if (uport->type == PORT_UNKNOWN) {
		seq_putc(m, '\n');
		return;
	}

	if (capable(CAP_SYS_ADMIN)) {
		mutex_lock(&port->mutex);
		pm_state = state->pm_state;
		if (pm_state != UART_PM_STATE_ON)
			uart_change_pm(state, UART_PM_STATE_ON);
		spin_lock_irq(&uport->lock);
		status = uport->ops->get_mctrl(uport);
		spin_unlock_irq(&uport->lock);
		if (pm_state != UART_PM_STATE_ON)
			uart_change_pm(state, pm_state);
		mutex_unlock(&port->mutex);

		seq_printf(m, " tx:%d rx:%d",
				uport->icount.tx, uport->icount.rx);
		if (uport->icount.frame)
			seq_printf(m, " fe:%d",
				uport->icount.frame);
		if (uport->icount.parity)
			seq_printf(m, " pe:%d",
				uport->icount.parity);
		if (uport->icount.brk)
			seq_printf(m, " brk:%d",
				uport->icount.brk);
		if (uport->icount.overrun)
			seq_printf(m, " oe:%d",
				uport->icount.overrun);

#define INFOBIT(bit, str) \
	if (uport->mctrl & (bit)) \
		strncat(stat_buf, (str), sizeof(stat_buf) - \
			strlen(stat_buf) - 2)
#define STATBIT(bit, str) \
	if (status & (bit)) \
		strncat(stat_buf, (str), sizeof(stat_buf) - \
		       strlen(stat_buf) - 2)

		stat_buf[0] = '\0';
		stat_buf[1] = '\0';
		INFOBIT(TIOCM_RTS, "|RTS");
		STATBIT(TIOCM_CTS, "|CTS");
		INFOBIT(TIOCM_DTR, "|DTR");
		STATBIT(TIOCM_DSR, "|DSR");
		STATBIT(TIOCM_CAR, "|CD");
		STATBIT(TIOCM_RNG, "|RI");
		if (stat_buf[0])
			stat_buf[0] = ' ';

		seq_puts(m, stat_buf);
	}
	seq_putc(m, '\n');
#undef STATBIT
#undef INFOBIT
}
