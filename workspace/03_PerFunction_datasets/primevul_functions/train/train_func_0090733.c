next_opt(datawin, str)
winid datawin;
const char *str;
{
	static char *buf = 0;
	int i;
	char *s;

	if (!buf) *(buf = (char *)alloc(BUFSZ)) = '\0';

	if (!*str) {
		s = eos(buf);
		if (s > &buf[1] && s[-2] == ',')
		    Strcpy(s - 2, ".");
		i = COLNO;
	} else {
		i = strlen(buf) + strlen(str) + 2;
	}

	if (i > COLNO - 2) {
		putstr(datawin, 0, buf);
		buf[0] = 0;
	}
	if (*str) {
		Strcat(buf, str);
		Strcat(buf, ", ");
	} else {
		putstr(datawin, 0, str);
		free(buf),  buf = 0;
	}
	return;
}
