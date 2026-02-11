crypto_aead_encrypt(
  unsigned char *c, unsigned long long *clen,
  const unsigned char *m, unsigned long long mlen,
  const unsigned char *ad, unsigned long long adlen,
  const unsigned char *nsec,
  const unsigned char *npub,
  const unsigned char *k
)
{


	u8 TA[16], TE[16];
	int j;

	if (adlen) {
		AD128(ad, adlen, k, TA);
	}
	EF128(npub, m, mlen, k, c, TE);
	if (adlen) {
		for (j=0; j<16; j++)
			TE[j] ^= TA[j];
	}
	for (j=0; j<CRYPTO_ABYTES; j++)
		c[mlen+j] = TE[j];
	*clen = mlen+CRYPTO_ABYTES;

	return 0;
}
