ctob64(unsigned char *p, int pad)
{
	static signed char b64[4];

	b64[0] = b64table[p[0] >> 2];
	b64[1] = b64table[((p[0] & 0x3) << 4) | ((p[1] & 0xF0) >> 4)];
	if (pad == 2) {
		b64[1] = b64table[(p[0] & 0x3) << 4];
		b64[2] = b64[3] = '=';
	} else if (pad == 1) {
		b64[2] = b64table[((p[1] & 0xF) << 2)];
		b64[3] = '=';
	} else {
		b64[2] = b64table[((p[1] & 0xF) << 2) | ((p[2] & 0xC0) >> 6)];
		b64[3] = b64table[p[2] & 0x3F];
	}
	return b64;
}
