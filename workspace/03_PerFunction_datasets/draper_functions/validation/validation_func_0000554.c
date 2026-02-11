urldecode(s, len)
CONST char *s;
int len;
{
	char *cp;
	int i, j, n, c;

	if (!s) return(NULL);
	if (len < 0) len = strlen(s);
	cp = Xmalloc(len + 1);

	for (i = j = 0; i < len; i++, j++) {
		if (s[i] == '%') {
			cp[j] = '\0';
			for (n = 1; n <= 2; n++) {
				c = Xtolower(s[i + n]);
				if (Xisdigit(c)) c -= '0';
				else if (Xisxdigit(c)) c -= 'a' - 10;
				else break;
				cp[j] = ((cp[j]) << 4) + c;
			}
			if (n >= 2) {
				i += 2;
				continue;
			}
		}
		cp[j] = s[i];
	}
	cp[j++] = '\0';
	cp = Xrealloc(cp, j);

	return(cp);
}
