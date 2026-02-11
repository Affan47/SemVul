crypto_aead_decrypt(
  unsigned char *m, unsigned long long *mlen,
  unsigned char *nsec,
  const unsigned char *c, unsigned long long clen,
  const unsigned char *ad, unsigned long long adlen,
  const unsigned char *npub,
  const unsigned char *k
)
{


	u8 TA[16], TE[16], T[CRYPTO_ABYTES];
	int j;

	memcpy((void*)T, (void*)&c[clen-CRYPTO_ABYTES], CRYPTO_ABYTES);
	if (adlen) {
		AD128(ad, adlen, k, TA);
	}
	DF128(npub, c, clen-CRYPTO_ABYTES, k, m, TE);
	if (adlen) {
		for (j=0; j<16; j++)
			TE[j] ^= TA[j];
	}
	*mlen = clen-CRYPTO_ABYTES;
	if (memcmp((void*)TE, (void*)T, CRYPTO_ABYTES))
		return -1;

	return 0;
}
