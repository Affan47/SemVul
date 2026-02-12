static int ssl_parse_alpn_ext( ssl_context *ssl,
                               const unsigned char *buf, size_t len )
{
    size_t list_len, cur_len, ours_len;
    const unsigned char *theirs, *start, *end;
    const char **ours;


    if( ssl->alpn_list == NULL )
        return( 0 );


    if( len < 4 )
        return( POLARSSL_ERR_SSL_BAD_HS_CLIENT_HELLO );

    list_len = ( buf[0] << 8 ) | buf[1];
    if( list_len != len - 2 )
        return( POLARSSL_ERR_SSL_BAD_HS_CLIENT_HELLO );


    start = buf + 2;
    end = buf + len;
    for( ours = ssl->alpn_list; *ours != NULL; ours++ )
    {
        ours_len = strlen( *ours );
        for( theirs = start; theirs != end; theirs += cur_len )
        {

            if( theirs > end )
                return( POLARSSL_ERR_SSL_BAD_HS_CLIENT_HELLO );

            cur_len = *theirs++;


            if( cur_len == 0 )
                return( POLARSSL_ERR_SSL_BAD_HS_CLIENT_HELLO );

            if( cur_len == ours_len &&
                memcmp( theirs, *ours, cur_len ) == 0 )
            {
                ssl->alpn_chosen = *ours;
                return( 0 );
            }
        }
    }


    ssl_send_alert_message( ssl, SSL_ALERT_LEVEL_FATAL,
                            SSL_ALERT_MSG_NO_APPLICATION_PROTOCOL );
    return( POLARSSL_ERR_SSL_BAD_HS_CLIENT_HELLO );
}
