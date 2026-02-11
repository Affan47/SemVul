ftpgetreply(fp, sp)
XFILE *fp;
char **sp;
{
	char *cp, *buf;
	ALLOC_T len, size;
	int i, n, code;

	if (!(buf = ftprecv(fp))) return(-1);
	for (i = n = 0; i < 3; i++) {
		if (!Xisdigit(buf[i])) break;
		n *= 10;
		n += buf[i] - '0';
	}
	code = n;

	if (i < 3) {
		Xfree(buf);
		return(seterrno(EINVAL));
	}
	if (buf[3] == '-') {
		size = strlen(buf);
		for (;;) {
			if (!(cp = ftprecv(fp))) {
				Xfree(buf);
				return(-1);
			}
			for (i = n = 0; i < 3; i++) {
				if (!Xisdigit(cp[i])) break;
				n *= 10;
				n += cp[i] - '0';
			}
			if (i < 3 || cp[3] != ' ') n = -1;

			len = strlen(cp);
			buf = Xrealloc(buf, size + 1 + len + 1);
			buf[size++] = '\n';
			memcpy(&(buf[size]), cp, len + 1);
			size += len;
			Xfree(cp);
			if (n == code) break;
		}
	}
	if (sp) *sp = buf;
	else Xfree(buf);

	return(code);
}
