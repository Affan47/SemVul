hso_serial_set_termios(struct tty_struct *tty, struct ktermios *old)
{
	struct hso_serial *serial = tty->driver_data;
	unsigned long flags;

	if (old)
		D5("Termios called with: cflags new[%d] - old[%d]",
		   tty->termios.c_cflag, old->c_cflag);


	spin_lock_irqsave(&serial->serial_lock, flags);
	if (serial->port.count)
		_hso_serial_set_termios(tty, old);
	else
		tty->termios = *old;
	spin_unlock_irqrestore(&serial->serial_lock, flags);


}
