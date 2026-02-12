void (*SSL_get_info_callback(const SSL *ssl)) (const SSL *  ,
                                               int  ,
                                               int  ) {
    return ssl->info_callback;
}
