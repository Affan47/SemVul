ssl_write_finished( ssl_context *ssl )
{
    int ret, hash_len;
     md5_context  md5;
    sha1_context sha1;

    SSL_DEBUG_MSG( 2, ( "=> write finished" ) );

    memcpy( &md5 , &ssl->fin_md5 , sizeof(  md5_context ) );
    memcpy( &sha1, &ssl->fin_sha1, sizeof( sha1_context ) );

    ssl_calc_finished( ssl, ssl->out_msg + 4,
                       ssl->endpoint, &md5, &sha1 );

    hash_len = ( ssl->minor_ver == SSL_MINOR_VERSION_0 ) ? 36 : 12;

    ssl->out_msglen  = 4 + hash_len;
    ssl->out_msgtype = SSL_MSG_HANDSHAKE;
    ssl->out_msg[0]  = SSL_HS_FINISHED;


    if( ssl->resume != 0 )
    {
        if( ssl->endpoint == SSL_IS_CLIENT )
            ssl->state = SSL_HANDSHAKE_OVER;
        else
            ssl->state = SSL_CLIENT_CHANGE_CIPHER_SPEC;
    }
    else
        ssl->state++;

    ssl->do_crypt = 1;

    if( ( ret = ssl_write_record( ssl ) ) != 0 )
    {
        SSL_DEBUG_RET( 1, "ssl_write_record", ret );
        return( ret );
    }

    SSL_DEBUG_MSG( 2, ( "<= write finished" ) );

    return( 0 );
}
