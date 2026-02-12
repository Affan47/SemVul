static void ssl_extract_add_data_from_record( unsigned char* add_data,
                                              size_t *add_data_len,
                                              mbedtls_record *rec,
                                              unsigned minor_ver )
{


    unsigned char *cur = add_data;

#if defined(MBEDTLS_SSL_PROTO_TLS1_3_EXPERIMENTAL)
    if( minor_ver != MBEDTLS_SSL_MINOR_VERSION_4 )
#endif
    {
        ((void) minor_ver);
        memcpy( cur, rec->ctr, sizeof( rec->ctr ) );
        cur += sizeof( rec->ctr );
    }

    *cur = rec->type;
    cur++;

    memcpy( cur, rec->ver, sizeof( rec->ver ) );
    cur += sizeof( rec->ver );

#if defined(MBEDTLS_SSL_DTLS_CONNECTION_ID)
    if( rec->cid_len != 0 )
    {
        memcpy( cur, rec->cid, rec->cid_len );
        cur += rec->cid_len;

        *cur = rec->cid_len;
        cur++;

        MBEDTLS_PUT_UINT16_BE( rec->data_len, cur, 0 );
        cur += 2;
    }
    else
#endif
    {
        MBEDTLS_PUT_UINT16_BE( rec->data_len, cur, 0 );
        cur += 2;
    }

    *add_data_len = cur - add_data;
}
