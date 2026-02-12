void mbedtls_ssl_update_handshake_status( mbedtls_ssl_context *ssl )
{
    mbedtls_ssl_handshake_params * const hs = ssl->handshake;

    if( ssl->state != MBEDTLS_SSL_HANDSHAKE_OVER && hs != NULL )
    {
        ssl->handshake->update_checksum( ssl, ssl->in_msg, ssl->in_hslen );
    }


#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM &&
        ssl->handshake != NULL )
    {
        unsigned offset;
        mbedtls_ssl_hs_buffer *hs_buf;


        hs->in_msg_seq++;


        ssl_buffering_free_slot( ssl, 0 );


        for( offset = 0, hs_buf = &hs->buffering.hs[0];
             offset + 1 < MBEDTLS_SSL_MAX_BUFFERED_HS;
             offset++, hs_buf++ )
        {
            *hs_buf = *(hs_buf + 1);
        }


        memset( hs_buf, 0, sizeof( mbedtls_ssl_hs_buffer ) );
    }
#endif
}
