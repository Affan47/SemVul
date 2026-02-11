Blowfish_expandstate(blf_ctx *c, const uint8_t *data, uint16_t databytes,
    const uint8_t *key, uint16_t keybytes)
{
	uint16_t i;
	uint16_t j;
	uint16_t k;
	uint32_t temp;
	uint32_t datal;
	uint32_t datar;

	j = 0;
	for (i = 0; i < BLF_N + 2; i++) {

		temp = Blowfish_stream2word(key, keybytes, &j);
		c->P[i] = c->P[i] ^ temp;
	}

	j = 0;
	datal = 0x00000000;
	datar = 0x00000000;
	for (i = 0; i < BLF_N + 2; i += 2) {
		datal ^= Blowfish_stream2word(data, databytes, &j);
		datar ^= Blowfish_stream2word(data, databytes, &j);
		Blowfish_encipher(c, &datal, &datar);

		c->P[i] = datal;
		c->P[i + 1] = datar;
	}

	for (i = 0; i < 4; i++) {
		for (k = 0; k < 256; k += 2) {
			datal ^= Blowfish_stream2word(data, databytes, &j);
			datar ^= Blowfish_stream2word(data, databytes, &j);
			Blowfish_encipher(c, &datal, &datar);

			c->S[i][k] = datal;
			c->S[i][k + 1] = datar;
		}
	}

}
