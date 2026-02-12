void mbedtls_ssl_update_in_pointers( mbedtls_ssl_context *ssl )
{


#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM )
    {


        ssl->in_ctr = ssl->in_hdr +  3;
#if defined(MBEDTLS_SSL_DTLS_CONNECTION_ID)
        ssl->in_cid = ssl->in_ctr +  8;
        ssl->in_len = ssl->in_cid;
#else
        ssl->in_len = ssl->in_ctr + 8;
#endif
        ssl->in_iv  = ssl->in_len + 2;
    }
    else
#endif
    {
        ssl->in_ctr = ssl->in_hdr - 8;
        ssl->in_len = ssl->in_hdr + 3;
#if defined(MBEDTLS_SSL_DTLS_CONNECTION_ID)
        ssl->in_cid = ssl->in_len;
#endif
        ssl->in_iv  = ssl->in_hdr + 5;
    }


    ssl->in_msg = ssl->in_iv;
}
