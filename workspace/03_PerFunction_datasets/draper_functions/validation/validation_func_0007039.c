read_aesd(fz_stream *stm, unsigned char *buf, int len)
{
	fz_aesd *state = stm->state;
	unsigned char *p = buf;
	unsigned char *ep = buf + len;

	while (state->ivcount < 16)
	{
		int c = fz_read_byte(state->chain);
		if (c < 0)
			fz_throw(stm->ctx, "premature end in aes filter");
		state->iv[state->ivcount++] = c;
	}

	while (state->rp < state->wp && p < ep)
		*p++ = *state->rp++;

	while (p < ep)
	{
		int n = fz_read(state->chain, state->bp, 16);
		if (n == 0)
			return p - buf;
		else if (n < 16)
			fz_throw(stm->ctx, "partial block in aes filter");

		aes_crypt_cbc(&state->aes, AES_DECRYPT, 16, state->iv, state->bp, state->bp);
		state->rp = state->bp;
		state->wp = state->bp + 16;


		if (fz_is_eof(state->chain))
		{
			int pad = state->bp[15];
			if (pad < 1 || pad > 16)
				fz_throw(stm->ctx, "aes padding out of range: %d", pad);
			state->wp -= pad;
		}

		while (state->rp < state->wp && p < ep)
			*p++ = *state->rp++;
	}

	return p - buf;
}
