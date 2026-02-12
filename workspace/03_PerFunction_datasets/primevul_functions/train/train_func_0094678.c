static void make_tunnel_passwd(uint8_t *output, int *outlen,
			       const uint8_t *input, int inlen, int room,
			       const char *secret, const uint8_t *vector)
{
	MD5_CTX context, old;
	uint8_t	digest[AUTH_VECTOR_LEN];
	uint8_t passwd[MAX_STRING_LEN + AUTH_VECTOR_LEN];
	int	i, n;
	int	len;


	room -= 2;
	room -= (room & 0x0f);
	room--;

	if (inlen > room) inlen = room;


	len = inlen + 1;
	if ((len & 0x0f) != 0) {
		len += 0x0f;
		len &= ~0x0f;
	}
	*outlen = len + 2;


	memcpy(passwd + 3, input, inlen);
	memset(passwd + 3 + inlen, 0, sizeof(passwd) - 3 - inlen);


	passwd[0] = (0x80 | ( ((salt_offset++) & 0x0f) << 3) |
		     (lrad_rand() & 0x07));
	passwd[1] = lrad_rand();
	passwd[2] = inlen;

	MD5Init(&context);
	MD5Update(&context, secret, strlen(secret));
	old = context;

	MD5Update(&context, vector, AUTH_VECTOR_LEN);
	MD5Update(&context, &passwd[0], 2);

	for (n = 0; n < len; n += AUTH_PASS_LEN) {
		if (n > 0) {
			context = old;
			MD5Update(&context,
				       passwd + 2 + n - AUTH_PASS_LEN,
				       AUTH_PASS_LEN);
		}

		MD5Final(digest, &context);
		for (i = 0; i < AUTH_PASS_LEN; i++) {
			passwd[i + 2 + n] ^= digest[i];
		}
	}
	memcpy(output, passwd, len + 2);
}
