cb_encode_program_id (const char *name)
{
	unsigned char		*p;
	const unsigned char	*s;
	unsigned char		buff[COB_SMALL_BUFF];

	p = buff;
	s = (const unsigned char *)name;

	if (isdigit (*s)) {
		p += sprintf ((char *)p, "_%02X", *s++);
	}

	for (; *s; s++) {
		if (isalnum (*s) || *s == '_') {
			*p++ = *s;
		} else if (*s == '-') {
			*p++ = '_';
			*p++ = '_';
		} else {
			p += sprintf ((char *)p, "_%02X", *s);
		}
	}
	*p = 0;
	return strdup ((char *)buff);
}
