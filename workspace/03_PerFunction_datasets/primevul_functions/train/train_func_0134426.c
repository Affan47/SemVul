static void _hso_serial_set_termios(struct tty_struct *tty,
				    struct ktermios *old)
{
	struct hso_serial *serial = tty->driver_data;

	if (!serial) {
		pr_err("%s: no tty structures", __func__);
		return;
	}

	hso_dbg(0x8, "port %d\n", serial->minor);


	tty->termios.c_iflag &= ~IXON;

	tty->termios.c_cflag &=
		~(CSIZE
		| PARENB
		| CBAUD
		| CBAUDEX);

	tty->termios.c_cflag |= CS8;


	tty_encode_baud_rate(tty, 115200, 115200);
}
