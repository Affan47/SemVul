static int ssl_parse_record_header( mbedtls_ssl_context const *ssl,
                                    unsigned char *buf,
                                    size_t len,
                                    mbedtls_record *rec )
{
    int major_ver, minor_ver;

    size_t const rec_hdr_type_offset    = 0;
    size_t const rec_hdr_type_len       = 1;

    size_t const rec_hdr_version_offset = rec_hdr_type_offset +
                                          rec_hdr_type_len;
    size_t const rec_hdr_version_len    = 2;

    size_t const rec_hdr_ctr_len        = 8;
#if defined(MBEDTLS_SSL_PROTO_DTLS)
    uint32_t     rec_epoch;
    size_t const rec_hdr_ctr_offset     = rec_hdr_version_offset +
                                          rec_hdr_version_len;

#if defined(MBEDTLS_SSL_DTLS_CONNECTION_ID)
    size_t const rec_hdr_cid_offset     = rec_hdr_ctr_offset +
                                          rec_hdr_ctr_len;
    size_t       rec_hdr_cid_len        = 0;
#endif
#endif

    size_t       rec_hdr_len_offset;
    size_t const rec_hdr_len_len    = 2;


#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM )
    {
        rec_hdr_len_offset = rec_hdr_ctr_offset + rec_hdr_ctr_len;
    }
    else
#endif
    {
        rec_hdr_len_offset = rec_hdr_version_offset + rec_hdr_version_len;
    }

    if( len < rec_hdr_len_offset + rec_hdr_len_len )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "datagram of length %u too small to hold DTLS record header of length %u",
                 (unsigned) len,
                 (unsigned)( rec_hdr_len_len + rec_hdr_len_len ) ) );
        return( MBEDTLS_ERR_SSL_INVALID_RECORD );
    }


    rec->type = buf[ rec_hdr_type_offset ];


#if defined(MBEDTLS_SSL_DTLS_CONNECTION_ID)
    rec->cid_len = 0;

    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM &&
        ssl->conf->cid_len != 0                                &&
        rec->type == MBEDTLS_SSL_MSG_CID )
    {


        rec_hdr_cid_len = ssl->conf->cid_len;
        rec_hdr_len_offset += rec_hdr_cid_len;

        if( len < rec_hdr_len_offset + rec_hdr_len_len )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "datagram of length %u too small to hold DTLS record header including CID, length %u",
                (unsigned) len,
                (unsigned)( rec_hdr_len_offset + rec_hdr_len_len ) ) );
            return( MBEDTLS_ERR_SSL_INVALID_RECORD );
        }


        rec->cid_len = (uint8_t) rec_hdr_cid_len;
        memcpy( rec->cid, buf + rec_hdr_cid_offset, rec_hdr_cid_len );
    }
    else
#endif
    {
        if( ssl_check_record_type( rec->type ) )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "unknown record type %u",
                                        (unsigned) rec->type ) );
            return( MBEDTLS_ERR_SSL_INVALID_RECORD );
        }
    }


    rec->ver[0] = buf[ rec_hdr_version_offset + 0 ];
    rec->ver[1] = buf[ rec_hdr_version_offset + 1 ];
    mbedtls_ssl_read_version( &major_ver, &minor_ver,
                              ssl->conf->transport,
                              &rec->ver[0] );

    if( major_ver != ssl->major_ver )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "major version mismatch: got %u, expected %u",
                                    (unsigned) major_ver,
                                    (unsigned) ssl->major_ver ) );
        return( MBEDTLS_ERR_SSL_INVALID_RECORD );
    }

    if( minor_ver > ssl->conf->max_minor_ver )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "minor version mismatch: got %u, expected max %u",
                                    (unsigned) minor_ver,
                                    (unsigned) ssl->conf->max_minor_ver ) );
        return( MBEDTLS_ERR_SSL_INVALID_RECORD );
    }


#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM )
    {

        memcpy( &rec->ctr[0], buf + rec_hdr_ctr_offset,
                rec_hdr_ctr_len );
    }
    else
#endif
    {

        memcpy( &rec->ctr[0], ssl->in_ctr, rec_hdr_ctr_len );
    }


    rec->data_offset = rec_hdr_len_offset + rec_hdr_len_len;
    rec->data_len    = ( (size_t) buf[ rec_hdr_len_offset + 0 ] << 8 ) |
                       ( (size_t) buf[ rec_hdr_len_offset + 1 ] << 0 );
    MBEDTLS_SSL_DEBUG_BUF( 4, "input record header", buf, rec->data_offset );

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "input record: msgtype = %u, "
                                "version = [%d:%d], msglen = %" MBEDTLS_PRINTF_SIZET,
                                rec->type,
                                major_ver, minor_ver, rec->data_len ) );

    rec->buf     = buf;
    rec->buf_len = rec->data_offset + rec->data_len;

    if( rec->data_len == 0 )
        return( MBEDTLS_ERR_SSL_INVALID_RECORD );


#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM )
    {
        rec_epoch = ( rec->ctr[0] << 8 ) | rec->ctr[1];


        if( len < rec->data_offset + rec->data_len )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "Datagram of length %u too small to contain record of advertised length %u.",
                             (unsigned) len,
                             (unsigned)( rec->data_offset + rec->data_len ) ) );
            return( MBEDTLS_ERR_SSL_INVALID_RECORD );
        }


        if( rec_epoch != ssl->in_epoch )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "record from another epoch: "
                                        "expected %u, received %lu",
                                        ssl->in_epoch, (unsigned long) rec_epoch ) );


            if( rec_epoch == (unsigned) ssl->in_epoch + 1 )
            {
                MBEDTLS_SSL_DEBUG_MSG( 2, ( "Consider record for buffering" ) );
                return( MBEDTLS_ERR_SSL_EARLY_MESSAGE );
            }

            return( MBEDTLS_ERR_SSL_UNEXPECTED_RECORD );
        }
#if defined(MBEDTLS_SSL_DTLS_ANTI_REPLAY)


        else if( mbedtls_ssl_dtls_record_replay_check( (mbedtls_ssl_context *) ssl,
            &rec->ctr[0] ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "replayed record" ) );
            return( MBEDTLS_ERR_SSL_UNEXPECTED_RECORD );
        }
#endif
    }
#endif

    return( 0 );
}
