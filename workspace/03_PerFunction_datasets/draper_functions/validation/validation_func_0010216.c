convert(j1, j2, fp)
int j1, j2;
FILE *fp;
{
	int c1, c2;

	c1 = c2 = '\0';
	if (kanjicode == K_EUC) {
		if (j1) {
			c1 = (j1 | 0x80);
			c2 = (j2 | 0x80);
		}
		else if (j2 <= 0x20 || j2 >= 0x60) c2 = j2;
		else {
			c1 = 0x8e;
			c2 = (j2 | 0x80);
		}
	}
	else {
		if (j1) {
			c1 = ((j1 - 1) >> 1) + ((j1 < 0x5f) ? 0x71 : 0xb1);
			c2 = j2 + ((j1 & 1)
				? ((j2 < 0x60) ? 0x1f : 0x20) : 0x7e);
		}
		else if (j2 <= 0x20 || j2 >= 0x60) c2 = j2;
		else c2 = (j2 | 0x80);
#ifdef	WITHUTF8
		if (kanjicode == K_UTF8) {
			convertutf8(((u_int)c1 << 8) | c2, fp);
			c1 = c2 = '\0';
		}
#endif
	}

	if (c1) Xfputc(c1, fp);
	if (c2) Xfputc(c2, fp);
	if (c2 == '\\' && (prefix || msboff)) Xfputc('\\', fp);
}
