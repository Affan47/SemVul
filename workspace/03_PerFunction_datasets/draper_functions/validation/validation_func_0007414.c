aes_wrap ( const void *kek, const void *src, void *dest, int nblk )
{
	u8 *A = dest;
	u8 B[16];
	u8 *R;
	int i, j;
	void *aes_ctx = malloc ( AES_CTX_SIZE );

	if ( ! aes_ctx )
		return -1;

	cipher_setkey ( &aes_algorithm, aes_ctx, kek, 16 );


	memset ( A, 0xA6, sizeof ( A ) );
	memmove ( dest + 8, src, nblk * 8 );


	for ( j = 0; j < 6; j++ ) {
		R = dest + 8;
		for ( i = 1; i <= nblk; i++ ) {
			memcpy ( B, A, 8 );
			memcpy ( B + 8, R, 8 );
			cipher_encrypt ( &aes_algorithm, aes_ctx, B, B, 16 );
			memcpy ( A, B, 8 );
			A[7] ^= ( nblk * j ) + i;
			memcpy ( R, B + 8, 8 );
			R += 8;
		}
	}

	free ( aes_ctx );
	return 0;
}
