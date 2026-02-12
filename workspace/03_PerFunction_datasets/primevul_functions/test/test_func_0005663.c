int mbedtls_ssl_check_record( mbedtls_ssl_context const *ssl,
                              unsigned char *buf,
                              size_t buflen )
{
    int ret = 0;
    MBEDTLS_SSL_DEBUG_MSG( 1, ( "=> mbedtls_ssl_check_record" ) );
    MBEDTLS_SSL_DEBUG_BUF( 3, "record buffer", buf, buflen );


    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_STREAM )
    {
        ret = MBEDTLS_ERR_SSL_FEATURE_UNAVAILABLE;
        goto exit;
    }
#if defined(MBEDTLS_SSL_PROTO_DTLS)
    else
    {
        mbedtls_record rec;

        ret = ssl_parse_record_header( ssl, buf, buflen, &rec );
        if( ret != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 3, "ssl_parse_record_header", ret );
            goto exit;
        }

        if( ssl->transform_in != NULL )
        {
            ret = mbedtls_ssl_decrypt_buf( ssl, ssl->transform_in, &rec );
            if( ret != 0 )
            {
                MBEDTLS_SSL_DEBUG_RET( 3, "mbedtls_ssl_decrypt_buf", ret );
                goto exit;
            }
        }
    }
#endif

exit:


    mbedtls_platform_zeroize( buf, buflen );


    if( ret == MBEDTLS_ERR_SSL_UNEXPECTED_CID ||
        ret == MBEDTLS_ERR_SSL_EARLY_MESSAGE )
    {
        ret = MBEDTLS_ERR_SSL_UNEXPECTED_RECORD;
    }

    MBEDTLS_SSL_DEBUG_MSG( 1, ( "<= mbedtls_ssl_check_record" ) );
    return( ret );
}
