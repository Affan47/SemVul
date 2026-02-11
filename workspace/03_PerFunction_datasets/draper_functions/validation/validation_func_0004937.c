detransdir(dir, buf, ptr)
CONST char *dir;
char *buf;
int ptr;
{
	char *cp, *next;
	int dlen, flen;

	while (dir) {
		dlen = ptr;
		buf[ptr++] = _SC_;
		if ((next = strdelim(dir, 0))) flen = next++ - dir;
		else flen = strlen(dir);

		if (!inittrans(buf, dlen)) cp = NULL;
		else cp = detransfile(dir, flen, buf, ptr);
		if (!cp) cp = Xstrncpy(&(buf[ptr]), dir, flen);
		ptr = cp - buf;
		dir = next;
	}

	return(&(buf[ptr]));
}
