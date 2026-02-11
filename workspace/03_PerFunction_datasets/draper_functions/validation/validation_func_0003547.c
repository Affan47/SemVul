vty_out(vty_t *vty, const char *format, ...)
{
	va_list args;
	int len = 0;
	int size = 1024;
	char buf[1024];
	char *tmp = NULL;
	char *p = NULL;

	if (vty_shell (vty)) {
		va_start(args, format);
		vprintf(format, args);
		va_end(args);
	} else {

		va_start(args, format);
		len = vsnprintf(buf, sizeof buf, format, args);
		va_end(args);


		if (len < 0 || len >= size) {
		for (;;) {
			if (len > -1)
				size = len + 1;
			else
				size = size * 2;

			tmp = REALLOC(p, size);
			if (! tmp) {
				FREE(p);
				return -1;
			}
			p = tmp;

			va_start(args, format);
			len = vsnprintf(p, size, format, args);
			va_end(args);

			if (len > -1 && len < size)
				break;
		}
	}


	if (! p)
		p = buf;


	buffer_put(vty->obuf, (u_char *) p, len);


	if (p != buf)
		FREE(p);
	}

	return len;
}
