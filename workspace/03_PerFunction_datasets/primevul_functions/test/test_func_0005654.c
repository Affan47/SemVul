int mbedtls_ssl_decrypt_buf( mbedtls_ssl_context const *ssl,
                             mbedtls_ssl_transform *transform,
                             mbedtls_record *rec )
{
    size_t olen;
    mbedtls_cipher_mode_t mode;
    int ret, auth_done = 0;
#if defined(MBEDTLS_SSL_SOME_MODES_USE_MAC)
    size_t padlen = 0, correct = 1;
#endif
    unsigned char* data;
    unsigned char add_data[13 + 1 + MBEDTLS_SSL_CID_IN_LEN_MAX ];
    size_t add_data_len;

#if !defined(MBEDTLS_DEBUG_C)
    ssl = NULL;
    ((void) ssl);
#endif

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> decrypt buf" ) );
    if( rec == NULL                     ||
        rec->buf == NULL                ||
        rec->buf_len < rec->data_offset ||
        rec->buf_len - rec->data_offset < rec->data_len )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad record structure provided to decrypt_buf" ) );
        return( MBEDTLS_ERR_SSL_INTERNAL_ERROR );
    }

    data = rec->buf + rec->data_offset;
    mode = mbedtls_cipher_get_cipher_mode( &transform->cipher_ctx_dec );

#if defined(MBEDTLS_SSL_DTLS_CONNECTION_ID)


    if( rec->cid_len != transform->in_cid_len ||
        memcmp( rec->cid, transform->in_cid, rec->cid_len ) != 0 )
    {
        return( MBEDTLS_ERR_SSL_UNEXPECTED_CID );
    }
#endif

#if defined(MBEDTLS_ARC4_C) || defined(MBEDTLS_CIPHER_NULL_CIPHER)
    if( mode == MBEDTLS_MODE_STREAM )
    {
        padlen = 0;
        if( ( ret = mbedtls_cipher_crypt( &transform->cipher_ctx_dec,
                                   transform->iv_dec,
                                   transform->ivlen,
                                   data, rec->data_len,
                                   data, &olen ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_cipher_crypt", ret );
            return( ret );
        }

        if( rec->data_len != olen )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "should never happen" ) );
            return( MBEDTLS_ERR_SSL_INTERNAL_ERROR );
        }
    }
    else
#endif
#if defined(MBEDTLS_GCM_C) || \
    defined(MBEDTLS_CCM_C) || \
    defined(MBEDTLS_CHACHAPOLY_C)
    if( mode == MBEDTLS_MODE_GCM ||
        mode == MBEDTLS_MODE_CCM ||
        mode == MBEDTLS_MODE_CHACHAPOLY )
    {
        unsigned char iv[12];
        unsigned char *dynamic_iv;
        size_t dynamic_iv_len;


        dynamic_iv_len = sizeof( rec->ctr );
        if( ssl_transform_aead_dynamic_iv_is_explicit( transform ) == 1 )
        {
            if( rec->data_len < dynamic_iv_len )
            {
                MBEDTLS_SSL_DEBUG_MSG( 1, ( "msglen (%" MBEDTLS_PRINTF_SIZET
                                            " ) < explicit_iv_len (%" MBEDTLS_PRINTF_SIZET ") ",
                                            rec->data_len,
                                            dynamic_iv_len ) );
                return( MBEDTLS_ERR_SSL_INVALID_MAC );
            }
            dynamic_iv = data;

            data += dynamic_iv_len;
            rec->data_offset += dynamic_iv_len;
            rec->data_len    -= dynamic_iv_len;
        }
        else
        {
            dynamic_iv = rec->ctr;
        }


        if( rec->data_len < transform->taglen )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "msglen (%" MBEDTLS_PRINTF_SIZET
                                        ") < taglen (%" MBEDTLS_PRINTF_SIZET ") ",
                                        rec->data_len,
                                        transform->taglen ) );
            return( MBEDTLS_ERR_SSL_INVALID_MAC );
        }
        rec->data_len -= transform->taglen;


        ssl_build_record_nonce( iv, sizeof( iv ),
                                transform->iv_dec,
                                transform->fixed_ivlen,
                                dynamic_iv,
                                dynamic_iv_len );


        ssl_extract_add_data_from_record( add_data, &add_data_len, rec,
                                          transform->minor_ver );
        MBEDTLS_SSL_DEBUG_BUF( 4, "additional data used for AEAD",
                               add_data, add_data_len );


        MBEDTLS_SSL_DEBUG_BUF( 4, "IV used", iv, transform->ivlen );
        MBEDTLS_SSL_DEBUG_BUF( 4, "TAG used", data + rec->data_len,
                               transform->taglen );


        if( ( ret = mbedtls_cipher_auth_decrypt_ext( &transform->cipher_ctx_dec,
                  iv, transform->ivlen,
                  add_data, add_data_len,
                  data, rec->data_len + transform->taglen,
                  data, rec->buf_len - (data - rec->buf), &olen,
                  transform->taglen ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_cipher_auth_decrypt", ret );

            if( ret == MBEDTLS_ERR_CIPHER_AUTH_FAILED )
                return( MBEDTLS_ERR_SSL_INVALID_MAC );

            return( ret );
        }
        auth_done++;


        if( olen != rec->data_len )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "should never happen" ) );
            return( MBEDTLS_ERR_SSL_INTERNAL_ERROR );
        }
    }
    else
#endif
#if defined(MBEDTLS_SSL_SOME_SUITES_USE_CBC)
    if( mode == MBEDTLS_MODE_CBC )
    {
        size_t minlen = 0;


#if defined(MBEDTLS_SSL_PROTO_TLS1_1) || defined(MBEDTLS_SSL_PROTO_TLS1_2)
        if( transform->minor_ver >= MBEDTLS_SSL_MINOR_VERSION_2 )
        {

            minlen += transform->ivlen;
        }
#endif


        if( rec->data_len < minlen + transform->ivlen ||
            rec->data_len < minlen + transform->maclen + 1 )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "msglen (%" MBEDTLS_PRINTF_SIZET
                                        ") < max( ivlen(%" MBEDTLS_PRINTF_SIZET
                                        "), maclen (%" MBEDTLS_PRINTF_SIZET ") "
                                "+ 1 ) ( + expl IV )", rec->data_len,
                                transform->ivlen,
                                transform->maclen ) );
            return( MBEDTLS_ERR_SSL_INVALID_MAC );
        }


#if defined(MBEDTLS_SSL_ENCRYPT_THEN_MAC)
        if( transform->encrypt_then_mac == MBEDTLS_SSL_ETM_ENABLED )
        {
            unsigned char mac_expect[MBEDTLS_SSL_MAC_ADD];

            MBEDTLS_SSL_DEBUG_MSG( 3, ( "using encrypt then mac" ) );


            rec->data_len -= transform->maclen;
            ssl_extract_add_data_from_record( add_data, &add_data_len, rec,
                                              transform->minor_ver );


            MBEDTLS_SSL_DEBUG_BUF( 4, "MAC'd meta-data", add_data,
                                   add_data_len );
            ret = mbedtls_md_hmac_update( &transform->md_ctx_dec, add_data,
                                          add_data_len );
            if( ret != 0 )
                goto hmac_failed_etm_enabled;
            ret = mbedtls_md_hmac_update( &transform->md_ctx_dec,
                                    data, rec->data_len );
            if( ret != 0 )
                goto hmac_failed_etm_enabled;
            ret = mbedtls_md_hmac_finish( &transform->md_ctx_dec, mac_expect );
            if( ret != 0 )
                goto hmac_failed_etm_enabled;
            ret = mbedtls_md_hmac_reset( &transform->md_ctx_dec );
            if( ret != 0 )
                goto hmac_failed_etm_enabled;

            MBEDTLS_SSL_DEBUG_BUF( 4, "message  mac", data + rec->data_len,
                                   transform->maclen );
            MBEDTLS_SSL_DEBUG_BUF( 4, "expected mac", mac_expect,
                                   transform->maclen );


            if( mbedtls_ct_memcmp( data + rec->data_len, mac_expect,
                                              transform->maclen ) != 0 )
            {
                MBEDTLS_SSL_DEBUG_MSG( 1, ( "message mac does not match" ) );
                ret = MBEDTLS_ERR_SSL_INVALID_MAC;
                goto hmac_failed_etm_enabled;
            }
            auth_done++;

        hmac_failed_etm_enabled:
            mbedtls_platform_zeroize( mac_expect, transform->maclen );
            if( ret != 0 )
            {
                if( ret != MBEDTLS_ERR_SSL_INVALID_MAC )
                    MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_hmac_xxx", ret );
                return( ret );
            }
        }
#endif


        if( rec->data_len % transform->ivlen != 0 )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "msglen (%" MBEDTLS_PRINTF_SIZET
                                        ") %% ivlen (%" MBEDTLS_PRINTF_SIZET ") != 0",
                                        rec->data_len, transform->ivlen ) );
            return( MBEDTLS_ERR_SSL_INVALID_MAC );
        }

#if defined(MBEDTLS_SSL_PROTO_TLS1_1) || defined(MBEDTLS_SSL_PROTO_TLS1_2)


        if( transform->minor_ver >= MBEDTLS_SSL_MINOR_VERSION_2 )
        {

            memcpy( transform->iv_dec, data, transform->ivlen );

            data += transform->ivlen;
            rec->data_offset += transform->ivlen;
            rec->data_len -= transform->ivlen;
        }
#endif


        if( ( ret = mbedtls_cipher_crypt( &transform->cipher_ctx_dec,
                                   transform->iv_dec, transform->ivlen,
                                   data, rec->data_len, data, &olen ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_cipher_crypt", ret );
            return( ret );
        }


        if( rec->data_len != olen )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "should never happen" ) );
            return( MBEDTLS_ERR_SSL_INTERNAL_ERROR );
        }

#if defined(MBEDTLS_SSL_PROTO_SSL3) || defined(MBEDTLS_SSL_PROTO_TLS1)
        if( transform->minor_ver < MBEDTLS_SSL_MINOR_VERSION_2 )
        {


            memcpy( transform->iv_dec, transform->cipher_ctx_dec.iv,
                    transform->ivlen );
        }
#endif


        padlen = data[rec->data_len - 1];

        if( auth_done == 1 )
        {
            const size_t mask = mbedtls_ct_size_mask_ge(
                                rec->data_len,
                                padlen + 1 );
            correct &= mask;
            padlen  &= mask;
        }
        else
        {
#if defined(MBEDTLS_SSL_DEBUG_ALL)
            if( rec->data_len < transform->maclen + padlen + 1 )
            {
                MBEDTLS_SSL_DEBUG_MSG( 1, ( "msglen (%" MBEDTLS_PRINTF_SIZET
                                            ") < maclen (%" MBEDTLS_PRINTF_SIZET
                                            ") + padlen (%" MBEDTLS_PRINTF_SIZET ")",
                                            rec->data_len,
                                            transform->maclen,
                                            padlen + 1 ) );
            }
#endif

            const size_t mask = mbedtls_ct_size_mask_ge(
                                rec->data_len,
                                transform->maclen + padlen + 1 );
            correct &= mask;
            padlen  &= mask;
        }

        padlen++;


#if defined(MBEDTLS_SSL_PROTO_SSL3)
        if( transform->minor_ver == MBEDTLS_SSL_MINOR_VERSION_0 )
        {


            if( padlen > transform->ivlen )
            {
#if defined(MBEDTLS_SSL_DEBUG_ALL)
                MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad padding length: is %" MBEDTLS_PRINTF_SIZET ", "
                                            "should be no more than %" MBEDTLS_PRINTF_SIZET,
                                            padlen, transform->ivlen ) );
#endif
                correct = 0;
            }
        }
        else
#endif
#if defined(MBEDTLS_SSL_PROTO_TLS1) || defined(MBEDTLS_SSL_PROTO_TLS1_1) || \
    defined(MBEDTLS_SSL_PROTO_TLS1_2)
        if( transform->minor_ver > MBEDTLS_SSL_MINOR_VERSION_0 )
        {


            size_t pad_count = 0;
            volatile unsigned char* const check = data;


            size_t const padding_idx = rec->data_len - padlen;
            size_t const num_checks = rec->data_len <= 256 ? rec->data_len : 256;
            size_t const start_idx = rec->data_len - num_checks;
            size_t idx;

            for( idx = start_idx; idx < rec->data_len; idx++ )
            {


                const size_t mask = mbedtls_ct_size_mask_ge( idx, padding_idx );
                const size_t equal = mbedtls_ct_size_bool_eq( check[idx],
                                                              padlen - 1 );
                pad_count += mask & equal;
            }
            correct &= mbedtls_ct_size_bool_eq( pad_count, padlen );

#if defined(MBEDTLS_SSL_DEBUG_ALL)
            if( padlen > 0 && correct == 0 )
                MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad padding byte detected" ) );
#endif
            padlen &= mbedtls_ct_size_mask( correct );
        }
        else
#endif

        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "should never happen" ) );
            return( MBEDTLS_ERR_SSL_INTERNAL_ERROR );
        }


        rec->data_len -= padlen;
    }
    else
#endif
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "should never happen" ) );
        return( MBEDTLS_ERR_SSL_INTERNAL_ERROR );
    }

#if defined(MBEDTLS_SSL_DEBUG_ALL)
    MBEDTLS_SSL_DEBUG_BUF( 4, "raw buffer after decryption",
                           data, rec->data_len );
#endif


#if defined(MBEDTLS_SSL_SOME_MODES_USE_MAC)
    if( auth_done == 0 )
    {
        unsigned char mac_expect[MBEDTLS_SSL_MAC_ADD] = { 0 };
        unsigned char mac_peer[MBEDTLS_SSL_MAC_ADD] = { 0 };


        rec->data_len -= transform->maclen;
        ssl_extract_add_data_from_record( add_data, &add_data_len, rec,
                                          transform->minor_ver );

#if defined(MBEDTLS_SSL_PROTO_SSL3)
        if( transform->minor_ver == MBEDTLS_SSL_MINOR_VERSION_0 )
        {
            ret = ssl_mac( &transform->md_ctx_dec,
                           transform->mac_dec,
                           data, rec->data_len,
                           rec->ctr, rec->type,
                           mac_expect );
            if( ret != 0 )
            {
                MBEDTLS_SSL_DEBUG_RET( 1, "ssl_mac", ret );
                goto hmac_failed_etm_disabled;
            }
            memcpy( mac_peer, data + rec->data_len, transform->maclen );
        }
        else
#endif
#if defined(MBEDTLS_SSL_PROTO_TLS1) || defined(MBEDTLS_SSL_PROTO_TLS1_1) || \
        defined(MBEDTLS_SSL_PROTO_TLS1_2)
        if( transform->minor_ver > MBEDTLS_SSL_MINOR_VERSION_0 )
        {


            const size_t max_len = rec->data_len + padlen;
            const size_t min_len = ( max_len > 256 ) ? max_len - 256 : 0;

            ret = mbedtls_ct_hmac( &transform->md_ctx_dec,
                                   add_data, add_data_len,
                                   data, rec->data_len, min_len, max_len,
                                   mac_expect );
            if( ret != 0 )
            {
                MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ct_hmac", ret );
                goto hmac_failed_etm_disabled;
            }

            mbedtls_ct_memcpy_offset( mac_peer, data,
                                      rec->data_len,
                                      min_len, max_len,
                                      transform->maclen );
        }
        else
#endif

        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "should never happen" ) );
            return( MBEDTLS_ERR_SSL_INTERNAL_ERROR );
        }

#if defined(MBEDTLS_SSL_DEBUG_ALL)
        MBEDTLS_SSL_DEBUG_BUF( 4, "expected mac", mac_expect, transform->maclen );
        MBEDTLS_SSL_DEBUG_BUF( 4, "message  mac", mac_peer, transform->maclen );
#endif

        if( mbedtls_ct_memcmp( mac_peer, mac_expect,
                                          transform->maclen ) != 0 )
        {
#if defined(MBEDTLS_SSL_DEBUG_ALL)
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "message mac does not match" ) );
#endif
            correct = 0;
        }
        auth_done++;

    hmac_failed_etm_disabled:
        mbedtls_platform_zeroize( mac_peer, transform->maclen );
        mbedtls_platform_zeroize( mac_expect, transform->maclen );
        if( ret != 0 )
            return( ret );
    }


    if( correct == 0 )
        return( MBEDTLS_ERR_SSL_INVALID_MAC );
#endif


    if( auth_done != 1 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "should never happen" ) );
        return( MBEDTLS_ERR_SSL_INTERNAL_ERROR );
    }

#if defined(MBEDTLS_SSL_PROTO_TLS1_3_EXPERIMENTAL)
    if( transform->minor_ver == MBEDTLS_SSL_MINOR_VERSION_4 )
    {

        ret = ssl_parse_inner_plaintext( data, &rec->data_len,
                                         &rec->type );

        if( ret != 0 )
            return( MBEDTLS_ERR_SSL_INVALID_RECORD );
    }
#endif

#if defined(MBEDTLS_SSL_DTLS_CONNECTION_ID)
    if( rec->cid_len != 0 )
    {
        ret = ssl_parse_inner_plaintext( data, &rec->data_len,
                                         &rec->type );
        if( ret != 0 )
            return( MBEDTLS_ERR_SSL_INVALID_RECORD );
    }
#endif

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= decrypt buf" ) );

    return( 0 );
}
