eckey_sign_wrap( void *ctx, md_type_t md_alg,
                   const unsigned char *hash, size_t hash_len,
                   unsigned char *sig, size_t *sig_len,
                   int (*f_rng)(void *, unsigned char *, size_t), void *p_rng )
{
    int ret;
    ecdsa_context ecdsa;

    ecdsa_init( &ecdsa );

    if( ( ret = ecdsa_from_keypair( &ecdsa, ctx ) ) == 0 )
        ret = ecdsa_sign_wrap( &ecdsa, md_alg, hash, hash_len, sig, sig_len,
                               f_rng, p_rng );

    ecdsa_free( &ecdsa );

    return( ret );
}
