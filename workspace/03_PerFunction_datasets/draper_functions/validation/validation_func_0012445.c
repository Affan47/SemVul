ccmp_kie_mic ( const void *kck, const void *msg, size_t len,
			   void *mic )
{
	u8 sha1_ctx[SHA1_CTX_SIZE];
	u8 kckb[16];
	u8 hash[SHA1_SIZE];
	size_t kck_len = 16;

	memcpy ( kckb, kck, kck_len );

	hmac_init ( &sha1_algorithm, sha1_ctx, kckb, &kck_len );
	hmac_update ( &sha1_algorithm, sha1_ctx, msg, len );
	hmac_final ( &sha1_algorithm, sha1_ctx, kckb, &kck_len, hash );

	memcpy ( mic, hash, 16 );
}
