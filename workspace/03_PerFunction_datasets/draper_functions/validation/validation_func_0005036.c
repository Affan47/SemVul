md5_hmac(unsigned char *digest,
	 const unsigned char* text, int text_len,
	 const unsigned char* key, int key_len)
{
	MD5_CONTEXT context;
	unsigned char k_ipad[64];


	unsigned char k_opad[64];


	int i;


	memset(k_ipad, 0, sizeof k_ipad);
	memset(k_opad, 0, sizeof k_opad);
	if (key_len > 64) {

		MD5_CONTEXT tctx;

		md5_init(&tctx);
		md5_update(&tctx, key, key_len);
		md5_final(k_ipad, &tctx);
		md5_final(k_opad, &tctx);
	} else {
		memcpy(k_ipad, key, key_len);
		memcpy(k_opad, key, key_len);
	}


	for (i = 0; i < 64; i++) {
		k_ipad[i] ^= 0x36;
		k_opad[i] ^= 0x5c;
	}


	md5_init(&context);

	md5_update(&context, k_ipad, 64);
	md5_update(&context, text, text_len);
	md5_final(digest, &context);


	md5_init(&context);

	md5_update(&context, k_opad, 64);
	md5_update(&context, digest, 16);

	md5_final(digest, &context);
}
