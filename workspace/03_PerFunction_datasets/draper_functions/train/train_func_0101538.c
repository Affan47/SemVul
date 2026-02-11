rd_Z(Uint *n, int w, ftnlen len)
#endif
{
	long x[9];
	char *s, *s0, *s1, *se, *t;
	Const char *sc;
	int ch, i, w1, w2;
	static char hex[256];
	static int one = 1;
	int bad = 0;

	if (!hex['0']) {
		sc = "0123456789";
		while(ch = *sc++)
			hex[ch] = ch - '0' + 1;
		sc = "ABCDEF";
		while(ch = *sc++)
			hex[ch] = hex[ch + 'a' - 'A'] = ch - 'A' + 11;
		}
	s = s0 = (char *)x;
	s1 = (char *)&x[4];
	se = (char *)&x[8];
	if (len > 4*sizeof(long))
		return errno = 117;
	while (w) {
		GET(ch);
		if (ch==',' || ch=='\n')
			break;
		w--;
		if (ch > ' ') {
			if (!hex[ch & 0xff])
				bad++;
			*s++ = ch;
			if (s == se) {

				for(t = s0, s = s1; t < s1;)
					*t++ = *s++;
				s = s1;
				}
			}
		}
	if (bad)
		return errno = 115;
	w = (int)len;
	w1 = s - s0;
	w2 = w1+1 >> 1;
	t = (char *)n;
	if (*(char *)&one) {

		t += w - 1;
		i = -1;
		}
	else
		i = 1;
	for(; w > w2; t += i, --w)
		*t = 0;
	if (!w)
		return 0;
	if (w < w2)
		s0 = s - (w << 1);
	else if (w1 & 1) {
		*t = hex[*s0++ & 0xff] - 1;
		if (!--w)
			return 0;
		t += i;
		}
	do {
		*t = hex[*s0 & 0xff]-1 << 4 | hex[s0[1] & 0xff]-1;
		t += i;
		s0 += 2;
		}
		while(--w);
	return 0;
	}
