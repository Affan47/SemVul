convert_escapes(char *buf)
{
	char *p = buf, *s = buf;

	while (*s) {
		if (*s == '\\') {
			s++;
			if (*s == 'n') {
				*p++ = '\n';
			} else if (*s == '\\') {
				*p++ = '\\';
			}
			s++;
		} else {
			*p++ = *s++;
		}
	}
	*p = '\0';
}
