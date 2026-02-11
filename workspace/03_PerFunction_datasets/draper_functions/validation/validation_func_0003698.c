us_net_get_nameinfo( struct addrinfo *ai, char *hostname_buf, int hostname_buf_len, char *serv_buf, int serv_buf_len )
{
    bool r = false;
    if ( getnameinfo( ai->ai_addr,
                      ai->ai_addrlen,
                      hostname_buf,
                      hostname_buf_len,
                      serv_buf,
                      serv_buf_len,
                      NI_NUMERICHOST | NI_NUMERICSERV ) == 0 )
    {
        r = true;
    }
    return r;
}
