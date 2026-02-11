wasp_tcp_connect( wasp_value host, wasp_value service ){
    int result;
    struct addrinfo hints;
    struct addrinfo* addr;
    char* service_str;
    wasp_string host_str;

    if( wasp_is_integer( host ) ){
        wasp_quad addr = wasp_integer_fv( host );
        host_str = wasp_formatf( "isisisi",
                                 addr >> 24, ".",
                                 (addr >> 16) & 255, ".",
                                 (addr >> 8) & 255, ".",
                                 addr & 255 );
    }else host_str = wasp_req_string( host ) ;

    if( wasp_is_string( service ) ){
        service_str = wasp_sf_string( wasp_string_fv( service ) );
    }else{
        char buf[ 17 ];
        service_str = utoa( buf, wasp_req_integer( service ) );
    }

    bzero( &hints, sizeof( struct addrinfo ) );

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    addr = NULL;

    result = getaddrinfo(
        wasp_sf_string( host_str ), service_str, &hints, &addr
    );

    if( result ){
        if( addr ) freeaddrinfo( addr );
        wasp_errf( wasp_es_vm, "sxx", gai_strerror( result ), host, service );
    }

    result = socket( addr->ai_family, addr->ai_socktype, addr->ai_protocol );

    if( result == -1 ){
        freeaddrinfo( addr );
        wasp_report_net_error( );
    }


    if( connect( result, addr->ai_addr, (int) addr->ai_addrlen ) ){
        freeaddrinfo( addr );
        wasp_report_net_error( );
    }

    wasp_unblock_fd( result );

    wasp_os_connection conn = wasp_make_os_connection( result, 0 );
    IO_TRACE( "Connecting to remote host on %x\n", conn );

    return conn;
}
