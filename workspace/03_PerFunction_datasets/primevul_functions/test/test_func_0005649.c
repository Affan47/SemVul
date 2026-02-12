void mbedtls_ssl_recv_flight_completed( mbedtls_ssl_context *ssl )
{

    mbedtls_ssl_flight_free( ssl->handshake->flight );
    ssl->handshake->flight = NULL;
    ssl->handshake->cur_msg = NULL;


    ssl->handshake->in_flight_start_seq = ssl->handshake->in_msg_seq;


    ssl->handshake->buffering.seen_ccs = 0;


    mbedtls_ssl_buffering_free( ssl );


    mbedtls_ssl_set_timer( ssl, 0 );

    if( ssl->in_msgtype == MBEDTLS_SSL_MSG_HANDSHAKE &&
        ssl->in_msg[0] == MBEDTLS_SSL_HS_FINISHED )
    {
        ssl->handshake->retransmit_state = MBEDTLS_SSL_RETRANS_FINISHED;
    }
    else
        ssl->handshake->retransmit_state = MBEDTLS_SSL_RETRANS_PREPARING;
}
