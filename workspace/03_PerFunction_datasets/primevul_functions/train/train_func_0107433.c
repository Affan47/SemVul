int ssl_derive_keys( ssl_context *ssl )
{
    int ret = 0;
    unsigned char tmp[64];
    unsigned char keyblk[256];
    unsigned char *key1;
    unsigned char *key2;
    unsigned char *mac_enc;
    unsigned char *mac_dec;
    size_t iv_copy_len;
    const cipher_info_t *cipher_info;
    const md_info_t *md_info;

    ssl_session *session = ssl->session_negotiate;
    ssl_transform *transform = ssl->transform_negotiate;
    ssl_handshake_params *handshake = ssl->handshake;

    SSL_DEBUG_MSG( 2, ( "=> derive keys" ) );

    cipher_info = cipher_info_from_type( transform->ciphersuite_info->cipher );
    if( cipher_info == NULL )
    {
        SSL_DEBUG_MSG( 1, ( "cipher info for %d not found",
                            transform->ciphersuite_info->cipher ) );
        return( POLARSSL_ERR_SSL_BAD_INPUT_DATA );
    }

    md_info = md_info_from_type( transform->ciphersuite_info->mac );
    if( md_info == NULL )
    {
        SSL_DEBUG_MSG( 1, ( "md info for %d not found",
                            transform->ciphersuite_info->mac ) );
        return( POLARSSL_ERR_SSL_BAD_INPUT_DATA );
    }


#if defined(POLARSSL_SSL_PROTO_SSL3)
    if( ssl->minor_ver == SSL_MINOR_VERSION_0 )
    {
        handshake->tls_prf = ssl3_prf;
        handshake->calc_verify = ssl_calc_verify_ssl;
        handshake->calc_finished = ssl_calc_finished_ssl;
    }
    else
#endif
#if defined(POLARSSL_SSL_PROTO_TLS1) || defined(POLARSSL_SSL_PROTO_TLS1_1)
    if( ssl->minor_ver < SSL_MINOR_VERSION_3 )
    {
        handshake->tls_prf = tls1_prf;
        handshake->calc_verify = ssl_calc_verify_tls;
        handshake->calc_finished = ssl_calc_finished_tls;
    }
    else
#endif
#if defined(POLARSSL_SSL_PROTO_TLS1_2)
#if defined(POLARSSL_SHA512_C)
    if( ssl->minor_ver == SSL_MINOR_VERSION_3 &&
        transform->ciphersuite_info->mac == POLARSSL_MD_SHA384 )
    {
        handshake->tls_prf = tls_prf_sha384;
        handshake->calc_verify = ssl_calc_verify_tls_sha384;
        handshake->calc_finished = ssl_calc_finished_tls_sha384;
    }
    else
#endif
#if defined(POLARSSL_SHA256_C)
    if( ssl->minor_ver == SSL_MINOR_VERSION_3 )
    {
        handshake->tls_prf = tls_prf_sha256;
        handshake->calc_verify = ssl_calc_verify_tls_sha256;
        handshake->calc_finished = ssl_calc_finished_tls_sha256;
    }
    else
#endif
#endif
    {
        SSL_DEBUG_MSG( 1, ( "should never happen" ) );
        return( POLARSSL_ERR_SSL_INTERNAL_ERROR );
    }


    if( handshake->resume == 0 )
    {
        SSL_DEBUG_BUF( 3, "premaster secret", handshake->premaster,
                       handshake->pmslen );

#if defined(POLARSSL_SSL_EXTENDED_MASTER_SECRET)
        if( ssl->handshake->extended_ms == SSL_EXTENDED_MS_ENABLED )
        {
            unsigned char session_hash[48];
            size_t hash_len;

            SSL_DEBUG_MSG( 3, ( "using extended master secret" ) );

            ssl->handshake->calc_verify( ssl, session_hash );

#if defined(POLARSSL_SSL_PROTO_TLS1_2)
            if( ssl->minor_ver == SSL_MINOR_VERSION_3 )
            {
#if defined(POLARSSL_SHA512_C)
                if( ssl->transform_negotiate->ciphersuite_info->mac ==
                    POLARSSL_MD_SHA384 )
                {
                    hash_len = 48;
                }
                else
#endif
                    hash_len = 32;
            }
            else
#endif
                hash_len = 36;

            SSL_DEBUG_BUF( 3, "session hash", session_hash, hash_len );

            handshake->tls_prf( handshake->premaster, handshake->pmslen,
                                "extended master secret",
                                session_hash, hash_len, session->master, 48 );

        }
        else
#endif
        handshake->tls_prf( handshake->premaster, handshake->pmslen,
                            "master secret",
                            handshake->randbytes, 64, session->master, 48 );


        polarssl_zeroize( handshake->premaster, sizeof(handshake->premaster) );
    }
    else
        SSL_DEBUG_MSG( 3, ( "no premaster (session resumed)" ) );


    memcpy( tmp, handshake->randbytes, 64 );
    memcpy( handshake->randbytes, tmp + 32, 32 );
    memcpy( handshake->randbytes + 32, tmp, 32 );
    polarssl_zeroize( tmp, sizeof( tmp ) );


    handshake->tls_prf( session->master, 48, "key expansion",
                        handshake->randbytes, 64, keyblk, 256 );

    SSL_DEBUG_MSG( 3, ( "ciphersuite = %s",
                   ssl_get_ciphersuite_name( session->ciphersuite ) ) );
    SSL_DEBUG_BUF( 3, "master secret", session->master, 48 );
    SSL_DEBUG_BUF( 4, "random bytes", handshake->randbytes, 64 );
    SSL_DEBUG_BUF( 4, "key block", keyblk, 256 );

    polarssl_zeroize( handshake->randbytes, sizeof( handshake->randbytes ) );


    transform->keylen = cipher_info->key_length / 8;

    if( cipher_info->mode == POLARSSL_MODE_GCM ||
        cipher_info->mode == POLARSSL_MODE_CCM )
    {
        transform->maclen = 0;

        transform->ivlen = 12;
        transform->fixed_ivlen = 4;


        transform->minlen = transform->ivlen - transform->fixed_ivlen
                            + ( transform->ciphersuite_info->flags &
                                POLARSSL_CIPHERSUITE_SHORT_TAG ? 8 : 16 );
    }
    else
    {

        if( ( ret = md_init_ctx( &transform->md_ctx_enc, md_info ) ) != 0 ||
            ( ret = md_init_ctx( &transform->md_ctx_dec, md_info ) ) != 0 )
        {
            SSL_DEBUG_RET( 1, "md_init_ctx", ret );
            return( ret );
        }


        transform->maclen = md_get_size( md_info );

#if defined(POLARSSL_SSL_TRUNCATED_HMAC)


        if( session->trunc_hmac == SSL_TRUNC_HMAC_ENABLED )
            transform->maclen = SSL_TRUNCATED_HMAC_LEN;
#endif


        transform->ivlen = cipher_info->iv_size;


        if( cipher_info->mode == POLARSSL_MODE_STREAM )
            transform->minlen = transform->maclen;
        else
        {


#if defined(POLARSSL_SSL_ENCRYPT_THEN_MAC)
            if( session->encrypt_then_mac == SSL_ETM_ENABLED )
            {
                transform->minlen = transform->maclen
                                  + cipher_info->block_size;
            }
            else
#endif
            {
                transform->minlen = transform->maclen
                                  + cipher_info->block_size
                                  - transform->maclen % cipher_info->block_size;
            }

#if defined(POLARSSL_SSL_PROTO_SSL3) || defined(POLARSSL_SSL_PROTO_TLS1)
            if( ssl->minor_ver == SSL_MINOR_VERSION_0 ||
                ssl->minor_ver == SSL_MINOR_VERSION_1 )
                ;
            else
#endif
#if defined(POLARSSL_SSL_PROTO_TLS1_1) || defined(POLARSSL_SSL_PROTO_TLS1_2)
            if( ssl->minor_ver == SSL_MINOR_VERSION_2 ||
                ssl->minor_ver == SSL_MINOR_VERSION_3 )
            {
                transform->minlen += transform->ivlen;
            }
            else
#endif
            {
                SSL_DEBUG_MSG( 1, ( "should never happen" ) );
                return( POLARSSL_ERR_SSL_INTERNAL_ERROR );
            }
        }
    }

    SSL_DEBUG_MSG( 3, ( "keylen: %d, minlen: %d, ivlen: %d, maclen: %d",
                   transform->keylen, transform->minlen, transform->ivlen,
                   transform->maclen ) );


#if defined(POLARSSL_SSL_CLI_C)
    if( ssl->endpoint == SSL_IS_CLIENT )
    {
        key1 = keyblk + transform->maclen * 2;
        key2 = keyblk + transform->maclen * 2 + transform->keylen;

        mac_enc = keyblk;
        mac_dec = keyblk + transform->maclen;


        iv_copy_len = ( transform->fixed_ivlen ) ?
                            transform->fixed_ivlen : transform->ivlen;
        memcpy( transform->iv_enc, key2 + transform->keylen,  iv_copy_len );
        memcpy( transform->iv_dec, key2 + transform->keylen + iv_copy_len,
                iv_copy_len );
    }
    else
#endif
#if defined(POLARSSL_SSL_SRV_C)
    if( ssl->endpoint == SSL_IS_SERVER )
    {
        key1 = keyblk + transform->maclen * 2 + transform->keylen;
        key2 = keyblk + transform->maclen * 2;

        mac_enc = keyblk + transform->maclen;
        mac_dec = keyblk;


        iv_copy_len = ( transform->fixed_ivlen ) ?
                            transform->fixed_ivlen : transform->ivlen;
        memcpy( transform->iv_dec, key1 + transform->keylen,  iv_copy_len );
        memcpy( transform->iv_enc, key1 + transform->keylen + iv_copy_len,
                iv_copy_len );
    }
    else
#endif
    {
        SSL_DEBUG_MSG( 1, ( "should never happen" ) );
        return( POLARSSL_ERR_SSL_INTERNAL_ERROR );
    }

#if defined(POLARSSL_SSL_PROTO_SSL3)
    if( ssl->minor_ver == SSL_MINOR_VERSION_0 )
    {
        if( transform->maclen > sizeof transform->mac_enc )
        {
            SSL_DEBUG_MSG( 1, ( "should never happen" ) );
            return( POLARSSL_ERR_SSL_INTERNAL_ERROR );
        }

        memcpy( transform->mac_enc, mac_enc, transform->maclen );
        memcpy( transform->mac_dec, mac_dec, transform->maclen );
    }
    else
#endif
#if defined(POLARSSL_SSL_PROTO_TLS1) || defined(POLARSSL_SSL_PROTO_TLS1_1) || \
    defined(POLARSSL_SSL_PROTO_TLS1_2)
    if( ssl->minor_ver >= SSL_MINOR_VERSION_1 )
    {
        md_hmac_starts( &transform->md_ctx_enc, mac_enc, transform->maclen );
        md_hmac_starts( &transform->md_ctx_dec, mac_dec, transform->maclen );
    }
    else
#endif
    {
        SSL_DEBUG_MSG( 1, ( "should never happen" ) );
        return( POLARSSL_ERR_SSL_INTERNAL_ERROR );
    }

#if defined(POLARSSL_SSL_HW_RECORD_ACCEL)
    if( ssl_hw_record_init != NULL )
    {
        int ret = 0;

        SSL_DEBUG_MSG( 2, ( "going for ssl_hw_record_init()" ) );

        if( ( ret = ssl_hw_record_init( ssl, key1, key2, transform->keylen,
                                        transform->iv_enc, transform->iv_dec,
                                        iv_copy_len,
                                        mac_enc, mac_dec,
                                        transform->maclen ) ) != 0 )
        {
            SSL_DEBUG_RET( 1, "ssl_hw_record_init", ret );
            return( POLARSSL_ERR_SSL_HW_ACCEL_FAILED );
        }
    }
#endif

    if( ( ret = cipher_init_ctx( &transform->cipher_ctx_enc,
                                 cipher_info ) ) != 0 )
    {
        SSL_DEBUG_RET( 1, "cipher_init_ctx", ret );
        return( ret );
    }

    if( ( ret = cipher_init_ctx( &transform->cipher_ctx_dec,
                                 cipher_info ) ) != 0 )
    {
        SSL_DEBUG_RET( 1, "cipher_init_ctx", ret );
        return( ret );
    }

    if( ( ret = cipher_setkey( &transform->cipher_ctx_enc, key1,
                               cipher_info->key_length,
                               POLARSSL_ENCRYPT ) ) != 0 )
    {
        SSL_DEBUG_RET( 1, "cipher_setkey", ret );
        return( ret );
    }

    if( ( ret = cipher_setkey( &transform->cipher_ctx_dec, key2,
                               cipher_info->key_length,
                               POLARSSL_DECRYPT ) ) != 0 )
    {
        SSL_DEBUG_RET( 1, "cipher_setkey", ret );
        return( ret );
    }

#if defined(POLARSSL_CIPHER_MODE_CBC)
    if( cipher_info->mode == POLARSSL_MODE_CBC )
    {
        if( ( ret = cipher_set_padding_mode( &transform->cipher_ctx_enc,
                                             POLARSSL_PADDING_NONE ) ) != 0 )
        {
            SSL_DEBUG_RET( 1, "cipher_set_padding_mode", ret );
            return( ret );
        }

        if( ( ret = cipher_set_padding_mode( &transform->cipher_ctx_dec,
                                             POLARSSL_PADDING_NONE ) ) != 0 )
        {
            SSL_DEBUG_RET( 1, "cipher_set_padding_mode", ret );
            return( ret );
        }
    }
#endif

    polarssl_zeroize( keyblk, sizeof( keyblk ) );

#if defined(POLARSSL_ZLIB_SUPPORT)


    if( session->compression == SSL_COMPRESS_DEFLATE )
    {
        if( ssl->compress_buf == NULL )
        {
            SSL_DEBUG_MSG( 3, ( "Allocating compression buffer" ) );
            ssl->compress_buf = polarssl_malloc( SSL_BUFFER_LEN );
            if( ssl->compress_buf == NULL )
            {
                SSL_DEBUG_MSG( 1, ( "malloc(%d bytes) failed",
                                    SSL_BUFFER_LEN ) );
                return( POLARSSL_ERR_SSL_MALLOC_FAILED );
            }
        }

        SSL_DEBUG_MSG( 3, ( "Initializing zlib states" ) );

        memset( &transform->ctx_deflate, 0, sizeof( transform->ctx_deflate ) );
        memset( &transform->ctx_inflate, 0, sizeof( transform->ctx_inflate ) );

        if( deflateInit( &transform->ctx_deflate,
                         Z_DEFAULT_COMPRESSION )   != Z_OK ||
            inflateInit( &transform->ctx_inflate ) != Z_OK )
        {
            SSL_DEBUG_MSG( 1, ( "Failed to initialize compression" ) );
            return( POLARSSL_ERR_SSL_COMPRESSION_FAILED );
        }
    }
#endif

    SSL_DEBUG_MSG( 2, ( "<= derive keys" ) );

    return( 0 );
}
