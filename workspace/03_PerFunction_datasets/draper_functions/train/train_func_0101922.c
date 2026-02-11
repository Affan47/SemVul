md5_final_text(char *buf, MD5_CONTEXT *ctx)
{
	static const char *chars = "abcdefghijklmnopqrstuvwxyz234567";
	int bit;
	if (!ctx->finalized)
		do_final(ctx);
	for (bit = 0; bit < 16*8; bit += 5) {
		int first_char = bit / 8;
		int val = ctx->buf[first_char] >> (bit % 8);
		if (bit + 8 > (first_char + 1) * 8 && first_char < 15)
			val += ctx->buf[first_char + 1] << (8 - (bit % 8));
		*buf++ = chars[val & 0x1F];
	}
	*buf++ = 0;
}
