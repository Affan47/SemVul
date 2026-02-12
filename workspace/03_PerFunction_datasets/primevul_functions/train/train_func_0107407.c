static int ssl_write_real( ssl_context *ssl,
                           const unsigned char *buf, size_t len )
{
    int ret;
    size_t n;
    unsigned int max_len = SSL_MAX_CONTENT_LEN;

#if defined(POLARSSL_SSL_MAX_FRAGMENT_LENGTH)


    max_len = mfl_code_to_length[ssl->mfl_code];


    if( ssl->session_out != NULL &&
        mfl_code_to_length[ssl->session_out->mfl_code] < max_len )
    {
        max_len = mfl_code_to_length[ssl->session_out->mfl_code];
    }
#endif

    n = ( len < max_len) ? len : max_len;

    if( ssl->out_left != 0 )
    {
        if( ( ret = ssl_flush_output( ssl ) ) != 0 )
        {
            SSL_DEBUG_RET( 1, "ssl_flush_output", ret );
            return( ret );
        }
    }
    else
    {
        ssl->out_msglen  = n;
        ssl->out_msgtype = SSL_MSG_APPLICATION_DATA;
        memcpy( ssl->out_msg, buf, n );

        if( ( ret = ssl_write_record( ssl ) ) != 0 )
        {
            SSL_DEBUG_RET( 1, "ssl_write_record", ret );
            return( ret );
        }
    }

    return( (int) n );
}
