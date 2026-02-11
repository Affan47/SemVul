ast_base64encode_full(char *dst, const unsigned char *src, int srclen, int max, int linebreaks)
{
	int cnt = 0;
	int col = 0;
	unsigned int byte = 0;
	int bits = 0;
	int cntin = 0;

	max--;
	while ((cntin < srclen) && (cnt < max)) {
		byte <<= 8;
		byte |= *(src++);
		bits += 8;
		cntin++;
		if ((bits == 24) && (cnt + 4 <= max)) {
			*dst++ = base64[(byte >> 18) & 0x3f];
			*dst++ = base64[(byte >> 12) & 0x3f];
			*dst++ = base64[(byte >> 6) & 0x3f];
			*dst++ = base64[byte & 0x3f];
			cnt += 4;
			col += 4;
			bits = 0;
			byte = 0;
		}
		if (linebreaks && (cnt < max) && (col == 64)) {
			*dst++ = '\n';
			cnt++;
			col = 0;
		}
	}
	if (bits && (cnt + 4 <= max)) {


		byte <<= 24 - bits;
		*dst++ = base64[(byte >> 18) & 0x3f];
		*dst++ = base64[(byte >> 12) & 0x3f];
		if (bits == 16)
			*dst++ = base64[(byte >> 6) & 0x3f];
		else
			*dst++ = '=';
		*dst++ = '=';
		cnt += 4;
	}
	if (linebreaks && (cnt < max)) {
		*dst++ = '\n';
		cnt++;
	}
	*dst = '\0';
	return cnt;
}
