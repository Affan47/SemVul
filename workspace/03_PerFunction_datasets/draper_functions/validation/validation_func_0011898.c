pbkdf2_sha1_f ( const void *passphrase, size_t pass_len,
			    const void *salt, size_t salt_len,
			    int iterations, u32 blocknr, u8 *block )
{
	u8 pass[pass_len];
	u8 in[salt_len + 4];
	u8 last[SHA1_SIZE];
	u8 sha1_ctx[SHA1_CTX_SIZE];
	u8 *next_in = in;
	int next_size = sizeof ( in );
	int i, j;

	blocknr = htonl ( blocknr );

	memcpy ( pass, passphrase, pass_len );
	memcpy ( in, salt, salt_len );
	memcpy ( in + salt_len, &blocknr, 4 );
	memset ( block, 0, SHA1_SIZE );

	for ( i = 0; i < iterations; i++ ) {
		hmac_init ( &sha1_algorithm, sha1_ctx, pass, &pass_len );
		hmac_update ( &sha1_algorithm, sha1_ctx, next_in, next_size );
		hmac_final ( &sha1_algorithm, sha1_ctx, pass, &pass_len, last );

		for ( j = 0; j < SHA1_SIZE; j++ ) {
			block[j] ^= last[j];
		}

		next_in = last;
		next_size = SHA1_SIZE;
	}
}
