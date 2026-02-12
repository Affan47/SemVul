static void hso_init_termios(struct ktermios *termios)
{


	termios->c_iflag &=
		~(IGNBRK
		| BRKINT
		| PARMRK
		| ISTRIP
		| INLCR
		| IGNCR
		| ICRNL
		| IXON);


	termios->c_oflag &= ~OPOST;

	termios->c_lflag &=
		~(ECHO
		| ECHONL
		| ICANON

		| ISIG

		| IEXTEN);

	termios->c_cflag &=
		~(CSIZE
		| PARENB
		| CBAUD
		| CBAUDEX);

	termios->c_cflag |= CS8;


	tty_termios_encode_baud_rate(termios, 115200, 115200);
}
