static void lp_console_write (struct console *co, const char *s,
			      unsigned count)
{
	struct pardevice *dev = lp_table[CONSOLE_LP].dev;
	struct parport *port = dev->port;
	ssize_t written;

	if (parport_claim (dev))

		return;

	parport_set_timeout (dev, 0);


	parport_negotiate (port, IEEE1284_MODE_COMPAT);

	do {

		ssize_t canwrite = count;
		char *lf = memchr (s, '\n', count);
		if (lf)
			canwrite = lf - s;

		if (canwrite > 0) {
			written = parport_write (port, s, canwrite);

			if (written <= 0)
				continue;

			s += written;
			count -= written;
			canwrite -= written;
		}

		if (lf && canwrite <= 0) {
			const char *crlf = "\r\n";
			int i = 2;


			s++;
			count--;
			do {
				written = parport_write (port, crlf, i);
				if (written > 0)
					i -= written, crlf += written;
			} while (i > 0 && (CONSOLE_LP_STRICT || written > 0));
		}
	} while (count > 0 && (CONSOLE_LP_STRICT || written > 0));

	parport_release (dev);
}
