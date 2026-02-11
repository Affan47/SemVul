UncheckedSetKey(const byte *key_string, unsigned int keylength, const NameValuePairs &)
{
	AssertValidKeyLength(keylength);

	unsigned i, j=0, k;
	word32 data, dspace[2] = {0, 0};

	memcpy(pbox, p_init, sizeof(p_init));
	memcpy(sbox, s_init, sizeof(s_init));


	for (i=0 ; i<ROUNDS+2 ; ++i)
	{
		data = 0 ;
		for (k=0 ; k<4 ; ++k )
			data = (data << 8) | key_string[j++ % keylength];
		pbox[i] ^= data;
	}

	crypt_block(dspace, pbox);

	for (i=0; i<ROUNDS; i+=2)
		crypt_block(pbox+i, pbox+i+2);

	crypt_block(pbox+ROUNDS, sbox);

	for (i=0; i<4*256-2; i+=2)
		crypt_block(sbox+i, sbox+i+2);

	if (!IsForwardTransformation())
		for (i=0; i<(ROUNDS+2)/2; i++)
			std::swap(pbox[i], pbox[ROUNDS+1-i]);
}
