void tty_save_termios(struct tty_struct *tty)
{
	struct ktermios *tp;
	int idx = tty->index;


	if (tty->driver->flags & TTY_DRIVER_RESET_TERMIOS)
		return;


	tp = tty->driver->termios[idx];
	if (tp == NULL) {
		tp = kmalloc(sizeof(*tp), GFP_KERNEL);
		if (tp == NULL)
			return;
		tty->driver->termios[idx] = tp;
	}
	*tp = tty->termios;
}
