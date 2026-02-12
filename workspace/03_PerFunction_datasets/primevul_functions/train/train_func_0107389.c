void ssl_handshake_free( ssl_handshake_params *handshake )
{
    if( handshake == NULL )
        return;

#if defined(POLARSSL_DHM_C)
    dhm_free( &handshake->dhm_ctx );
#endif
#if defined(POLARSSL_ECDH_C)
    ecdh_free( &handshake->ecdh_ctx );
#endif

#if defined(POLARSSL_ECDH_C) || defined(POLARSSL_ECDSA_C)

    polarssl_free( (void *) handshake->curves );
#endif

#if defined(POLARSSL_X509_CRT_PARSE_C) && \
    defined(POLARSSL_SSL_SERVER_NAME_INDICATION)


    if( handshake->sni_key_cert != NULL )
    {
        ssl_key_cert *cur = handshake->sni_key_cert, *next;

        while( cur != NULL )
        {
            next = cur->next;
            polarssl_free( cur );
            cur = next;
        }
    }
#endif

    polarssl_zeroize( handshake, sizeof( ssl_handshake_params ) );
}
